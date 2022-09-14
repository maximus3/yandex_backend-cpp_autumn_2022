#ifndef DISK_REST_API_SCHEMAS_VALIDATORS_H
#define DISK_REST_API_SCHEMAS_VALIDATORS_H

#include <string>
#include <optional>

#include "system_item_type.h"

namespace utils::validators {

    void date_must_be_iso_8601(const std::string& a_Date);

    void validate_size(const std::optional<int64_t>& a_Size, const schemas::SystemItemType& a_Type);

}

#endif //DISK_REST_API_SCHEMAS_VALIDATORS_H
