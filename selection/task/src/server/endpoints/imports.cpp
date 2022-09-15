#include <optional>

#include "imports.h"
#include "system_item_import_request.h"
#include "error_schema.h"

namespace endpoints {

    void handle_imports(Poco::Net::HTTPServerRequest& a_Request, Poco::Net::HTTPServerResponse& a_Response, json& a_JSON, Poco::StringTokenizer& a_Tokenizer, const std::shared_ptr<PGConnection>& a_PGConnection) {

        std::cerr << "Contest: " << to_string(a_JSON) << std::endl;

        std::optional<schemas::SystemItemImportRequest> importRequest = std::nullopt;
        try {
            importRequest.emplace(schemas::SystemItemImportRequest::from_json(a_JSON));
        } catch (json::out_of_range& e) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            a_Response.send() << schemas::ErrorSchema(e.what(), a_Response.getStatus());
            return;
        } catch (json::type_error & e) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            a_Response.send() << schemas::ErrorSchema(e.what(), a_Response.getStatus());
            return;
        } catch (std::invalid_argument& e) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            a_Response.send() << schemas::ErrorSchema(e.what(), a_Response.getStatus());
            return;
        } catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            a_Response.send() << schemas::ErrorSchema(e.what(), a_Response.getStatus());
            return;
        }

        std::stringstream _statusStream;
        auto status = importRequest->database_save(a_PGConnection, _statusStream);

        if (status == database::Status::OK) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            a_Response.send() << "{}";
            return;
        }
        if (status == database::Status::VALIDATION_ERROR) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            a_Response.send() << schemas::ErrorSchema(_statusStream.str(), a_Response.getStatus());
            return;
        }
        if (status == database::Status::DATABASE_ERROR) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            a_Response.send() << schemas::ErrorSchema(_statusStream.str(), a_Response.getStatus());
            return;
        }

        a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        a_Response.send() << schemas::ErrorSchema("Unknown error", a_Response.getStatus());
    }

} // namespace endpoints