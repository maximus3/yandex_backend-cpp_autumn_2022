#ifndef DISK_REST_API_SCHEMAS_SYSTEM_ITEM_TYPE_H
#define DISK_REST_API_SCHEMAS_SYSTEM_ITEM_TYPE_H

#include <string>
#include <stdexcept>

namespace schemas {
    enum class SystemItemType {
        FILE,
        FOLDER
    };

    inline std::string to_string(SystemItemType system_item) {
        switch (system_item) {
            case SystemItemType::FILE:
                return "FILE";
            case SystemItemType::FOLDER:
                return "FOLDER";
            default:
                throw std::runtime_error("Unknown SystemItemType");
        }
    }

    inline SystemItemType to_system_item(const std::string& system_item) {
        if (system_item == "FILE") {
            return SystemItemType::FILE;
        } else if (system_item == "FOLDER") {
            return SystemItemType::FOLDER;
        } else {
            throw std::invalid_argument("Invalid system item: " + system_item);
        }
    }
}

#endif //DISK_REST_API_SCHEMAS_SYSTEM_ITEM_TYPE_H
