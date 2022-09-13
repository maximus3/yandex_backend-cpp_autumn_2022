#ifndef DISK_REST_API_PG_BACKEND_H
#define DISK_REST_API_PG_BACKEND_H

#include <memory>
#include <mutex>
#include <string>
#include <queue>
#include <condition_variable>
#include <libpq-fe.h>
#include "pg_connection.h"


class PGBackend
{
public:
    PGBackend();
    std::shared_ptr<PGConnection> connection();
    void freeConnection(std::shared_ptr<PGConnection>);

private:
    void createPool();

    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::queue<std::shared_ptr<PGConnection>> m_pool;

    const int POOL = 10;
};

#endif //DISK_REST_API_PG_BACKEND_H
