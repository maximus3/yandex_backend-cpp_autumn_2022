#ifndef DISK_REST_API_SCHEMAS_ERROR_SCHEMA_H
#define DISK_REST_API_SCHEMAS_ERROR_SCHEMA_H

#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

#include "base_schema.h"

namespace schemas {

    class ErrorSchema : public BaseSchema {
    private:
        static std::vector<std::string> m_AvailableFields;
    public:
        const std::string message;
        const int code;

        ErrorSchema(std::string message, int code) : message(std::move(message)), code(code) {}

        json to_json() const override  {
            json j;
            j["message"] = message;
            j["code"] = code;
            return j;
        }

        static ErrorSchema from_json(const json &j) {
            m_AvailableFields = {"message", "code"};
            validate_fields(j);
            return {
                    j.at("message").get<std::string>(),
                    j.at("code").get<int>()
            };
        }
    };
}

#endif //DISK_REST_API_SCHEMAS_ERROR_SCHEMA_H
