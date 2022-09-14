#include "nodes.h"

namespace endpoints {

    void handle_nodes(Poco::Net::HTTPServerRequest& a_Request, Poco::Net::HTTPServerResponse& a_Response, json& a_JSON, Poco::StringTokenizer& a_Tokenizer, std::shared_ptr<PGConnection> a_PGConnection) {
        a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        a_Response.send() << schemas::ErrorSchema("TODO nodes", a_Response.getStatus());  // TODO
    }

} // namespace endpoints