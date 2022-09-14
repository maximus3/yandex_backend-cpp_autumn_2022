#include "system_item_import_schema.h"
#include "validators.h"

namespace schemas {

    SystemItemImportSchema SystemItemImportSchema::from_json(const json& j) {
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

        utils::validators::validate_size(_size, _type);
        // TODO: validate

        return {
                std::move(_id),
                std::move(_url),
                std::move(_parentId),
                _type,
                _size
        };
    }

}