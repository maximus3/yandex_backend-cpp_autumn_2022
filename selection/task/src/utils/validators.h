#ifndef DISK_REST_API_SCHEMAS_VALIDATORS_H
#define DISK_REST_API_SCHEMAS_VALIDATORS_H

#include <string>

namespace utils::validators {

    void date_must_be_iso_8601(const std::string& a_Date);

}

#endif //DISK_REST_API_SCHEMAS_VALIDATORS_H
