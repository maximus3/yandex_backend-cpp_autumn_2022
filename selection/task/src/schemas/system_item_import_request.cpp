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
}