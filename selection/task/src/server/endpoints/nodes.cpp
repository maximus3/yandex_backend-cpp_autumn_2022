#include "nodes.h"

namespace endpoints {

    void handle_nodes(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp, Poco::StringTokenizer& tokenizer) {
        //Poco::Net::HTMLForm form(req,req.stream());

        resp.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        resp.send() << schemas::ErrorSchema("TODO", resp.getStatus()).to_json();  // TODO
    }

} // namespace endpoints