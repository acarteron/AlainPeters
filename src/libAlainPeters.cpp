#include "libAlainPeters.hh"

#include "files/files.hh"
#include "database/mongodb.hh"
#include "data/Utils.hpp"
#include "Utils.hpp"
#include "data/user.hh"

libAlainPeters::libAlainPeters(){
  apeters::File file("/opt/Sati/db.json");
  std::string db_param=file.readFile();
  file.closeFile();

  nlohmann::json j=nlohmann::json::parse(db_param);
  mongo_host=j["mongo_host"].get<std::string>();
  mongo_port=j["mongo_port"].get<int>();
  mongo_base=j["streams_collection"].get<std::string>();
}
libAlainPeters::~libAlainPeters(){
}
void libAlainPeters::do_what_you_do(std::string date){
  //std::string date="2017-06-08";
  getPriorities();
  //std::cout<<"all: "<<std::endl;
  std::vector<apeters::User> users;
  std::string collections=apeters::Mongodb::get_collections(mongo_host,mongo_port,mongo_base);  
  std::vector<std::string> vect_user=collection_to_vector(collections);
  for(size_t i(0);i<vect_user.size();++i){
    std::string user_str=vect_user[i];//"_DomassistTeynie";
    //std::cout<<user_str<<" "<<date<<std::endl;
    std::string rules_list=apeters::Mongodb::get_rules_of_collection_at_a_date(mongo_host,mongo_port,user_str,date,mongo_base);
    //std::cout<<rules_list<<" "<<user_str<<std::endl;
    std::vector<std::string> vect_rule_list=rule_list_to_vector(rules_list);
    apeters::User us;
    us.set_user(user_str);//vect_user[i];
    us.set_date(date);
    //std::cout<<"vect rule size "<<vect_rule_list.size()<<std::endl;
    for(size_t j(0);j<vect_rule_list.size();++j){
      //std::cout<<vect_rule_list[j]<<std::endl;
      std::vector<std::string> vector_streams=stream_list_to_vector(apeters::Mongodb::get_streams_of_rules_and_coll_at_a_date(mongo_host,mongo_port,user_str,vect_rule_list[j],date,mongo_base));
      //std::cout<<"vect stream size "<<vector_streams.size()<<std::endl;
      // for(size_t z(0);z<vector_streams.size();++z)
      // 	std::cout<<vector_streams[z]<<std::endl;
      us.addrules(vect_rule_list[j],find_prio(vect_rule_list[j]),vector_streams);
    }
    //std::cout<<"asdasd"<<std::endl;
    if(vect_rule_list.size()>0){
      users.push_back(us);	    
    }  
  }
  //std::cout<<" asdasdasdasdasd "<<users.size()<<std::endl;
  std::string allarray="[";
  if(users.size()>0){
    for(size_t i(0);i<users.size()-1;++i){
      //std::cout<<users[i].getAll()->dump()<<std::endl;
      users[i].getAll();
      allarray+=users[i].getAll()->dump()+",";
    }
    allarray+=users[users.size()-1].getAll()->dump();
  }
  allarray+="]";
  all["date"]=date;
  all["results"]=nlohmann::json::parse(allarray);
  // //getPriorities();
}
std::string libAlainPeters::find_prio(std::string rule_name){
  std::string prio="";
  bool found=false;
  for (nlohmann::json::iterator it = all_prio_array.begin();
       it != all_prio_array.end()&&!found;
       ++it) {
    std::vector<std::string> tmp_rule=map_prio[it.value().get<std::string>()];
    for(size_t j(0);j<tmp_rule.size();++j){
      if(tmp_rule[j].compare(rule_name)==0){
	prio=it.value().get<std::string>();
	found=true;
      }
    }
  }
  //std::cout<<"rule: "<<rule_name<<" prio "<< prio <<std::endl;
  return prio;
}
void libAlainPeters::getPriorities(){
  std::vector<std::string> vect_rule;
  apeters::File file("/opt/Sati/order.json");
  std::string prios=file.readFile();
  file.closeFile();
  nlohmann::json j=nlohmann::json::parse(prios);
  //std::cout<<j["priorities"]<<std::endl;
  all_prio_array = j["priorities"];
  for (nlohmann::json::iterator it = j["priorities"].begin();
       it != j["priorities"].end();
       ++it) {
    all[it.value().get<std::string>()]=j[it.value().get<std::string>()];
    for (nlohmann::json::iterator it_r = j[it.value().get<std::string>()].begin();
	 it_r != j[it.value().get<std::string>()].end();
	 ++it_r) {
      vect_rule.push_back(it_r.value().get<std::string>());
    }
    map_prio[it.value().get<std::string>()]=vect_rule;
  }
  all["priorities"]=j["priorities"];
}
std::string libAlainPeters::getDailyReport_as_string(){
  return all.dump();
}
// // Poco::JSON::Object::Ptr libAlainPeters::getDailyReport_as_json_object(){
// //   return all;
// // }


std::vector<std::string> libAlainPeters::collection_to_vector(std::string collection){
  std::vector<std::string> vector_collection;
  nlohmann::json j=nlohmann::json::parse(collection);
  for (nlohmann::json::iterator it = j.begin();it != j.end();++it) {
    vector_collection.push_back(it.value().get<std::string>());
  }
  sort(vector_collection.begin(), vector_collection.end());
  return vector_collection;
}
std::vector<std::string> libAlainPeters::rule_list_to_vector(std::string rule_list){
  std::vector<std::string> vector_rules;
  nlohmann::json j=nlohmann::json::parse(rule_list);
  //std::cout<<j<<std::endl;
  for (nlohmann::json::iterator it = j["values"].begin();
       it != j["values"].end();
       ++it) {
    vector_rules.push_back(it.value().get<std::string>());
  }
  sort(vector_rules.begin(), vector_rules.end());
  return vector_rules;
}
std::vector<std::string> libAlainPeters::stream_list_to_vector(std::string stream_list){
  std::vector<std::string> vector_streams;

  nlohmann::json j=nlohmann::json::parse(stream_list);
  //std::cout<<j<<std::endl;
  for (nlohmann::json::iterator it = j.begin();it != j.end(); ++it) {
    vector_streams.push_back(it.value().dump());
  }
  return vector_streams;
}

