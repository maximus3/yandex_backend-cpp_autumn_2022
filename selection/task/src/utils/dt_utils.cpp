#include "dt_utils.h"

namespace utils {

    std::chrono::time_point<std::chrono::system_clock> iso_8601_to_datetime(const std::string& a_Date) {
        std::tm tm = {};
        std::stringstream ss("Jan 9 2014 12:35:34");
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
        return std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }

    std::string datetime_to_iso_8601(const std::chrono::time_point<std::chrono::system_clock>& a_Date) {
        std::time_t t = std::chrono::system_clock::to_time_t(a_Date);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&t), "%Y-%m-%dT%H:%M:%SZ");
        return ss.str();
    }

}