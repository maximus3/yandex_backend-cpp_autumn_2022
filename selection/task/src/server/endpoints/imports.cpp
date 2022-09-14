#include "imports.h"

namespace endpoints {

    void handle_imports(Poco::Net::HTTPServerRequest& a_Request, Poco::Net::HTTPServerResponse& a_Response, json& a_JSON, Poco::StringTokenizer& a_Tokenizer, const std::shared_ptr<PGConnection>& a_PGConnection) {

        std::cerr << to_string(a_JSON) << std::endl;

        std::cerr << a_JSON.at("items") << std::endl;
        std::cerr << a_JSON.at("updateDate") << std::endl;
        std::cerr << a_JSON.at("lol") << std::endl;

        a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_CONFLICT);
        a_Response.send() << schemas::ErrorSchema("TODO imports", a_Response.getStatus());  // TODO
    }

} // namespace endpoints