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

        static SystemItemImportSchema from_json(const json& j) {
            const std::vector<std::string>& available_fields = {
                    "id",
                    "url",
                    "parentId",
                    "type",
                    "size"
            };
            validate_fields(j, available_fields);

            auto _id = j.at("id").get<std::string>();

            std::optional<std::string> _url;
            if (j.contains("url") && !j.at("url").is_null()) {
                std::cerr << "Have url" << std::endl;
                _url = j.at("url").get<std::string>();
            } else {
                _url = std::nullopt;
            }

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

            // TODO: validate

            return {
                    std::move(_id),
                    std::move(_url),
                    std::move(_parentId),
                    _type,
                    _size
            };
        }
    };
}

#endif //DISK_REST_API_SCHEMAS_SYSTEM_ITEM_IMPORT_SCHEMA_H
