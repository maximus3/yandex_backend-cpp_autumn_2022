#include <iostream>
#include "system_item_schema.h"

namespace schemas {

    SystemItemSchema SystemItemSchema::from_json(const json& j) {
        const std::vector<std::string>& available_fields = {
                "id",
                "url",
                "date",
                "parentId",
                "type",
                "size",
                "children"
        };
        validate_fields(j, available_fields);

        auto _id = j.at("id").get<std::string>();

        std::optional<std::string> _url;
        if (j.contains("url") && !j.at("url").is_null()) {
            _url = j.at("url").get<std::string>();
        } else {
            _url = std::nullopt;
        }

        auto _date = j.at("date").get<std::string>();

        std::optional<std::string> _parentId;
        if (j.contains("parentId") && !j.at("parentId").is_null()) {
            _parentId = j.at("parentId").get<std::string>();
        } else {
            _parentId = std::nullopt;
        }

        auto _type = to_system_item(j.at("type").get<std::string>());

        std::optional<int64_t> _size;
        if (j.contains("size") && !j.at("size").is_null()) {
            _size = j.at("size").get<int64_t>();
        } else {
            _size = std::nullopt;
        }

        std::optional<std::vector<SystemItemSchema>> _children;
        if (j.contains("children") && !j.at("children").is_null()) {
            _children = std::vector<SystemItemSchema>();
            for (auto& child : j.at("children")) {
                _children->push_back(SystemItemSchema::from_json(child));
            }
        } else {
            _children = std::nullopt;
        }

        // Change children FILE to None, Folder to []
        if (_type == SystemItemType::FILE) {
            _children = std::nullopt;
        } else if (_type == SystemItemType::FOLDER) {
            _children = _children.has_value() ? _children : std::vector<SystemItemSchema>() ;
        }

        return {
                std::move(_id),
                std::move(_url),
                std::move(_date),
                std::move(_parentId),
                _type,
                _size,
                std::move(_children)
        };
    }

    database::Status SystemItemSchema::database_save(const std::shared_ptr<PGConnection>& a_PGConnection) {
        return database::Status::DATABASE_ERROR;
    }

    database::Status SystemItemSchema::database_get(const std::shared_ptr<PGConnection>& a_PGConnection, std::stringstream& a_StatusStream, std::vector<SystemItemSchema>& a_ReturnVector, const std::string& a_Field, const std::string& a_Value) {
        const char command[] = "SELECT id, url, date, parentId, type, size FROM system_item WHERE $1 = $2;";
        int nParams = 2;
        const char* paramValues[] = {
                a_Field.c_str(),
                a_Value.c_str()
        };
        const int paramLengths[] = {
                sizeof(paramValues[0]),
                sizeof(paramValues[1])
        };
        const int paramFormats[] = {0, 0};
        int resultFormat = 0;
        PGresult *res = PQexecParams(
                a_PGConnection->GetConnection().get(),
                command,
                nParams,
                nullptr,
                paramValues,
                paramLengths,
                paramFormats,
                resultFormat);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            a_StatusStream << "SELECT failed: " << PQresultErrorMessage(res);
            return database::Status::DATABASE_ERROR;
        } else {
            std::cerr << "Get " << PQntuples(res) << " tuples, each tuple has "
                      << PQnfields(res) << " fields" << std::endl;
            for (int i = 0; i < PQntuples(res); i++) {
                json js;
                for (int j = 0; j < PQnfields(res); j++) {
                    js[PQfname(res, j)] = PQgetvalue(res, i, j);
                }
                a_ReturnVector.push_back(SystemItemSchema::from_json(js));
            }
        }

        return database::Status::OK;
    }
    database::Status SystemItemSchema::database_get(const std::shared_ptr<PGConnection>& a_PGConnection, std::stringstream& a_StatusStream, std::optional<SystemItemSchema>& a_ReturnValue, const std::string& a_Field, const std::string& a_Value) {
        std::vector<SystemItemSchema> returnVector;
        a_ReturnValue = std::nullopt;
        database::Status status = database_get(a_PGConnection, a_StatusStream, returnVector, a_Field, a_Value);
        if (status != database::Status::OK) {
            return status;
        }
        if (returnVector.empty()) {
            return database::Status::OK;
        } else if (returnVector.size() == 1) {
            a_ReturnValue.emplace(returnVector[0]);
            return database::Status::OK;
        } else {
            a_StatusStream << "DB returned more than one item with " << a_Field << " = " << a_Value;
            return database::Status::DATABASE_ERROR;
        }
    }
}
