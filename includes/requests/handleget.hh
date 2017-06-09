/**
 * \class requests/handleget
 *
 * \brief 
 *
 * \note 
 *
 * \author Adrien Carteron
 *
 * \version 0.1 
 *
 * \date mar. mai 30 09:58:55 CEST 2017 
 *
 * Contact: acarteron@openmailbox.org
 *
 * Created on: mar. mai 30 09:58:55 CEST 2017
 *
 *
 */

#ifndef HANDLEGET_HH
#define HANDLEGET_HH

#include <utility>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Util/ServerApplication.h>

class HandleGet: public Poco::Net::HTTPRequestHandler{

private:
  void poco_log(std::string);
  std::pair<std::string,std::string> switch_URI(Poco::Net::HTTPServerRequest& );
  std::string mongo_host="localhost";
  int mongo_port=27017;

  std::string main_page();
  std::pair<std::string,std::string> get_file(const std::string&);

  std::string get_streams_rules_collection(std::vector<std::string>);
  std::string get_rules_list_collection(std::string);
  std::string get_streams_collection(std::string);
  std::string get_all_batteries_of_collection(std::string);

public:
  /** \brief Void constructor
   * 
   * add desc 
   * 
   */
  HandleGet();

  void handleRequest(Poco::Net::HTTPServerRequest& , Poco::Net::HTTPServerResponse& );

};

#endif // HANDLEGET_HH
