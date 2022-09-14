#ifndef DISK_REST_API_SCHEMAS_SYSTEM_ITEM_IMPORT_SCHEMA_H
#define DISK_REST_API_SCHEMAS_SYSTEM_ITEM_IMPORT_SCHEMA_H

#include <string>
#include <optional>

#include "json.hpp"

using json = nlohmann::json;

#include "base_schema.h"
#include "system_item_type.h"

namespace schemas {

    class SystemItemImportSchema : public BaseSchema {
    public:
        const std::string id;
        const std::optional<std::string> url;
        const std::optional<std::string> parentId;
        const SystemItemType type;
        const std::optional<int64_t> size;

        SystemItemImportSchema(
                std::string id,
                std::optional <std::string> url,
                std::optional <std::string> parentId,
                SystemItemType type,
                std::optional<int64_t> size
        )
                : id(std::move(id))
                , url(std::move(url))
                , parentId(std::move(parentId))
                , type(type)
                , size(size) {}

        json to_json() const override {
            json j;
            j["id"] = id;
            if (url.has_value()) {
                j["url"] = url.value();
            }
            if (parentId.has_value()) {
                j["parentId"] = parentId.value();
            }
            j["type"] = type;
            if (size.has_value()) {
                j["size"] = size.value();
            }
            return j;
        }

        static SystemItemImportSchema from_json(const json& j);
    };
}

#endif //DISK_REST_API_SCHEMAS_SYSTEM_ITEM_IMPORT_SCHEMA_H
