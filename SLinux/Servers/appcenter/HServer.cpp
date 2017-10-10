#include "stdafx.h"
#include "HServer.h"

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"

#include "Poco/File.h"
#include "Poco/ErrorHandler.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/CountingStream.h"
#include "Poco/NullStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/URI.h"

class MyPartHandler : public Poco::Net::PartHandler
{
public:
    MyPartHandler() :
        _length(0)
    {
    }

    void handlePart(const MessageHeader& header, std::istream& stream)
    {
        _type = header.get("Content-Type", "(unspecified)");
        if (header.has("Content-Disposition"))
        {
            std::string disp;
            NameValueCollection params;
            MessageHeader::splitParameters(header["Content-Disposition"], disp, params);
            _name = params.get("name", "(unnamed)");
            _fileName = params.get("filename", "(unnamed)");
        }

        CountingInputStream istr(stream);
        NullOutputStream ostr;
        StreamCopier::copyStream(istr, ostr);
        _length = istr.chars();
    }

    int length() const
    {
        return _length;
    }

    const std::string& name() const
    {
        return _name;
    }

    const std::string& fileName() const
    {
        return _fileName;
    }

    const std::string& contentType() const
    {
        return _type;
    }

private:
    int _length;
    std::string _type;
    std::string _name;
    std::string _fileName;
};


enum VisitType
{
    GM = 0,
    PM = 1,
    Other = 2,
};

class FormRequestHandler : public HTTPRequestHandler
/// Return a HTML document with the current date and time.
{
public:
    FormRequestHandler()
    {
    }

    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
    {
        //Application& app = Application::instance();
        //app.logger().information("Request from " + request.clientAddress().toString());

        MyPartHandler partHandler;
        HTMLForm form(request, request.stream(), partHandler);

        response.setChunkedTransferEncoding(true);
        response.setContentType("text/html");

        std::ostream& ostr = response.send();

        /*ostr <<
             "<html>\n"
             "<head>\n"
             "<title>POCO Form Server Sample</title>\n"
             "</head>\n"
             "<body>\n"
             "<h1>POCO Form Server Sample</h1>\n"
             "<h2>GET Form</h2>\n"
             "<form method=\"GET\" action=\"/form\">\n"
             "<input type=\"text\" name=\"text\" size=\"31\">\n"
             "<input type=\"submit\" value=\"GET\">\n"
             "</form>\n"
             "<h2>POST Form</h2>\n"
             "<form method=\"POST\" action=\"/form\">\n"
             "<input type=\"text\" name=\"text\" size=\"31\">\n"
             "<input type=\"submit\" value=\"POST\">\n"
             "</form>\n"
             "<h2>File Upload</h2>\n"
             "<form method=\"POST\" action=\"/form\" enctype=\"multipart/form-data\">\n"
             "<input type=\"file\" name=\"file\" size=\"31\"> \n"
             "<input type=\"submit\" value=\"Upload\">\n"
             "</form>\n";*/

        //ostr << "<h2>Request</h2><p>\n";
        //ostr << "Method: " << request.getMethod() << "<br>\n";
        //ostr << "URI: " << request.getURI() << "<br>\n";
        //NameValueCollection::ConstIterator it = request.begin();
        //NameValueCollection::ConstIterator end = request.end();
        //for (; it != end; ++it)
        //{
        //    ostr << it->first << ": " << it->second << "<br>\n";
        //}
        //ostr << "</p>";

        if (!form.empty())
        {
            if (form.has("type"))
            {
                auto strType = form.get("type");
                VisitType type =(VisitType) atoi(strType.c_str());
                switch (type)
                {
                case GM:
                    break;
                case PM:
                    break;
                case Other:
                    break;
                default:
                    break;
                }
            }
            ostr << "<h2>Form</h2><p>\n";
            for (auto it = form.begin(); it != form.end(); ++it)
            {
                ostr << it->first << ": " << it->second << "<br>\n";
            }
            ostr << "</p>";
        }
        ostr << "</body>\n";
    }
};

class NotFileHandler : public Poco::Net::HTTPRequestHandler
{
public:

    void handleRequest(Poco::Net::HTTPServerRequest& request,
                       Poco::Net::HTTPServerResponse& response)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        response.setContentType("text/html");

        std::ostream& ostr = response.send();
        ostr << "<html><head>";
        ostr << "<title>FF</title>";
        ostr << "</head><body>Welcome To Come FF!<br />";
        ostr << "</body></html>";
    }
};

class FileRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:

    void handleRequest(Poco::Net::HTTPServerRequest& request,
                       Poco::Net::HTTPServerResponse& response)
    {
        try
        {
            std::string fpass = ".";
            fpass += request.getURI();

            response.sendFile(fpass, "text/html");
        }
        catch (Poco::Exception&)
        {
        }
    }
};

class MiniRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:

    Poco::Net::HTTPRequestHandler*
    createRequestHandler(const Poco::Net::HTTPServerRequest& request)
    {
        auto strUri = request.getURI();
        URI uri(strUri);
        auto query = uri.getQuery();
        auto path = uri.getPath();
        if (!query.empty())
            return new FormRequestHandler();

        std::string fpass = ".";
        fpass += request.getURI();

        Poco::File f(fpass);
        if (!f.exists() || !f.isFile())
            return new NotFileHandler();

        return new FileRequestHandler();
    }
};


HServer::HServer()
    :server_(nullptr)
    , port_(9980)
{

}

HServer::~HServer()
{
    if (server_)
    {
        server_->stop();
        dSafeDelete(server_);
    }
}
class MyErrorHandler :public ErrorHandler
{
public :
    HServer* httpServer;
public:
    virtual void exception(const Exception& exc) override
    {
        if (exc.className() == typeid(PathSyntaxException).name())
        {

        }
    }
    virtual void exception(const std::exception& exc) override
    {
    }

} errorHanlder_;

void HServer::Start()
{
    int maxThreads = 1;
    Poco::ThreadPool::defaultPool().addCapacity(maxThreads);
    Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;
    pParams->setMaxQueued(100);
    pParams->setMaxThreads(maxThreads);
    Poco::Net::ServerSocket socket(port_);
    server_ = new Poco::Net::HTTPServer(new MiniRequestHandlerFactory(), socket, pParams);

    errorHanlder_.httpServer = this;
    ErrorHandler::set(&errorHanlder_);
    try
    {
        server_->start();
    }
    catch (Exception exc)
    {
        printf(exc.what());
    }
}
