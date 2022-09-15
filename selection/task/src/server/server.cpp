#include <iostream>
#include <string>
#include <optional>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/StringTokenizer.h>
#include <Poco/URI.h>
#include <Poco/NullStream.h>
#include <Poco/StreamCopier.h>

#include "json.hpp"

#include "server.h"

#include "endpoints/nodes.h"
#include "endpoints/imports.h"
#include "endpoints/delete.h"
#include "pg_backend.h"
#include "error_schema.h"

using json = nlohmann::json;


class RequestHandler : public Poco::Net::HTTPRequestHandler
{
private:
    std::shared_ptr<PGBackend> m_PGBackend;
    std::shared_ptr<PGConnection> m_PGConnection;
public:
    explicit RequestHandler(std::shared_ptr<PGBackend>& a_PGBackend)
        : Poco::Net::HTTPRequestHandler()
        , m_PGBackend(a_PGBackend) {}

    void handler(Poco::Net::HTTPServerRequest &a_Request, Poco::Net::HTTPServerResponse &a_Response, std::optional<json>& a_JSON) {
        Poco::URI uri(a_Request.getURI());
        std::string method = a_Request.getMethod();

        std::cerr << "URI: " << uri.toString() << std::endl;
        std::cerr << "Method: " << method << std::endl;

        Poco::StringTokenizer tokenizer(uri.getPath(), "/", Poco::StringTokenizer::TOK_TRIM);
        Poco::Net::HTMLForm form(a_Request, a_Request.stream());

        if (tokenizer.count() < 2) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            a_Response.send() << schemas::ErrorSchema("Not found", a_Response.getStatus());
            return;
        }

        std::string endpoint = tokenizer[1];

        if (endpoint == "imports") {
            if (method == "POST") {
                if (a_JSON.has_value()) {
                    return endpoints::handle_imports(a_Request, a_Response, a_JSON.value(), tokenizer, m_PGConnection);
                } else {
                    a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                    a_Response.send() << schemas::ErrorSchema("No JSON data", a_Response.getStatus());
                    a_Response.send().flush();
                    return;
                }
            }
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
            a_Response.send() << schemas::ErrorSchema("Method not allowed", a_Response.getStatus());
            a_Response.send().flush();
            return;
        }
        if (endpoint == "delete") {
            if (method == "DELETE") {
                return endpoints::handle_delete(a_Request, a_Response, tokenizer, m_PGConnection);
            }
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
            a_Response.send() << schemas::ErrorSchema("Method not allowed", a_Response.getStatus());
            a_Response.send().flush();
            return;
        }
        if (endpoint == "nodes") {
            if (method == "GET") {
                return endpoints::handle_nodes(a_Request, a_Response, tokenizer, m_PGConnection);
            }
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
            a_Response.send() << schemas::ErrorSchema("Method not allowed", a_Response.getStatus());
            a_Response.send().flush();
            return;
        }
        a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        a_Response.send() << schemas::ErrorSchema("Not found", a_Response.getStatus());
        a_Response.send().flush();
    }

    void handleRequest(Poco::Net::HTTPServerRequest& a_Request, Poco::Net::HTTPServerResponse& a_Response) override {
        a_Response.setContentType("application/json");

        std::string content_type = a_Request.getContentType();

        std::optional<json> json_data;
        if (content_type == "application/json") {
            try {
                json_data = json::parse(a_Request.stream());
            }
            catch (json::parse_error &exception) {
                // Make sure everything is read, otherwise this can result
                // in Bad Request error in the next call.
                Poco::NullOutputStream nos;
                Poco::StreamCopier::copyStream(a_Request.stream(), nos);

                a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                a_Response.send()
                        << schemas::ErrorSchema(&"JSON error occurred: "[*exception.what()], a_Response.getStatus());
                a_Response.send().flush();
                return;
            }
        }

        m_PGConnection = m_PGBackend->connection();
        try {
            handler(a_Request, a_Response, json_data);
        } catch (std::exception& exception) {
            a_Response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            a_Response.send() << schemas::ErrorSchema(&"Internal server error: "[*exception.what()], a_Response.getStatus());
            a_Response.send().flush();
        }
        m_PGBackend->freeConnection(m_PGConnection);

        a_Response.send().flush();
   }
};

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
private:
    std::shared_ptr<PGBackend> m_PGBackend;
public:
    explicit RequestHandlerFactory(std::shared_ptr<PGBackend>& a_PGBackend)
        : Poco::Net::HTTPRequestHandlerFactory()
        , m_PGBackend(a_PGBackend) {}
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest & request) override {
        return new RequestHandler(m_PGBackend);
    }
};

int App::main(const std::vector<std::string> &)
{
    auto* pParams = new Poco::Net::HTTPServerParams;

    pParams->setMaxQueued(100);
    pParams->setMaxThreads(16);

    auto pg_backend = std::make_shared<PGBackend>();

    Poco::Net::HTTPServer s(new RequestHandlerFactory(pg_backend), Poco::Net::ServerSocket(8000), pParams);

    s.start();
    std::cerr << "Server started" << std::endl;

    waitForTerminationRequest();  // wait for CTRL-C or kill

    std::cerr << "Shutting down..." << std::endl;
    s.stop();

    return Application::EXIT_OK;
}