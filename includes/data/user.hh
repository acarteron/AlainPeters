#ifndef USER_HH
#define USER_HH

#include <memory>
#include <string>
#include "data/rule.hh"
#include "data/Utils.hpp"

namespace apeters{
  class User{
    nlohmann::json user_obj;
    std::string date;
    std::string user;
    std::map<std::string,nlohmann::json> priorities;
  public:
    void set_user(std::string);
    void set_date(std::string);
    void addrules(std::string,std::string,std::vector<std::string>);
    std::shared_ptr<nlohmann::json> getAll();
  };
}
#endif // USER_HH
