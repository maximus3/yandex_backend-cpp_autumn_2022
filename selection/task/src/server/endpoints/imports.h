#ifndef DISK_REST_API_ENDPOINTS_IMPORTS_H
#define DISK_REST_API_ENDPOINTS_IMPORTS_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StringTokenizer.h>
#include <Poco/URI.h>

#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

#include "pg_connection.h"

namespace endpoints {

    void handle_imports(Poco::Net::HTTPServerRequest& a_Request, Poco::Net::HTTPServerResponse& a_Response, json& a_JSON, Poco::StringTokenizer& a_Tokenizer, const std::shared_ptr<PGConnection>& a_PGConnection);

} // namespace endpoints

#endif //DISK_REST_API_ENDPOINTS_IMPORTS_H
