#ifndef RULE_INSTANCE_HH
#define RULE_INSTANCE_HH

#include <string>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Array.h>
#include "data/role.hh"

class Rule_Instance{
private:
  std::string timestamp;
  std::vector<Role> roles;
  Poco::JSON::Object::Ptr rule_instance_obj=new Poco::JSON::Object();
public:
  //~Rule_Instance(){roles.clear();}
  std::vector<Role> getRoles();
  void set_timestamp(std::string);

  bool operator==(const Rule_Instance& ) const;
  bool operator<(const Rule_Instance& )const;
  void set_roles(std::string ,std::vector<std::string> );
  Poco::JSON::Object::Ptr get_rule_instance_obj();
  std::string to_string();
};

#endif // RULE_INSTANCE_HH
