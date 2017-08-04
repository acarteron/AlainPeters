#ifndef RULE_HH
#define RULE_HH

#include <string>
#include "data/rule_instance.hh"
#include <algorithm>
namespace apeters{
  class Rule{
    nlohmann::json rules_obj;
    //nlohmann::json rules_inst_array;
    unsigned int size=0;
    std::string name;
    std::vector<Rule_Instance> rules_inst;
  public:
    void set_streams(std::string ,std::vector<std::string> );
    //Poco::JSON::Array::Ptr get_rules_array();
    std::shared_ptr<nlohmann::json> get_rules_object();
    std::string to_string();
  };
}


#endif
