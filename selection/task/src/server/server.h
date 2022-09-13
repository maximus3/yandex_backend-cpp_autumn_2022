#ifndef DISK_REST_API_SERVER_H
#define DISK_REST_API_SERVER_H

#include <string>
#include <vector>
#include <Poco/Util/ServerApplication.h>

class App : public Poco::Util::ServerApplication
{
    protected:
        int main(const std::vector<std::string> &);
};

#endif //DISK_REST_API_SERVER_H