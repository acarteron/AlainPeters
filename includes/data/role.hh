#ifndef ROLE_HH
#define ROLE_HH

#include <string>
#include <memory>
#include "data/Utils.hpp"

namespace apeters{
  class Role {
  private:
    nlohmann::json role_obj;
    std::string location="";
    std::string kind="";
    std::string timestamp="";
    std::string status="";
  public:
    std::string getLocation()const ;
    std::string getKind()const ;
    void define_role(std::string);
    std::string to_string();
    std::shared_ptr<nlohmann::json> get_role_obj();
  };
}
#endif // ROLE_HH
