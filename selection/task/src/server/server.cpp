#include <iostream>
#include <string>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/StringTokenizer.h>
#include <Poco/URI.h>

#include "server.h"


class RequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
    {
        Poco::URI uri(req.getURI());
        std::string method = req.getMethod();

        std::cerr << "URI: " << uri.toString() << std::endl;
        std::cerr << "Method: " << req.getMethod() << std::endl;

        Poco::StringTokenizer tokenizer(uri.getPath(), "/", Poco::StringTokenizer::TOK_TRIM);
        Poco::Net::HTMLForm form(req,req.stream());

        if(!method.compare("POST"))
        {
            std::cerr << "POST" << std::endl;
        }
        else if(!method.compare("PUT"))
        {
            std::cerr << "PUT" << std::endl;
        }
        else if(!method.compare("DELETE"))
        {
            std::cerr << "DELETE" << std::endl;
        }

        resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        resp.setContentType("application/json");
        std::ostream& out = resp.send();

        out << "{hello:heh}" << std::endl;

        out.flush();
    }
};

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    virtual Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest & request)
    {
        return new RequestHandler;
    }
};

int App::main(const std::vector<std::string> &)
{
    Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;

    pParams->setMaxQueued(100);
    pParams->setMaxThreads(16);

    Poco::Net::HTTPServer s(new RequestHandlerFactory, Poco::Net::ServerSocket(8000), pParams);

    s.start();
    std::cerr << "Server started" << std::endl;

    waitForTerminationRequest();  // wait for CTRL-C or kill

    std::cerr << "Shutting down..." << std::endl;
    s.stop();

    return Application::EXIT_OK;
}