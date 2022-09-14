#ifndef DISK_REST_API_SCHEMAS_BASE_SCHEMA_H
#define DISK_REST_API_SCHEMAS_BASE_SCHEMA_H

#include <string>
#include "json.hpp"

using json = nlohmann::json;

namespace schemas
{
    class BaseSchema
    {
    private:
        static std::vector<std::string> m_AvailableFields;
    public:
        BaseSchema() = default;
        virtual json to_json() const = 0;

        std::string to_string() const {
            return to_json().dump();
        }

        static void validate_fields(const json& j) {
            for (auto& [key, value] : j.items()) {
                if (std::find(m_AvailableFields.begin(), m_AvailableFields.end(), key) == m_AvailableFields.end()) {
                    throw std::invalid_argument("Unknown field: " + key);
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
