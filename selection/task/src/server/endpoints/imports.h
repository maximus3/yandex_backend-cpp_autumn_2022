#ifndef DISK_REST_API_ENDPOINTS_IMPORTS_H
#define DISK_REST_API_ENDPOINTS_IMPORTS_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StringTokenizer.h>
#include <Poco/URI.h>

#include <iostream>

#include "../../schemas/error_schema.h"

namespace endpoints {

    void handle_imports(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp, Poco::StringTokenizer& tokenizer);

} // namespace endpoints

#endif //DISK_REST_API_ENDPOINTS_IMPORTS_H
