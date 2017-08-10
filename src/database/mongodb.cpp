
#include "database/mongodb.hh"
#include "data/Utils.hpp"
#include "data/time.hh"
#include "Utils.hpp"

// #include <Poco/MongoDB/MongoDB.h>
// #include <Poco/MongoDB/Connection.h>
// #include <Poco/MongoDB/Database.h>
// #include <Poco/MongoDB/Cursor.h>
// #include <Poco/MongoDB/Array.h>
// #include <Poco/MongoDB/Element.h>

#include <data/Utils.hpp>

#include <iostream>
#include <memory>
#include <mongo/client/dbclient.h>
#include <mongo/bson/bsonobj.h>
#include <mongo/client/dbclientcursor.h>
#include <mongo/bson/bsonobj.h>
//const std::string Mongodb::db_name="Streams";//"Streams-tests";

namespace apeters{
  Mongodb::Mongodb(){
  }

  std::string Mongodb::get_collections(const std::string & host,
				       int port,
				       const std::string & db_name){
    std::string result="[";
    std::vector<std::string> res_int;

    std::string err_msg;
    mongo::BSONObj info;
			 
    mongo::DBClientConnection c;
    mongo::HostAndPort handp(host, port);
    c.connect(handp,err_msg);
    std::list< std::string > lcollections=c.getCollectionNames(db_name,mongo::BSONObj());
    for (std::list<std::string>::iterator it = lcollections.begin();
	 it != lcollections.end(); it++){
      res_int.push_back(*it);
    }
    if(res_int.size()>0){
      for(size_t i(0);i<res_int.size()-1;++i){
	result+="\""+res_int[i]+"\",";
      }      
      result+="\""+res_int[res_int.size()-1]+"\"";
    }
    result+="]";
    c.logout(db_name,info);
    return result;
    //std::shared_ptr<mongo::DBClientCursor> cursor = c.query(db_name, MONGO_QUERY("listCollections" << "1"));

    // while (cursor->more())
    //   std::cout << cursor->next().toString() << std::endl;
  }

  int Mongodb::remove_rules(const std::string & host,
			    int port,
			    const std::string & collection,
			    const std::string & db_name,
			    const std::string & rule_name){
    std::string err_msg;
    mongo::BSONObj info;
    mongo::DBClientConnection c;
    mongo::BSONObjBuilder req_build;
    mongo::HostAndPort handp(host, port);
    c.connect(handp,err_msg);
    req_build.append("name",rule_name);
    c.remove(db_name+"."+collection,mongo::Query(req_build.obj()));
    c.logout(db_name,info);
    return 0;
  }
  
  std::string Mongodb::get_rules(const std::string & host,
				 int port,
				 const std::string & collection,
				 const std::string & db_name){
    std::string result="[";
    std::string err_msg;
    mongo::BSONObj info;
    mongo::DBClientConnection c;
    mongo::HostAndPort handp(host, port);
    c.connect(handp,err_msg);
    mongo::BSONObj req = BSON( "name" << 1 << "expressions" << 1 << "_id" << 0 );
    std::shared_ptr<mongo::DBClientCursor> cursor_ = c.query(db_name+"."+collection,mongo::BSONObj(),0,0, &req);
    while (cursor_->more()){
       result+=cursor_->next().jsonString();
       result+=",";
    }
    if(result.find_last_of(",")==result.size()-1){
      result=result.substr(0,result.size()-1);
    }
    c.logout(db_name,info);
    result+="]";
    return result;
  }
  
  std::string Mongodb::get_streams(const std::string & host,
				   int port,
				   const std::string & collection,
				   const std::string & db_name){
    std::string result="[";
    std::string err_msg;
    mongo::BSONObj info;
    mongo::DBClientConnection c;
    mongo::HostAndPort handp(host, port);
    c.connect(handp,err_msg);
    mongo::BSONObj req = BSON( "rule" << 1 << "timestamp" << 1 << "events" << 1 << "_id" << 0 );
    std::shared_ptr<mongo::DBClientCursor> cursor_ = c.query(db_name+"."+collection,mongo::BSONObj(),0,0, &req);
    while (cursor_->more()){
       result+=cursor_->next().jsonString();
       result+=",";
    }
    if(result.find_last_of(",")==result.size()-1){
      result=result.substr(0,result.size()-1);
    }
    c.logout(db_name,info);
    result+="]"; 
    // if(result.compare("[")!=0)
    //   result=result.substr(0,result.size()-1);
    // result+="]";
    //std::cout<<result<<std::endl;
    return result;
  }
  // std::string Mongodb::get_streams_of_rules_and_coll(const std::string & host,
  // 						     int port,
  // 						     const std::string & collection,
  // 						     const std::string & rules,
  // 						     const std::string & db_name){
  //   std::string result="[";
    
