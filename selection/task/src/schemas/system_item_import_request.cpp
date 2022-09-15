#include <iostream>

#include "system_item_import_request.h"

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

    bool SystemItemImportRequest::database_save(const std::shared_ptr<PGConnection> &a_PGConnection) const {
        if (PQstatus(a_PGConnection->GetConnection().get()) != CONNECTION_OK) {
            std::cerr << "Connection to database failed: "
                      << PQerrorMessage(a_PGConnection->GetConnection().get()) << std::endl;
            return false;
        } else {
            std::cerr << "Connection to database has been established" << std::endl;
        }

        PQexec(a_PGConnection->GetConnection().get(), "BEGIN");

        for (const auto &item: items) {
            PGresult *res = nullptr;
            int nParams = 5;

            std:: string sql = R"(INSERT INTO system_item (id, url, date, dt_date, type, size) VALUES ( $1::VARCHAR, CASE WHEN $2='' THEN NULL ELSE $2::VARCHAR END, $3::VARCHAR, TO_TIMESTAMP($3, 'YYYY-MM-DD"T"HH24:MI:SS"Z"'), $4::VARCHAR, CASE WHEN $5='' THEN NULL ELSE $5::BIGINT END );)";
            const char* paramValues[] = {
                    item.id.c_str(),
                    item.url.has_value() ? item.url.value().c_str() : "",
                    updateDate.c_str(),
                    schemas::to_string(item.type).c_str(),
                    item.size.has_value() ? std::to_string(item.size.value()).c_str() : ""
            };
            std::cerr << sql <<std::endl;
            const int paramLengths[] = {
                    sizeof(paramValues[0]),
                    sizeof(paramValues[1],
                    sizeof(paramValues[2]),
                    sizeof(paramValues[3]),
                    sizeof(paramValues[4])
            )};
            const int paramFormats[] = {0, 0, 0, 0, 0};
            int resultFormat = 0;
            res = PQexecParams(
                    a_PGConnection->GetConnection().get(),
                    sql.c_str(),
                    nParams,
                    nullptr,
                    paramValues,
                    paramLengths,
                    paramFormats,
                    resultFormat);
            if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                std::cerr << "PQexecParams failed: " << PQresultErrorMessage(res)
                          << std::endl;
                PQexec(a_PGConnection->GetConnection().get(), "ROLLBACK");
                return false;
            }
        }

        PQexec(a_PGConnection->GetConnection().get(), "COMMIT");
        return true;
    }
}