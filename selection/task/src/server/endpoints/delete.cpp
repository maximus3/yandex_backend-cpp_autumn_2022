#include "delete.h"
#include "error_schema.h"
#include "system_item_schema.h"

namespace endpoints {

    void handle_delete(Poco::Net::HTTPServerRequest& a_Request, Poco::Net::HTTPServerResponse& a_Response, Poco::StringTokenizer& a_Tokenizer, std::shared_ptr<PGConnection> a_PGConnection) {
        if (a_Tokenizer.count() < 2) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            a_Response.send() << schemas::ErrorSchema("Missing id", a_Response.getStatus());
            return;
        }
        auto id = a_Tokenizer[2];
        std::stringstream _statusStream;
        std::optional<schemas::SystemItemSchema> systemItem;
        auto status = schemas::SystemItemSchema::database_get(a_PGConnection, _statusStream, systemItem, "id", id);
        if (status == database::Status::OK) {
            if (!systemItem.has_value()) {
                a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                a_Response.send() << schemas::ErrorSchema("Not found", a_Response.getStatus());
                return;
            }
            status = systemItem->database_delete(a_PGConnection, _statusStream);
        }
        if (status == database::Status::OK) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            a_Response.send() << "{}";
            return;
        }
        if (status == database::Status::VALIDATION_ERROR) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
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