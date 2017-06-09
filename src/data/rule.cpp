#include "data/rule.hh"
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
    Poco::JSON::Parser      parser;
    Poco::Dynamic::Var      str_var;
    Poco::JSON::Object::Ptr str_obj;
    Poco::JSON::Array::Ptr  events_array;
       
    str_var = parser.parse(streams[i]);
    parser.reset();
    str_obj = str_var.extract<Poco::JSON::Object::Ptr>();
    str_var = str_obj->get("timestamp");
    std::string timestamp=str_var.toString();
    str_var = str_obj->get("events");
    events_array = str_var.extract<Poco::JSON::Array::Ptr>();
    Poco::Dynamic::Array da = *events_array;
    for(size_t i(0);i<da.size();++i){
      tmp_stream.push_back(da[i]);
    }
    rul.set_roles(timestamp,tmp_stream);
    rules_inst.push_back(rul);
  }
  std::sort(rules_inst.begin(), rules_inst.end());  
  std::sort(rules_inst.begin(), rules_inst.end(),sortRuleByRole);
  rules_inst.erase(std::unique(rules_inst.begin(), rules_inst.end()), rules_inst.end());    
  for(size_t i(0);i<rules_inst.size();++i){
    rules_inst_array->add(rules_inst[i].get_rule_instance_obj());
  }
  rules_obj->set("number",rules_inst.size());
  rules_obj->set("streams",rules_inst_array);
  size=rules_inst.size();
  //rules_inst.clear();
}
Poco::JSON::Array::Ptr Rule::get_rules_array(){return rules_inst_array;}
Poco::JSON::Object::Ptr Rule::get_rules_object(){return rules_obj;}
std::string Rule::to_string(){
  std::ostringstream  out;
  rules_inst_array->stringify(out,0);
  return  out.str();
}