  //   std::string err_msg;
  //   mongo::DBClientConnection c;
  //   mongo::HostAndPort handp(host, port);
  //   c.connect(handp,err_msg);
  //   mongo::BSONObj req = BSON( "rule" << 1 << "timestamp" << 1 << "events" << 1 << "_id" << 0 );
  //   std::shared_ptr<mongo::DBClientCursor> cursor_ = c.query(db_name+"."+collection,MONGO_QUERY("rule" << rules).sort("timestamp"),0,0, &req);
  //   while (cursor_->more()){
  //      result+=cursor_->next().jsonString();
  //      result+=",";
  //   }
  //   if(result.find_last_of(",")==result.size()-1){
  //     result=result.substr(0,result.size()-1);
  //   }
  //   result+="]"; 
  //   return result;
  // }
  std::string Mongodb::get_rules_of_collection(const std::string & host,
					       int port,
					       const std::string & collection,
					       const std::string & db_name){
    std::string result="";
    std::string err_msg;
    mongo::DBClientConnection c;
    mongo::HostAndPort handp(host, port);
    c.connect(handp,err_msg);
    mongo::BSONObj req = BSON("distinct" << collection << "key" << "rule");
    mongo::BSONObj info;
    c.runCommand(db_name,req,info,0);
    result=info.jsonString();
    c.logout(db_name,info);
    //std::cout<<result<<std::endl;
    return result;
  }
  std::string Mongodb::get_streams_of_rules_and_coll_at_a_date(const std::string & host,
							       int port,
							       const std::string & collection,
							       const std::string & rules,
							       const std::string &date,
							       const std::string & db_name){
    std::string result="[";
    //std::cout<<date<<std::endl;
    Time time_1(date,"00:00:00.000");
    long long timestamp=(long long)time_1.get_timestamp_ms();
    long long timestamp2=timestamp+86400000;
    //std::cout<<timestamp<<" "<<timestamp2<<" "<<time_1.get_timestamp_ms()<<std::endl;
    
    std::string err_msg;
    mongo::BSONObj info;
    mongo::DBClientConnection c;
    mongo::HostAndPort handp(host, port);
    c.connect(handp,err_msg);
    mongo::BSONObj req = BSON( "rule" << 1 << "timestamp" << 1 << "events" << 1 << "_id" << 0 );
    mongo::BSONObjBuilder req_time;
    req_time.append("$gte",timestamp);
    req_time.append("$lt",timestamp2);
    std::shared_ptr<mongo::DBClientCursor> cursor_ =
      c.query(db_name+"."+collection,MONGO_QUERY("rule" << rules << "timestamp" << req_time.obj()).sort("timestamp") /*mongo::BSONObj()*/,0,0, &req);
    while (cursor_->more()){
      result+= cursor_->next().jsonString();
      result+=",";
    }
    if(result.find_last_of(",")==result.size()-1){
      result=result.substr(0,result.size()-1);
    }
    c.logout(db_name,info);
    result+="]"; 
    return result;
  }
  std::string Mongodb::get_rules_of_collection_at_a_date(const std::string & host,
							 int port,
							 const std::string & collection,
							 const std::string & date,
							 const std::string & db_name){

    //{ distinct:"_DomassistSzelengowicz",key:"rule",query:{'timestamp':{$gt:1496872800000,$lt:1495522970170000},'rule':{$ne:"raw"}}} 
  
    //{ find:"_DomassistSzelengowicz",filter:{'timestamp':{$gt:1496872800000,$lt:1495522970170000},'rule':{$ne:"raw"}}}
    std::string result="[";
    //std::cout<<date<<std::endl;
    Time time_1(date,"00:00:00.000");
    long long timestamp=time_1.get_timestamp_ms();
    long long timestamp2=timestamp+86400000;
    //std::cout<<timestamp<<" "<<timestamp2<<std::endl;
    mongo::BSONObjBuilder req_time;
    mongo::BSONObj info;
    req_time.append("$gte",timestamp);
    req_time.append("$lt",timestamp2);
    mongo::BSONObjBuilder req_;
    req_.append("timestamp", req_time.obj());
    std::string err_msg;
    mongo::DBClientConnection c;
    mongo::HostAndPort handp(host, port);
    c.connect(handp,err_msg);
    mongo::BSONObj req = BSON("distinct" << collection << "key" << "rule" << "query" << req_.obj());
    //std::cout<<req.jsonString()<<std::endl;
    //mongo::BSONObj info;
    c.runCommand(db_name,req,info,0);

    // std::shared_ptr<mongo::DBClientCursor> cursor_ =
    //   c.query(db_name+"."+collection,MONGO_QUERY("key" << "rule" << "timestamp" << req_time.obj() << "distinct" << collection ) /*mongo::BSONObj()*/);
    // while (cursor_->more()){
    //   //result+=
    //   std::cout<<"lololil "<<cursor_->next().jsonString()<<std::endl;
    //   //result+=",";
    // }
    result=info.jsonString();
    c.logout(db_name,info);
    
    //std::cout<<result<<std::endl;
    return result;
  }

