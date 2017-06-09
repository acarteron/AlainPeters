#include "requests/handledata.hh"

HandleData::HandleData(){
}
void HandleData::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
  Poco::Util::Application& app = Poco::Util::Application::instance();
  app.logger().information("Request from " + request.clientAddress().toString());

  Poco::Net::HTMLForm form(request, request.stream()/*, partHandler*/);

  response.setChunkedTransferEncoding(true);
  response.setContentType("text/html");
  
  std::ostream& ostr = response.send();
  ostr << "This is it";
}
