#include <iostream>
#include <set>
#include <string>

#include "system_item_import_request.h"
#include "system_item_schema.h"

namespace schemas {
    SystemItemImportRequest SystemItemImportRequest::from_json(const json &j) {
        const std::vector<std::string> &available_fields = {
                "items",
                "updateDate"
        };
        validate_fields(j, available_fields);

        auto _items = std::vector<SystemItemImportSchema>();
        for (const auto &item: j.at("items")) {
            _items.push_back(SystemItemImportSchema::from_json(item));
        }
        auto _updateDate = j.at("updateDate").get<std::string>();

        utils::validators::date_must_be_iso_8601(_updateDate);

        return {
                std::move(_items),
                std::move(_updateDate)
        };
    }

    database::Status SystemItemImportRequest::database_save(const std::shared_ptr<PGConnection>& a_PGConnection, std::stringstream& a_StatusStream) const {
        if (PQstatus(a_PGConnection->GetConnection().get()) != CONNECTION_OK) {
            std::cerr << "Connection to database failed: "
                      << PQerrorMessage(a_PGConnection->GetConnection().get()) << std::endl;
            a_StatusStream << "Connection to database failed";
            return database::Status::DATABASE_ERROR;
        } else {
            std::cerr << "Connection to database has been established" << std::endl;
        }

        std::vector<SystemItemSchema> _items;
        auto _status = SystemItemSchema::database_get(a_PGConnection, a_StatusStream, _items, "id", items[0].id);
        std::cerr << _items.size() << std::endl;

        PQexec(a_PGConnection->GetConnection().get(), "BEGIN");

        std::set<std::string> _items_ids;

        for (const auto &item: items) {

            // Check if item already in query
            if (_items_ids.contains(item.id)) {
                a_StatusStream << "Item with id " << item.id << " already exists";
                PQexec(a_PGConnection->GetConnection().get(), "ROLLBACK");
                return database::Status::VALIDATION_ERROR;
            }
            _items_ids.insert(item.id);

            // Check if parent is FOLDER
            if (item.parentId.has_value()) {
                std::optional<SystemItemSchema> _parent;
                _status = SystemItemSchema::database_get(a_PGConnection, a_StatusStream, _parent, "id", item.parentId.value());
                if (_status != database::Status::OK) {
                    PQexec(a_PGConnection->GetConnection().get(), "ROLLBACK");
                    return _status;
                }
                if (!_parent.has_value()) {
                    a_StatusStream << "Item with id " << item.id << " has parent with id " << item.parentId.value() << " which does not exist";
                    PQexec(a_PGConnection->GetConnection().get(), "ROLLBACK");
                    return database::Status::VALIDATION_ERROR;
                } else {
                    if (_parent.value().type != SystemItemType::FOLDER) {
                        a_StatusStream << "Item with id " << item.id << " has parent with id " << item.parentId.value() << " which is not FOLDER";
                        PQexec(a_PGConnection->GetConnection().get(), "ROLLBACK");
                        return database::Status::VALIDATION_ERROR;
                    }
                }
            }

            // Check if item already in database
            std::optional<SystemItemSchema> _item;
            _status = SystemItemSchema::database_get(a_PGConnection, a_StatusStream, _item, "id", item.id);
            if (_status != database::Status::OK) {
                PQexec(a_PGConnection->GetConnection().get(), "ROLLBACK");
                return _status;
            }
            std::stringstream size_stream;
            if (item.size.has_value()) {
                size_stream << item.size.value();
            }
            if (_item.has_value()) {
                // UPDATE

                // Check item type is the same
                if (_item.value().type != item.type) {
                    a_StatusStream << "Item with id " << item.id << " already exists in database but has different type";
                    PQexec(a_PGConnection->GetConnection().get(), "ROLLBACK");
                    return database::Status::VALIDATION_ERROR;
                }

                int nParams = 6;
                std:: string sql = R"(UPDATE system_item SET url = CASE WHEN $1='' THEN NULL ELSE $1::VARCHAR END, date = $2::VARCHAR, dt_date = TO_TIMESTAMP($2, 'YYYY-MM-DD"T"HH24:MI:SS"Z"'), parentId = CASE WHEN $3='' THEN NULL ELSE $3 END, type=$4, size = CASE WHEN $5='' THEN NULL ELSE $5::BIGINT END WHERE id = $6;)";
                const char* paramValues[] = {
                        item.url.has_value() ? item.url.value().c_str() : "",
                        updateDate.c_str(),
                        item.parentId.has_value() ? item.parentId.value().c_str() : "",
                        schemas::to_string(item.type).c_str(),
                        size_stream.str().c_str(),
                        item.id.c_str()
                };
                const int paramLengths[] = {
                        sizeof(paramValues[0]),
                        sizeof(paramValues[1],
                            sizeof(paramValues[2]),
                            sizeof(paramValues[3]),
                            sizeof(paramValues[4]),
                            sizeof(paramValues[5])
                        )};
                const int paramFormats[] = {0, 0, 0, 0, 0, 0};
                int resultFormat = 0;
                PGresult *res = PQexecParams(
                        a_PGConnection->GetConnection().get(),
                        sql.c_str(),
                        nParams,
                        nullptr,
                        paramValues,
                        paramLengths,
                        paramFormats,
                        resultFormat);
                if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                    a_StatusStream << "UPDATE failed: " << PQresultErrorMessage(res)
                                   << std::endl;
                    PQexec(a_PGConnection->GetConnection().get(), "ROLLBACK");
                    return database::Status::VALIDATION_ERROR;
                }
            } else {
                // CREATE
                int nParams = 6;
                std:: string sql = R"(INSERT INTO system_item (
                        id,
                        url,
                        date,
                        dt_date,
                        parentId,
                        size,
                        type
                    ) VALUES (
                        $1::VARCHAR,
                        CASE WHEN $2='' THEN NULL ELSE $2::VARCHAR END,
                        $3::VARCHAR,
                        TO_TIMESTAMP($3, 'YYYY-MM-DD"T"HH24:MI:SS"Z"'),
                        CASE WHEN $4='' THEN NULL ELSE $4 END,
                        CASE WHEN $5='' THEN NULL ELSE $5::BIGINT END,
                        $6::VARCHAR
                         );)";
                //std::cerr << "Inserting " << item.to_string() << std::endl;
                const char* paramValues[] = {
                        item.id.c_str(),
                        item.url.has_value() ? item.url.value().c_str() : "",
                        updateDate.c_str(),
                        item.parentId.has_value() ? item.parentId.value().c_str() : "",
                        size_stream.str().c_str(),
                        schemas::to_string(item.type).c_str()
                };
                const int paramLengths[] = {
                        sizeof(paramValues[0]),
                        sizeof(paramValues[1],
                            sizeof(paramValues[2]),
                            sizeof(paramValues[3]),
                            sizeof(paramValues[4]),
                            sizeof(paramValues[5])
                        )};
                const int paramFormats[] = {0, 0, 0, 0, 0, 0};
                int resultFormat = 0;
                //std::cerr << "Executing " << sql << std::endl;
                //std::cerr << "Params: " << paramValues[0] << ", " << paramValues[1] << ", " << paramValues[2] << ", " << paramValues[3] << ", " << paramValues[4] << ", " << paramValues[5] << std::endl;
                PGresult *res = PQexecParams(
                        a_PGConnection->GetConnection().get(),
                        sql.c_str(),
                        nParams,
                        nullptr,
                        paramValues,
                        paramLengths,
                        paramFormats,
                        resultFormat);
                if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                    a_StatusStream << "CREATE failed: " << PQresultErrorMessage(res)
                              << std::endl;
                    PQexec(a_PGConnection->GetConnection().get(), "ROLLBACK");
                    return database::Status::VALIDATION_ERROR;
                }
            }
        }

        PQexec(a_PGConnection->GetConnection().get(), "COMMIT");
        return database::Status::OK;
    }
}