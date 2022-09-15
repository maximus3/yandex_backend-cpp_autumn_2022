#include "nodes.h"
#include "error_schema.h"
#include "system_item_schema.h"

namespace endpoints {

    void handle_nodes(Poco::Net::HTTPServerRequest& a_Request, Poco::Net::HTTPServerResponse& a_Response, Poco::StringTokenizer& a_Tokenizer, std::shared_ptr<PGConnection> a_PGConnection) {
        if (a_Tokenizer.count() < 2) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            a_Response.send() << schemas::ErrorSchema("Missing id", a_Response.getStatus());
            return;
        }
        auto id = a_Tokenizer[2];
        std::cerr << "ID: " << id << std::endl;
        std::stringstream _statusStream;
        std::optional<schemas::SystemItemSchema> systemItem;
        database::Status status;
        try {
            status = schemas::SystemItemSchema::database_get(a_PGConnection, _statusStream, systemItem, "id", id);
        } catch (const std::exception& e) {
            std::cerr << __FILE__ << ":" << __LINE__ << " EXCEPTION: " << e.what() << std::endl;
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            a_Response.send() << schemas::ErrorSchema(e.what(), a_Response.getStatus());
            return;
        }
        std::cerr << __FILE__ << ":" << __LINE__ << " Status: " << _statusStream.str() << std::endl;
        std::cerr << __FILE__ << ":" << __LINE__ << " database::Status: " << int(status) << std::endl;
        std::cerr << __FILE__ << ":" << __LINE__ << " systemItem.has_value(): " << systemItem.has_value() << std::endl;
        if (status == database::Status::OK) {
            std::cerr << __FILE__ << ":" << __LINE__ << " database::Status::OK" << std::endl;
            if (systemItem.has_value()) {
                std::cerr << __FILE__ << ":" << __LINE__ << " systemItem.has_value()" << std::endl;
                a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                std::cerr << __FILE__ << ":" << __LINE__ << " setStatus OK" << std::endl;
                std::cerr << "Sending response: " << systemItem->to_string() << std::endl;
                try {
                    a_Response.send() << systemItem.value().to_json();
                } catch (const std::exception& e) {
                    std::cerr << __FILE__ << ":" << __LINE__ << " EXCEPTION: " << e.what() << std::endl;
                    a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
                    a_Response.send() << schemas::ErrorSchema(e.what(), a_Response.getStatus());
                    return;
                }
                return;
            }
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            a_Response.send() << schemas::ErrorSchema("Not found", a_Response.getStatus());
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