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

        // TODO: validate

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

    bool SystemItemSchema::database_save(std::shared_ptr<PGConnection> &a_PGConnection) const {
        return false;
    }

    std::vector<SystemItemSchema> SystemItemSchema::database_get(std::shared_ptr<PGConnection> &a_PGConnection, const std::string &field, const std::string &value) const {
        return {};
    }

}