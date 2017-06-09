/**
 * \class handledata
 *
 * \brief 
 *
 * \note 
 *
 * \author Adrien Carteron
 *
 * \version 0.1 
 *
 * \date lun. mai 29 14:58:07 CEST 2017 
 *
 * Contact: acarteron@openmailbox.org
 *
 * Created on: lun. mai 29 14:58:07 CEST 2017
 *
 *
 */

#ifndef HANDLEDATA_HH
#define HANDLEDATA_HH

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Util/ServerApplication.h>

class HandleData: public Poco::Net::HTTPRequestHandler{

private:

public:
  /** \brief Void constructor
   * 
   * add desc 
   * 
   */
  HandleData();

  void handleRequest(Poco::Net::HTTPServerRequest& , Poco::Net::HTTPServerResponse& );

};

#endif // HANDLEDATA_HH
