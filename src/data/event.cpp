#include "data/event.hh"

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include "Utils.hpp"

Event & Event::affect(const Event & event_){
  status=event_.status;
  timestamp=event_.timestamp;
  user=event_.user;
  return * this;
}
Event::Event(){
  user="";
  status="";
  timestamp=Time();
}

Event::Event(const Event& event_){
  affect(event_);
}
Event::Event(std::string event_str_){
  Poco::JSON::Parser      parser;
  Poco::Dynamic::Var      str_var;
  Poco::JSON::Object::Ptr str_obj;
  // Poco::Dynamic::Var      streamevent_var;
  // Poco::JSON::Object::Ptr streamevent_obj;
  Poco::Dynamic::Var      role_var;
  Poco::JSON::Object::Ptr role_obj;
  Poco::Dynamic::Var      status_var;
  Poco::Dynamic::Var      timestamp_var;
  Poco::Dynamic::Var      user_var;
  
  str_var = parser.parse(event_str_);
  parser.reset();
  str_obj = str_var.extract<Poco::JSON::Object::Ptr>();
  // streamevent_var = str_obj->get("StreamEvent");
  // streamevent_obj = streamevent_var.extract<Poco::JSON::Object::Ptr>();  
 
  status_var= str_obj->get("status");//streamevent_obj->get("status");
  timestamp_var= str_obj->get("timestamp");
  user_var= str_obj->get("user");

  status=status_var.toString();
  timestamp=Time(Utils::stringTo<unsigned long>(timestamp_var.toString()));
  user=user_var.toString();
}

Event::Event(std::string status_,
	     unsigned long timestamp_,
	     std::string user_){
  status=status_;
  timestamp=Time(timestamp_);
  user=user_;
}
  
unsigned long  Event::getTimestamp(){
  return timestamp.get_timestamp_ms();
}
unsigned long  Event::getDailyTime(){
  return timestamp.get_daily_timestamp();
}
std::shared_ptr<Time> Event::getTime(){
  return std::make_shared<Time>(timestamp);
}

std::string  Event::getStatus(){
  return status;
}
std::string  Event::getUser(){
  return user;
}
bool  Event::equals(Event event_){
  return timestamp==event_.timestamp &&
    user.compare(event_.user)==0 &&
    status.compare(event_.status)==0;
}
// Event& operator=(const Event & event_){
//   return affect(event_);
// }
std::string  Event::toString(){
  return "{\"Event\":{\"status\":\""+status+"\",\"timestamp\":\""+timestamp.to_string()+"\",\"user\":\""+user+"\"}}";
}
