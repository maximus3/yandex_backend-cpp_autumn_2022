#pragma once

#include <string>
#include <vector>
#include <Poco/Util/ServerApplication.h>

class App : public Poco::Util::ServerApplication
{
    protected:
        int main(const std::vector<std::string> &);
};