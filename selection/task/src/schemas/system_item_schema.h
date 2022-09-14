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
                , size(std::move(size))
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

        static SystemItemSchema from_json(const json& j) {
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
            if (j.contains("url")) {
                _url = j.at("url").get<std::string>();
            } else {
                _url = std::nullopt;
            }

            auto _date = j.at("date").get<std::string>();

            std::optional<std::string> _parentId;
            if (j.contains("parentId")) {
                _parentId = j.at("parentId").get<std::string>();
            } else {
                _parentId = std::nullopt;
            }

            auto _type = j.at("type").get<SystemItemType>();

            std::optional<int64_t> _size;
            if (j.contains("size")) {
                _size = j.at("size").get<int64_t>();
            } else {
                _size = std::nullopt;
            }

            std::optional<std::vector<SystemItemSchema>> _children;
            if (j.contains("children")) {
                _children = std::vector<SystemItemSchema>();
                for (auto& child : j.at("children")) {
                    _children->push_back(SystemItemSchema::from_json(child));
                }
            } else {
                _children = std::nullopt;
            }

            // TODO: validate

            return {
                    std::move(_id),
                    std::move(_url),
                    std::move(_date),
                    std::move(_parentId),
                    std::move(_type),
                    std::move(_size),
                    std::move(_children)
            };
        }

    };
}

#endif //DISK_REST_API_SCHEMAS_SYSTEM_ITEM_SCHEMA_H
