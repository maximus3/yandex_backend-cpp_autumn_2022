#include <ctime>
#include <stdexcept>

#include "validators.h"
#include "dt_utils.h"

namespace utils::validators {

    void date_must_be_iso_8601(const std::string &a_Date) {
        try {
            const auto date = utils::iso_8601_to_datetime(a_Date);
        } catch (const std::invalid_argument &e) {
            throw std::invalid_argument("Date must be in ISO 8601 format");
        }
    }

}