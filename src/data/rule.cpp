#include "data/rule.hh"
#include "Utils.hpp"

namespace apeters{
  static bool sortRuleByRole(Rule_Instance rule1_,Rule_Instance rule2_){
    if(rule1_.getRoles()[0].getLocation().compare(rule2_.getRoles()[0].getLocation())==0){
      return rule1_.getRoles()[0].getKind()<rule2_.getRoles()[0].getKind();
    }
    return rule1_.getRoles()[0].getLocation()<rule2_.getRoles()[0].getLocation();
  }
  void Rule::set_streams(std::string name_,std::vector<std::string> streams){
    name=name_;
    for(size_t i(0);i<streams.size();++i){
      std::vector<std::string> tmp_stream;
      Rule_Instance rul;
      //std::cout<<"lol"<<std::endl;
      nlohmann::json j=nlohmann::json::parse(streams[i]);
      //std::cout<<"std"<<std::endl;
      std::string timestamp=j["timestamp"]["$numberLong"].get<std::string>();
      for (nlohmann::json::iterator it = j["events"].begin();
	   it != j["events"].end(); ++it) {
	//std::cout<<*it<<std::endl;
	tmp_stream.push_back(it.value().dump());
      }
      rul.set_roles(timestamp,tmp_stream);
      rules_inst.push_back(rul);
    }
    std::sort(rules_inst.begin(), rules_inst.end());  
    std::sort(rules_inst.begin(), rules_inst.end(),sortRuleByRole);
    rules_inst.erase(std::unique(rules_inst.begin(), rules_inst.end()), rules_inst.end());
    std::string rules_inst_array="[";
    for(size_t i(0);i<rules_inst.size()-1;++i){
      rules_inst_array+=rules_inst[i].get_rule_instance_obj()->dump()+",";
    }
    rules_inst_array+=rules_inst[rules_inst.size()-1].get_rule_instance_obj()->dump()+"]";
    rules_obj["number"]=rules_inst.size();
    rules_obj["streams"]=nlohmann::json::parse(rules_inst_array);
    size=rules_inst.size();
    //rules_inst.clear();
  }
  std::shared_ptr<nlohmann::json> Rule::get_rules_object(){
    return std::make_shared<nlohmann::json>(rules_obj);
  }
  std::string Rule::to_string(){
    return rules_obj.dump();
  }
}
