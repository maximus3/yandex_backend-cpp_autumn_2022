#ifndef DISK_REST_API_SCHEMAS_BASE_SCHEMA_H
#define DISK_REST_API_SCHEMAS_BASE_SCHEMA_H

#include <string>

namespace schemas
{
    class BaseSchema
    {
    public:
        virtual std::string to_json() = 0;
    };
}

#endif //DISK_REST_API_SCHEMAS_BASE_SCHEMA_H
