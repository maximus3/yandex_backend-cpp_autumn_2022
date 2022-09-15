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

    void validate_size(const std::optional<int64_t>& a_Size, const schemas::SystemItemType& a_Type) {
        if (a_Type == schemas::SystemItemType::FILE) {
            if (!a_Size.has_value()) {
                throw std::invalid_argument("Size must be specified for files");
            }
            if (a_Size.value() <= 0) {
                throw std::invalid_argument("Size must be greater than 0");
            }
        } else {
            if (a_Size.has_value()) {
                throw std::invalid_argument("Size must not be specified for directories");
            }
        }
    }

    void validate_url(const std::optional<std::string>& a_Url, const schemas::SystemItemType& a_Type) {
        if (a_Type == schemas::SystemItemType::FILE) {
            if (!a_Url.has_value()) {
                throw std::invalid_argument("Url must be specified for files");
            }
            if (a_Url.value().size() > 255) {
                throw std::invalid_argument("Url must be less equal than 255 characters");
            }
        } else {
            if (a_Url.has_value()) {
                throw std::invalid_argument("Url must not be specified for directories");
            }
        }
    }

}