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
        virtual json to_json() = 0;
        virtual std::string to_string() = 0;

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