  // std::string Mongodb::get_all_batteries_of_collection(const std::string & host,
// 						       int port,
// 						       const std::string & collection,
// 						       const std::string & db_name){


//     Poco::MongoDB::Document::Ptr existDoc=new Poco::MongoDB::Document;
//     existDoc->add("$exists",true);
//     Poco::MongoDB::Document::Ptr batteryDoc=new Poco::MongoDB::Document;
//     batteryDoc->add("BatteryLevel",existDoc);
//     Poco::MongoDB::Document::Ptr matchDoc=new Poco::MongoDB::Document;
//     matchDoc->add("$elemMatch",batteryDoc);
//     // Poco::MongoDB::Document::Ptr Doc=new Poco::MongoDB::Document;
//     // matchDoc->add("$elemMatch",batteryDoc);
//     // Poco::MongoDB::Document::Ptr eventDoc=new Poco::MongoDB::Document;
//     // eventDoc->add("events",roleDoc);
  

//     int cpt=0;

//     std::string result="[";
//     Poco::MongoDB::Connection connection(host, port);
//     //std::cout<<"collections "<<collection<<std::endl;
//     Poco::MongoDB::Cursor cursor(db_name, collection);
//     cursor.query().selector().addNewDocument("$query").add("rule", "raw").add("events",matchDoc);
//     cursor.query().returnFieldSelector().add("timestamp", 1);
//     cursor.query().returnFieldSelector().add("rule", 1);
//     cursor.query().returnFieldSelector().add("events", 1);
//     cursor.query().returnFieldSelector().add("_id", 0);
//     //cursor.query().returnFieldSelector().add("events",matchDoc);
//     cursor.query().selector().addNewDocument("$orderby").add("timestamp", 1);

//     //db.getCollection('_45109619').find({rule:"raw", events: {"$elemMatch":{BatteryLevel :{$exists : true}}} })
//     Poco::MongoDB::ResponseMessage& response = cursor.next(connection);
//     for (;;){
//       for (Poco::MongoDB::Document::Vector::const_iterator it = response.documents().begin(); it != response.documents().end(); ++it){
// 	cpt++;
// 	//std::cout << (*it)->toString() << std::endl;
// 	result+=(*it)->toString();
// 	result+=",";
//       }
//       if (response.cursorID() == 0){
// 	break;
//       }
//       response = cursor.next(connection);
//     };
//     if(cpt>0)
//       result=result.substr(0,result.size()-1);
//     result+="]";
//     //std::cout<<result<<std::endl;
//     return result;
//   }
}
//db.getCollection('_Domassist0122').find({events:{$elemMatch: {role : { location : "Livingroom", kind : "Presence" } }}})

//db.getCollection('_Domassist0122').find({$or:[{rule:"noUbiquity"},{rule:"WebsocketEndWarning"}]})
