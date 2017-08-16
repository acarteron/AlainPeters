#include "data/role.hh"
namespace apeters{
  std::string Role::getLocation()const {return location;}
  std::string Role::getKind()const {return kind;}
  void Role::define_role(std::string role_str){
    nlohmann::json j=nlohmann::json::parse(role_str);
    nlohmann::json role;
    location=j["role"]["location"].get<std::string>();
    kind=j["role"]["kind"].get<std::string>();
    timestamp=j["timestamp"]["$numberLong"].get<std::string>();
    status=j["status"].get<std::string>();

    role["location"]=location;
    role["kind"]=kind;
    role["timestamp"]=timestamp;
    role["status"]=status;
    role_obj["role"]=role;
  }
  std::shared_ptr<nlohmann::json> Role::get_role_obj(){
    return std::make_shared<nlohmann::json>(role_obj);
  }
  std::string Role::to_string(){
    return role_obj.dump();
  }
}
