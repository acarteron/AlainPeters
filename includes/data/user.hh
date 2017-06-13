#ifndef USER_HH
#define USER_HH

#include <string>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Array.h>
#include "data/rule.hh"
namespace apeters{
class User{
  Poco::JSON::Object::Ptr user_obj=new Poco::JSON::Object();
  std::string date;
  std::string user;
  std::map<std::string,Poco::JSON::Object::Ptr> priorities;
public:
  void set_user(std::string);
  void set_date(std::string);
  void addrules(std::string,std::string,std::vector<std::string>);
  Poco::JSON::Object::Ptr getAll();
};
}
#endif // USER_HH
