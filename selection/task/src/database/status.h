#ifndef DISK_REST_API_DATABASE_STATUS_H
#define DISK_REST_API_DATABASE_STATUS_H

namespace database {

        enum class Status {
            OK,
            VALIDATION_ERROR,
            DATABASE_ERROR
        };
}

#endif //DISK_REST_API_DATABASE_STATUS_H
