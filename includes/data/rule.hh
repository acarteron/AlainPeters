#ifndef RULE_HH
#define RULE_HH

#include <string>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Array.h>
#include "data/rule_instance.hh"
#include <algorithm>

class Rule{
  Poco::JSON::Object::Ptr rules_obj=new Poco::JSON::Object();
  Poco::JSON::Array::Ptr  rules_inst_array=new Poco::JSON::Array();
  unsigned int size=0;
  std::string name;
  std::vector<Rule_Instance> rules_inst;
public:
  void set_streams(std::string ,std::vector<std::string> );
  Poco::JSON::Array::Ptr get_rules_array();
  Poco::JSON::Object::Ptr get_rules_object();
  std::string to_string();
};



#endif
