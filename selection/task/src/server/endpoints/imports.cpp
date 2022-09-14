#include "imports.h"
#include "../../schemas/system_item_import_request.h"

namespace endpoints {

    void handle_imports(Poco::Net::HTTPServerRequest& a_Request, Poco::Net::HTTPServerResponse& a_Response, json& a_JSON, Poco::StringTokenizer& a_Tokenizer, const std::shared_ptr<PGConnection>& a_PGConnection) {

        std::cerr << to_string(a_JSON) << std::endl;

        try {
            schemas::SystemItemImportRequest importRequest = schemas::SystemItemImportRequest::from_json(a_JSON);
        } catch (json::out_of_range& e) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            a_Response.send() << schemas::ErrorSchema(e.what(), a_Response.getStatus());
            return;
        } catch (std::invalid_argument& e) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            a_Response.send() << schemas::ErrorSchema(e.what(), a_Response.getStatus());
            return;
        } catch (std::exception& e) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            a_Response.send() << schemas::ErrorSchema(e.what(), a_Response.getStatus());
            return;
        }

        a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        a_Response.send() << schemas::ErrorSchema("TODO imports", a_Response.getStatus());  // TODO
    }

} // namespace endpoints