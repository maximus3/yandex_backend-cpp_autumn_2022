#ifndef DISK_REST_API_SCHEMAS_SYSTEM_ITEM_IMPORT_REQUEST_H
#define DISK_REST_API_SCHEMAS_SYSTEM_ITEM_IMPORT_REQUEST_H

#include <string>
#include <optional>
#include <vector>

#include "json.hpp"

using json = nlohmann::json;

#include "base_schema.h"
#include "system_item_import_schema.h"

namespace schemas {

    class SystemItemImportRequest : public BaseSchema {
    public:
        const std::vector<SystemItemImportSchema> items;
        const std::string updateDate;

        SystemItemImportRequest(
                std::vector<SystemItemImportSchema> items,
                std::string updateDate
        )
                : items(std::move(items))
                , updateDate(std::move(updateDate)) {}

        json to_json() const override {
            json j;
            j["items"] = json::array();
            for (const auto &item : items) {
                j["items"].push_back(item.to_json());
            }
            j["updateDate"] = updateDate;
            return j;
        }

        static SystemItemImportRequest from_json(const json& j) {
            const std::vector<std::string>& available_fields = {
                    "items",
                    "updateDate"
            };
            validate_fields(j, available_fields);

            auto _items = std::vector<SystemItemImportSchema>();
            for (const auto &item : j.at("items")) {
                _items.push_back(SystemItemImportSchema::from_json(item));
            }
            auto _updateDate = j.at("updateDate").get<std::string>();

            // TODO: validate

            return {
                    std::move(_items),
                    std::move(_updateDate)
            };
        }
    };
}

#endif //DISK_REST_API_SCHEMAS_SYSTEM_ITEM_IMPORT_REQUEST_H
