#include "data/rule_instance.hh"
#include "data/Utils.hpp"

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
  Poco::JSON::Array::Ptr  roles_array=new Poco::JSON::Array;
  //std::cout<<roles_.size()<<std::endl;
  for(size_t i(0);i<roles_.size();++i){
    Poco::JSON::Parser      parser;
    Poco::Dynamic::Var      str_var;
    Poco::JSON::Object::Ptr str_obj;
    str_var = parser.parse(roles_[i]);
    parser.reset();
    Role rol;
    if(str_var.toString().find("CommFailure")!=std::string::npos){
      rol.define_role(data::Utils::extract_StreamType(str_var.toString(),"CommFailure"));
    }else{
      if(str_var.toString().find("BatteryLevel")!=std::string::npos){
	rol.define_role( data::Utils::extract_StreamType(str_var.toString(),"BatteryLevel"));
      }else{
	rol.define_role(data::Utils::extract_StreamType(str_var.toString(),"StreamEvent"));
      }
    }
    roles_array->add(rol.get_role_obj());
    roles.push_back(rol);
  }
  rule_instance_obj->set("timestamp",timestamp);
  rule_instance_obj->set("roles",roles_array);
}
Poco::JSON::Object::Ptr Rule_Instance::get_rule_instance_obj(){
  return rule_instance_obj;
}
std::string Rule_Instance::to_string(){
  std::ostringstream  out;
  rule_instance_obj->stringify(out,0);
  return out.str();
}
