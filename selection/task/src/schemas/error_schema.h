#ifndef DISK_REST_API_SCHEMAS_ERROR_SCHEMA_H
#define DISK_REST_API_SCHEMAS_ERROR_SCHEMA_H

#include <string>
#include "json.hpp"

using json = nlohmann::json;

#include "base_schema.h"

namespace schemas {

    class ErrorSchema : public BaseSchema {
    public:
        const std::string message;
        const int code;

        ErrorSchema(std::string message, int code) : message(std::move(message)), code(code) {}

        json to_json() override {
            json j;
            j["message"] = message;
            j["code"] = code;
            return j;
        }

        std::string to_string() override {
            return to_json().dump();
        }
    };

}

#endif //DISK_REST_API_SCHEMAS_ERROR_SCHEMA_H
