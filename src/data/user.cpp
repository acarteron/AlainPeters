#include "data/user.hh"
namespace apeters{
void User::set_user(std::string user_){
  user=user_;
  user_obj->set("user",user);
}
void User::set_date(std::string date_){date=date_;}
std::string User::define_priorities(std::string name){
  std::string prio="";
  if(name.compare("heartbeatAlert")==0){
    prio="internet";
  }else{
    if(name.compare("shutdownAlert")==0){
      prio="domassist_tablet";
    }else{
      if(name.compare("startDomassist")==0){
	prio="domassist_tablet";
      }else{
	if(name.compare("tabletRestarted")==0){
	  prio="domassist_tablet";
	}else{
	  if(name.compare("batteryAlert")==0){
	    prio="sensors";
	  }else{
	    if(name.compare("batteryWarning")==0){
	      prio="sensors";
	    }else{
	      if(name.compare("commfailureAlert")==0||
		 name.compare("CommfailureWwalert")==0/*||
		 /*name.compare("CommfailureWarning")==0*/){
		prio="sensors";
	      }else{}
	      //std::cout<<" lolol "<<name<<std::endl;
	    }
	  }
	}
      }
    }
  }
  return prio;
}
void User::addrules(std::string name,std::vector<std::string> streams){
  std::string prio=define_priorities(name);
  if(prio.compare("")!=0){
    Rule rul;
    rul.set_streams(name,streams);
    if(priorities.count(prio)==0)
      priorities[prio]=new Poco::JSON::Object();
    priorities[prio]->set(name,rul.get_rules_object());
  }
}
Poco::JSON::Object::Ptr User::getAll(){
  Poco::JSON::Array::Ptr  prio_array=new Poco::JSON::Array();
  std::string theend="{\"user\":\""+user+"\"";
  for(std::map<std::string,Poco::JSON::Object::Ptr>::iterator it = priorities.begin();it != priorities.end(); it++) {
    prio_array->add(it->first);
    Poco::Dynamic::Var rules_var;
    std::ostringstream  out;
    it->second->stringify(out,0);
    user_obj->set(it->first,it->second);
  }
  user_obj->set("priorities",prio_array);
  return user_obj;
}
}
