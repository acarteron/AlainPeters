#include "data/rule_instance.hh"

namespace apeters{
  std::vector<Role> Rule_Instance::getRoles(){return roles;}
  void Rule_Instance::set_timestamp(std::string timestamp_){timestamp=timestamp_;}
  bool Rule_Instance::operator==(const Rule_Instance& rule_) const{
    bool eq=true;
    if(roles.size()!=rule_.roles.size())
      return false;
    for(size_t i(0);i<roles.size()&&eq;++i){
      if(roles[i].getLocation().compare(rule_.roles[i].getLocation())!=0||
	 roles[i].getKind().compare(rule_.roles[i].getKind())!=0)
	eq=false;
    }
    return eq;
  }
  bool Rule_Instance::operator<(const Rule_Instance& rule_)const{
    return timestamp>rule_.timestamp;
  }
  void Rule_Instance::set_roles(std::string timestamp_,std::vector<std::string> roles_){
    timestamp=timestamp_;
   
    std::string roles_array="[";
    for(size_t i(0);i<roles_.size();++i){
      nlohmann::json j=nlohmann::json::parse(roles_[i]);
    
      Role rol;
      if(roles_[i].find("CommFailure")!=std::string::npos){
	rol.define_role(data::Utils::extract_StreamType(roles_[i],"CommFailure"));
      }else{
	if(roles_[i].find("BatteryLevel")!=std::string::npos){
	  rol.define_role(data::Utils::extract_StreamType(roles_[i],"BatteryLevel"));
	}else{
	  rol.define_role(data::Utils::extract_StreamType(roles_[i],"StreamEvent"));
	}
      }
      roles_array+=rol.get_role_obj()->dump();
      if(i<roles_.size()-1)
	roles_array+=",";
      roles.push_back(rol);
    }
    roles_array+="]";
    rule_instance_obj["timestamp"]=timestamp;
    rule_instance_obj["roles"]=nlohmann::json::parse(roles_array);
  }
  std::shared_ptr<nlohmann::json> Rule_Instance::get_rule_instance_obj(){
    return std::make_shared<nlohmann::json>(rule_instance_obj);
  }
  std::string Rule_Instance::to_string(){
    return rule_instance_obj.dump();
  }
}
