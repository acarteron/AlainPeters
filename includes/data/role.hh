#ifndef ROLE_HH
#define ROLE_HH

#include <string>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Array.h>

class Role {
private:
  Poco::JSON::Object::Ptr role_obj=new Poco::JSON::Object();
  std::string location="";
  std::string kind="";
public:
  std::string getLocation()const ;
  std::string getKind()const ;
  void define_role(std::string);
  std::string to_string();
  Poco::JSON::Object::Ptr get_role_obj();
};

#endif // ROLE_HH
