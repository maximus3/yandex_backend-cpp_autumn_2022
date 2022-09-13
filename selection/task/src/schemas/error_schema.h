#ifndef DISK_REST_API_SCHEMAS_ERROR_SCHEMA_H
#define DISK_REST_API_SCHEMAS_ERROR_SCHEMA_H

#include <string>

#include "base_schema.h"

namespace schemas {

    class ErrorSchema : BaseSchema {
    public:
        const std::string message;
        const int code;

        ErrorSchema(std::string message, int code) : message(std::move(message)), code(code) {}

        std::string to_json() override {
            return R"({"message": ")" + message + R"(", "code": )" + std::to_string(code) + "}";
        }
    };

}

#endif //DISK_REST_API_SCHEMAS_ERROR_SCHEMA_H
