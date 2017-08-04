#ifndef RULE_INSTANCE_HH
#define RULE_INSTANCE_HH

#include <string>
#include "data/role.hh"

namespace apeters{
  class Rule_Instance{
  private:
    std::string timestamp;
    std::vector<Role> roles;
    nlohmann::json rule_instance_obj;
  public:
    //~Rule_Instance(){roles.clear();}
    std::vector<Role> getRoles();
    void set_timestamp(std::string);

    bool operator==(const Rule_Instance& ) const;
    bool operator<(const Rule_Instance& )const;
    void set_roles(std::string ,std::vector<std::string> );
    std::shared_ptr<nlohmann::json> get_rule_instance_obj();
    std::string to_string();
  };
}
#endif // RULE_INSTANCE_HH
