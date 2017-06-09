#include <iostream>
#include <vector>

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Array.h>

#include "files/files.hh"
#include "database/mongodb.hh"
#include "data/Utils.hpp"
#include "Utils.hpp"
#include "data/user.hh"


std::vector<std::string> collection_to_vector(std::string collection){
  Poco::JSON::Parser      parser;
  Poco::Dynamic::Var      str_var;
  Poco::JSON::Array::Ptr  collection_array;
  std::vector<std::string> vector_collection;
  
  str_var = parser.parse(collection);
  parser.reset();
  collection_array = str_var.extract<Poco::JSON::Array::Ptr>();
  Poco::Dynamic::Array da = *collection_array;
  for(size_t i(0);i<da.size();++i){
    vector_collection.push_back(da[i]);
  }
  sort(vector_collection.begin(), vector_collection.end());
  return vector_collection;
}
std::vector<std::string> rule_list_to_vector(std::string rule_list){
  Poco::JSON::Parser      parser;
  Poco::Dynamic::Var      str_var;
  Poco::JSON::Object::Ptr str_obj;
  Poco::JSON::Array::Ptr  rule_list_array;
  std::vector<std::string> vector_rules;
  
  str_var = parser.parse(rule_list);
  parser.reset();
  str_obj = str_var.extract<Poco::JSON::Object::Ptr>();
  str_var = str_obj->get("values");
  rule_list_array = str_var.extract<Poco::JSON::Array::Ptr>();
  
  Poco::Dynamic::Array da = *rule_list_array;
  for(size_t i(0);i<da.size();++i){
    vector_rules.push_back(da[i]);
  }
  sort(vector_rules.begin(), vector_rules.end());
  return vector_rules;
}
std::vector<std::string> stream_list_to_vector(std::string stream_list){
  Poco::JSON::Parser      parser;
  Poco::Dynamic::Var      str_var;
  Poco::JSON::Array::Ptr  rule_list_array;
  std::vector<std::string> vector_streams;
  
  str_var = parser.parse(stream_list);
  parser.reset();
  rule_list_array = str_var.extract<Poco::JSON::Array::Ptr>();
  Poco::Dynamic::Array da = *rule_list_array;
  for(size_t i(0);i<da.size();++i){
    vector_streams.push_back(da[i]);
  }
  return vector_streams;
}

int main(int argc, char** argv){
  std::string date="2017-06-08";
  std::string mongo_host="localhost";
  int mongo_port=27017;
  std::vector<User> users;
  std::string collections=Mongodb::get_collections(mongo_host,mongo_port);  
  std::vector<std::string> vect_user=collection_to_vector(collections);
  for(size_t i(0);i<vect_user.size();++i){
    std::string user_str=vect_user[i];//"_DomassistTeynie";
    std::string rules_list=Mongodb::get_rules_of_collection_at_a_date(mongo_host,mongo_port,user_str,date);
    std::vector<std::string> vect_rule_list=rule_list_to_vector(rules_list);
    User us;
    us.set_user(user_str);//vect_user[i];
    us.set_date(date);
    for(size_t j(0);j<vect_rule_list.size();++j){
       std::vector<std::string> vector_streams=stream_list_to_vector(Mongodb::get_streams_of_rules_and_coll_at_a_date(mongo_host,mongo_port,user_str,vect_rule_list[j],date));
      us.addrules(vect_rule_list[j],vector_streams);		     
    }
    if(vect_rule_list.size()>0){
      users.push_back(us);	    
    }  
  }
  Poco::JSON::Object::Ptr all=new Poco::JSON::Object();
  Poco::JSON::Array::Ptr allarray=new Poco::JSON::Array();
  for(size_t i(0);i<users.size();++i){
    allarray->add(users[i].getAll());
  }
  all->set("date",date);
  all->set("results",allarray);
  std::ostringstream  out;
  all->stringify(out,0);
  Files file("res/"+date,"out");
  file.writeFile(out.str());
  file.closeFile();
  std::cout<< out.str()<<std::endl;
  

}
/** \mainpage : 
 * \author adcarter
 * \version : 0.0 $
 * \date : lun. mai 29 10:39:17 CEST 2017 $
 * \section intro_sec Introduction
 * Contact: acarteron@openmailbox.org
 * Created on: lun. mai 29 10:39:17 CEST 2017
 *
 * \section install_sec Installation
 *
 * This is f***** easy
 *
 * \subsection step1 Step 1 : Compile
 *
 *  Run this command to the project root
 *  <br/>
 *  <code>make</code>
 *
 * \subsection step2 Step 2 : Launch
 *
 *  Compiled program can be found in the subfolder <code>./bin</code>, it is called <code></code>.
 * 
 *  \subsection step3 Step 3 : Otherwise
 *  
 *  You can read the file <code>README.RTFM</code> if it exists
 */

