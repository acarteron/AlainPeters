#include "data/user.hh"
#include <iostream>
namespace apeters{
  void User::set_user(std::string user_){
    user=user_;
    user_obj["user"]=user;
  }
  void User::set_date(std::string date_){
    date=date_;
  }
  void User::addrules(std::string name,
		      std::string prio,
		      std::vector<std::string> streams){
    if(prio.compare("")!=0){
      Rule rul;
      rul.set_streams(name,streams);
      priorities[prio][name]=nlohmann::json::parse(rul.get_rules_object()->dump());
    }
  }
  std::shared_ptr<nlohmann::json> User::getAll(){
    std::string arr="[";
    std::vector<std::string> arr_tmp;
    for(std::map<std::string,nlohmann::json>::iterator it = priorities.begin();it != priorities.end(); it++) {
      arr_tmp.push_back(it->first);
      user_obj[it->first]=it->second;
    }
    if(arr_tmp.size()>0){
      for(size_t i(0);i<arr_tmp.size()-1;++i){
	arr+="\""+arr_tmp[i]+"\",";
      }
      arr+="\""+arr_tmp[arr_tmp.size()-1]+"\"";
    }
    arr+="]";
    user_obj["priorities"]=nlohmann::json::parse(arr);
    return std::make_shared<nlohmann::json>(user_obj);
  }
}
