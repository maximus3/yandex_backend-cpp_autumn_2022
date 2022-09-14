#ifndef DISK_REST_API_SCHEMAS_BASE_SCHEMA_H
#define DISK_REST_API_SCHEMAS_BASE_SCHEMA_H

#include <string>
#include "json.hpp"

using json = nlohmann::json;

namespace schemas
{
    class BaseSchema
    {
    public:
        BaseSchema() = default;
        virtual json to_json() const = 0;

        std::string to_string() const {
            return to_json().dump();
        }

        static void validate_fields(const json& j, const std::vector<std::string>& a_AvailableFields) {
            for (auto& [key, value] : j.items()) {
                if (std::find(a_AvailableFields.begin(), a_AvailableFields.end(), key) == a_AvailableFields.end()) {
                    throw std::invalid_argument("key '" + key + "' not found in schema");
                }
            }
        }

        friend std::ostream& operator<<(std::ostream& os, schemas::BaseSchema& schema)
        {
            os << schema.to_string();
            return os;
        }

        friend std::ostream& operator<<(std::ostream& os, schemas::BaseSchema&& schema)
        {
            os << schema.to_string();
            return os;
        }
    };
}

#endif //DISK_REST_API_SCHEMAS_BASE_SCHEMA_H
