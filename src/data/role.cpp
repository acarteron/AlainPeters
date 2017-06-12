#include "data/role.hh"
namespace apeters{
  std::string Role::getLocation()const {return location;}
  std::string Role::getKind()const {return kind;}
  void Role::define_role(std::string role_str){
    Poco::Dynamic::Var      location_var;
    Poco::Dynamic::Var      kind_var;
    Poco::JSON::Object::Ptr kloc_obj=new Poco::JSON::Object();    
    Poco::JSON::Parser      parser;
    Poco::Dynamic::Var      str_var;
    Poco::JSON::Object::Ptr str_obj;
    str_var = parser.parse(role_str);
    parser.reset();
    str_obj = str_var.extract<Poco::JSON::Object::Ptr>();
    str_var = str_obj->get("role");
    str_obj = str_var.extract<Poco::JSON::Object::Ptr>();
    location_var = str_obj->get("location");
    location=location_var.toString();
    kind_var = str_obj->get("kind");
    kind=kind_var.toString();
    kloc_obj->set("location",location_var);
    kloc_obj->set("kind",kind_var);
    role_obj->set("role",kloc_obj);
  }
  Poco::JSON::Object::Ptr Role::get_role_obj(){
    return role_obj;
  }
  std::string Role::to_string(){
    std::ostringstream  out;
    role_obj->stringify(out,0);
    return out.str();//"{\"role\":{\"kind\":\""+kind+"\",\"location\":\""+location+"\"}}";
  }
}
