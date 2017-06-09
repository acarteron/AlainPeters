#include "requests/requesthandlerfactory.hh"
#include "requests/handleget.hh"

#include <iostream>

RequestHandlerFactory::RequestHandlerFactory(){
}

Poco::Net::HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
  //poco_log("Request method : "+request.getMethod()+", uri : "+request.getURI());
  return switch_Method(request.getMethod());  
}
void RequestHandlerFactory::poco_log(std::string log_){
  Poco::Util::Application& app = Poco::Util::Application::instance();
  app.logger().information(log_);
}
Poco::Net::HTTPRequestHandler* RequestHandlerFactory::switch_Method(std::string method_){
  if(method_.compare("POST")==0){
    return NULL;
  }else{
    if(method_.compare("GET")==0){
      return new HandleGet;
    }else{
      if(method_.compare("PUT")==0){
	return NULL;
      }else{
	if(method_.compare("DELETE")==0){
	  return NULL;
	}else{
	  return NULL;
	}
      }
    }
  }
}
