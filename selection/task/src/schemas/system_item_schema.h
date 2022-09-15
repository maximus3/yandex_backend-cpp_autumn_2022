#ifndef DISK_REST_API_SCHEMAS_SYSTEM_ITEM_SCHEMA_H
#define DISK_REST_API_SCHEMAS_SYSTEM_ITEM_SCHEMA_H

#include <string>
#include <optional>
#include <vector>
#include <algorithm>

#include "json.hpp"

using json = nlohmann::json;

#include "base_schema.h"
#include "system_item_type.h"
#include "pg_connection.h"
#include "status.h"

namespace schemas {

    class SystemItemSchema : public BaseSchema {
    public:
        const std::string id;
        const std::optional<std::string> url;
        const std::string date;
        const std::optional<std::string> parentId;
        const SystemItemType type;
        const std::optional<int64_t> size;
        const std::optional<std::vector<SystemItemSchema>> children;

        SystemItemSchema(
                std::string id,
                std::optional<std::string> url,
                std::string date,
                std::optional<std::string> parentId,
                SystemItemType type,
                std::optional<int64_t> size,
                std::optional<std::vector<SystemItemSchema>> children
        )
                : id(std::move(id))
                , url(std::move(url))
                , date(std::move(date))
                , parentId(std::move(parentId))
                , type(type)
                , size(size)
                , children(std::move(children)) {}

        json to_json() const override  {
            std::cerr << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << std::endl;
            json j;
            j["id"] = id;
            std::cerr << __FILE__ << ":" << __LINE__ << " ID OK" << std::endl;
            if (url.has_value()) {
                j["url"] = url.value();
            } else {
                j["url"] = nullptr;
            }
            std::cerr << __FILE__ << ":" << __LINE__ << " URL OK" << std::endl;
            j["date"] = date;
            std::cerr << __FILE__ << ":" << __LINE__ << " DATE OK" << std::endl;
            if (parentId.has_value()) {
                j["parentId"] = parentId.value();
            } else {
                j["parentId"] = nullptr;
            }
            std::cerr << __FILE__ << ":" << __LINE__ << " PARENT ID OK" << std::endl;
            j["type"] = schemas::to_string(type);
            std::cerr << __FILE__ << ":" << __LINE__ << " TYPE OK" << std::endl;
            std::cerr << "size: " << size.has_value() << std::endl;
            if (size.has_value()) {
                j["size"] = size.value();
            } else {
                j["size"] = nullptr;
            }
            std::cerr << "size ok" << std::endl;
            if (children.has_value()) {
                j["children"] = json::array();
                for (const auto& child : children.value()) {
                    j["children"].push_back(child.to_json());
                }
            } else {
                if (type == SystemItemType::FOLDER) {
                    j["children"] = json::array();
                } else {
                    j["children"] = nullptr;
                }
            }
            return j;
        }

        static SystemItemSchema from_json(const json& j);

        database::Status database_save(const std::shared_ptr<PGConnection>& a_PGConnection);
        database::Status database_delete(const std::shared_ptr<PGConnection>& a_PGConnection, std::stringstream& a_StatusStream);
        static database::Status database_get(const std::shared_ptr<PGConnection>& a_PGConnection, std::stringstream& a_StatusStream, std::vector<SystemItemSchema>& a_ReturnVector, const std::string& a_Field, const std::string& a_Value, bool need_children = false);
        static database::Status database_get(const std::shared_ptr<PGConnection>& a_PGConnection, std::stringstream& a_StatusStream, std::optional<SystemItemSchema>& a_ReturnValue, const std::string& a_Field, const std::string& a_Value, bool need_children = false);

    };
}

#endif //DISK_REST_API_SCHEMAS_SYSTEM_ITEM_SCHEMA_H
