/**
 * \class requesthandlerfactory
 *
 * \brief 
 *
 * \note 
 *
 * \author Adrien Carteron
 *
 * \version 0.1 
 *
 * \date lun. mai 29 11:04:13 CEST 2017 
 *
 * Contact: acarteron@openmailbox.org
 *
 * Created on: lun. mai 29 11:04:13 CEST 2017
 *
 *
 */

#ifndef REQUESTHANDLERFACTORY_HH
#define REQUESTHANDLERFACTORY_HH

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequestImpl.h>
#include <Poco/Util/ServerApplication.h>

class RequestHandlerFactory:public Poco::Net::HTTPRequestHandlerFactory{
private:
  void poco_log(std::string);
  Poco::Net::HTTPRequestHandler* switch_Method(std::string);
  
  
public:
  RequestHandlerFactory();
  Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

};
#endif // REQUESTHANDLERFACTORY_HH
