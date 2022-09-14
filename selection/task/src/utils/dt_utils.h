#ifndef DISK_REST_API_UTILD_DT_UTILS_H
#define DISK_REST_API_UTILD_DT_UTILS_H

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

namespace utils {

    std::chrono::time_point<std::chrono::system_clock> iso_8601_to_datetime(const std::string& a_Date);

    std::string datetime_to_iso_8601(const std::chrono::time_point<std::chrono::system_clock>& a_Date);

}

#endif //DISK_REST_API_UTILD_DT_UTILS_H
