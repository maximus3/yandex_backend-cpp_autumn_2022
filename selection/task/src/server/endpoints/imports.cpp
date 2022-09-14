#include "imports.h"

namespace endpoints {

    void handle_imports(Poco::Net::HTTPServerRequest& a_Request, Poco::Net::HTTPServerResponse& a_Response, Poco::StringTokenizer& a_Tokenizer, std::shared_ptr<PGConnection> a_PGConnection) {
        //Poco::Net::HTMLForm form(req,req.stream());

        a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        a_Response.send() << schemas::ErrorSchema("TODO imports", a_Response.getStatus()).to_json();  // TODO
    }

} // namespace endpoints