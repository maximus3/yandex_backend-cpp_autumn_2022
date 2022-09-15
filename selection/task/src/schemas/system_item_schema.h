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
            json j;
            j["id"] = id;
            if (url.has_value()) {
                j["url"] = url.value();
            }
            j["date"] = date;
            if (parentId.has_value()) {
                j["parentId"] = parentId.value();
            }
            j["type"] = type;
            if (size.has_value()) {
                j["size"] = size.value();
            }
            if (children.has_value()) {
                j["children"] = json::array();
                for (auto& child : children.value()) {
                    j["children"].push_back(child.to_json());
                }
            }
            return j;
        }

        static SystemItemSchema from_json(const json& j);

        bool database_save(std::shared_ptr<PGConnection>& a_PGConnection) const;
        std::vector<SystemItemSchema> database_get(std::shared_ptr<PGConnection>& a_PGConnection, const std::string& field, const std::string& value) const;

    };
}

#endif //DISK_REST_API_SCHEMAS_SYSTEM_ITEM_SCHEMA_H
