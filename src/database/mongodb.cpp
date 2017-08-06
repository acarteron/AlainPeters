#include "database/mongodb.hh"
#include "data/Utils.hpp"
#include "data/time.hh"
#include "Utils.hpp"

#include <Poco/MongoDB/MongoDB.h>
#include <Poco/MongoDB/Connection.h>
#include <Poco/MongoDB/Database.h>
#include <Poco/MongoDB/Cursor.h>
#include <Poco/MongoDB/Array.h>
#include <Poco/MongoDB/Element.h>

#include <data/Utils.hpp>
//#include <json.hpp>

#include <iostream>

//const std::string Mongodb::db_name="Streams";//"Streams-tests";

namespace apeters{
  Mongodb::Mongodb(){
  }

  std::string Mongodb::get_collections(const std::string & host,
				       int port,
				       const std::string & db_name){
    Poco::MongoDB::Connection connection(host, port);
    Poco::MongoDB::Database db(db_name);
    Poco::SharedPtr<Poco::MongoDB::QueryRequest> command = db.createCommand();
    command->selector().add("listCollections", "1");
    std::string result="[";
    Poco::MongoDB::ResponseMessage response;
    connection.sendRequest(*command, response);
    if (response.hasDocuments()){
      nlohmann::json j=nlohmann::json::parse(response.documents()[0]->toString());
      std::vector<std::string> res_int;  
      for (nlohmann::json::iterator it = j["cursor"]["firstBatch"].begin();
	   it != j["cursor"]["firstBatch"].end(); ++it) {
	res_int.push_back((*it)["name"].get<std::string>());
      }
      for(size_t i(0);i<res_int.size()-1;++i){
	result+="\""+res_int[i]+"\",";
      }
      result+="\""+res_int[res_int.size()-1]+"\"";
    }
    result+="]";
    return result;
  }

  int Mongodb::remove_rules(const std::string & host,
			    int port,
			    const std::string & collection,
			    const std::string & db_name,
			    const std::string & rule_name){
    Poco::MongoDB::Connection connection(host, port);
    try{
      Poco::MongoDB::Database db(db_name);
      Poco::SharedPtr<Poco::MongoDB::DeleteRequest> deleteRuleRequest = db.createDeleteRequest(collection);
      deleteRuleRequest->selector().add("name", rule_name);
      connection.sendRequest(*deleteRuleRequest);
      std::string lastError = db.getLastError(connection);
      if (!lastError.empty()){
	std::cout << "Last Error: " << db.getLastError(connection) << std::endl;
	return -2;
      }
      return 0;
    }
    catch (Poco::Exception& exc){
      std::cerr << exc.displayText() << std::endl;
      return -1;
    }
  }
  
  std::string Mongodb::get_rules(const std::string & host,
				 int port,
				 const std::string & collection,
				 const std::string & db_name){
    std::string result="[";
    Poco::MongoDB::Connection connection(host, port);
    Poco::MongoDB::Cursor cursor(db_name, collection);
    cursor.query().returnFieldSelector().add("name", 1);
    cursor.query().returnFieldSelector().add("expressions", 1);
    cursor.query().returnFieldSelector().add("_id", 0);
    Poco::MongoDB::ResponseMessage& response = cursor.next(connection);
    for (;;){
      for (Poco::MongoDB::Document::Vector::const_iterator it = response.documents().begin(); it != response.documents().end(); ++it){
	result+=(*it)->toString();
	result+=",";
      }
      if (response.cursorID() == 0){
	break;
      }
      response = cursor.next(connection);
    };
    result=result.substr(0,result.size()-1);
    result+="]";
    return result;
  }
  
  std::string Mongodb::get_streams(const std::string & host,
				   int port,
				   const std::string & collection,
				   const std::string & db_name){
    std::string result="[";
    Poco::MongoDB::Connection connection(host, port);
    //std::cout<<"collections "<<collection<<std::endl;
    Poco::MongoDB::Cursor cursor(db_name, collection);
    cursor.query().returnFieldSelector().add("rule", 1);
    cursor.query().returnFieldSelector().add("timestamp", 1);
    cursor.query().returnFieldSelector().add("events", 1);
    cursor.query().returnFieldSelector().add("_id", 0);

    Poco::MongoDB::ResponseMessage& response = cursor.next(connection);
    for (;;){
      for (Poco::MongoDB::Document::Vector::const_iterator it = response.documents().begin(); it != response.documents().end(); ++it){
	//std::cout << (*it)->toString() << std::endl;
	result+=(*it)->toString();
	result+=",";
      }

      // When the cursorID is 0, there are no documents left, so break out ...
      if (response.cursorID() == 0){
	break;
      }

      // Get the next bunch of documents
      response = cursor.next(connection);
    };
    result=result.substr(0,result.size()-1);
    result+="]";
    //std::cout<<result<<std::endl;
    return result;
  }
  std::string Mongodb::get_streams_of_rules_and_coll(const std::string & host,
						     int port,
						     const std::string & collection,
						     const std::string & rules,
						     const std::string & db_name){
    std::string result="[";
    Poco::MongoDB::Connection connection(host, port);
    //std::cout<<"collections "<<collection<<std::endl;
    Poco::MongoDB::Cursor cursor(db_name, collection);
    cursor.query().selector().addNewDocument("$query").add("rule", rules);
    cursor.query().returnFieldSelector().add("timestamp", 1);
    cursor.query().returnFieldSelector().add("rule", 1);
    cursor.query().returnFieldSelector().add("events", 1);
    cursor.query().returnFieldSelector().add("_id", 0);
    cursor.query().selector().addNewDocument("$orderby").add("timestamp", 1);

    Poco::MongoDB::ResponseMessage& response = cursor.next(connection);
    for (;;){
      for (Poco::MongoDB::Document::Vector::const_iterator it = response.documents().begin(); it != response.documents().end(); ++it){
	//std::cout << (*it)->toString() << std::endl;
	result+=(*it)->toString();
	result+=",";
      }
      if (response.cursorID() == 0){
	break;
      }
      response = cursor.next(connection);
    };
    result=result.substr(0,result.size()-1);
    result+="]";
    //std::cout<<result<<std::endl;
    return result;
  }
  std::string Mongodb::get_rules_of_collection(const std::string & host,
					       int port,
					       const std::string & collection,
					       const std::string & db_name){
    std::string result="";
    Poco::MongoDB::Connection connection(host, port);
    Poco::MongoDB::Database db(db_name);
    Poco::SharedPtr<Poco::MongoDB::QueryRequest> command = db.createCommand();
    command->selector().add("distinct", collection);
    command->selector().add("key", "rule");
    Poco::MongoDB::ResponseMessage response;
    connection.sendRequest(*command, response);
    if (response.hasDocuments()){
      result = response.documents()[0]->toString();
    }  
    //std::cout<<result<<std::endl;
    return result;
  }
  std::string Mongodb::get_streams_of_rules_and_coll_at_a_date(const std::string & host,
							       int port,
							       const std::string & collection,
							       const std::string & rules,
							       const std::string &date,
							       const std::string & db_name){
    Time time_1(date,"00:00:00.000");
    long timestamp=time_1.get_timestamp_ms();
    long timestamp2=timestamp+86400000;
    Poco::MongoDB::Document::Ptr gteltDoc=new Poco::MongoDB::Document;
    gteltDoc->add("$gte",timestamp);
    gteltDoc->add("$lt",timestamp2);

    //std::cout<<rules<<" "<<timestamp<<" "<<timestamp2<<std::endl;
    
    std::string result="[";
    Poco::MongoDB::Connection connection(host, port);
    //std::cout<<"collections "<<collection<<std::endl;
    Poco::MongoDB::Cursor cursor(db_name, collection);
    cursor.query().selector().addNewDocument("$query").add("rule", rules).add("timestamp",gteltDoc);
    cursor.query().returnFieldSelector().add("timestamp", 1);
    cursor.query().returnFieldSelector().add("rule", 1);
    cursor.query().returnFieldSelector().add("events", 1);
    cursor.query().returnFieldSelector().add("_id", 0);
    cursor.query().selector().addNewDocument("$orderby").add("timestamp", 1);

    Poco::MongoDB::ResponseMessage& response = cursor.next(connection);
    for (;;){
      for (Poco::MongoDB::Document::Vector::const_iterator it = response.documents().begin(); it != response.documents().end(); ++it){
      	//std::cout << (*it)->toString() << std::endl;
      	result+=(*it)->toString();
      	result+=",";
      }
      if (response.cursorID() == 0){
    	break;
      }
      response = cursor.next(connection);
    };
    if(result.compare("[")!=0)
      result=result.substr(0,result.size()-1);
    result+="]";
    //std::cout<<result<<std::endl;
    return result;
  }
  std::string Mongodb::get_rules_of_collection_at_a_date(const std::string & host,
							 int port,
							 const std::string & collection,
							 const std::string & date,
							 const std::string & db_name){

    //{ distinct:"_DomassistSzelengowicz",key:"rule",query:{'timestamp':{$gt:1496872800000,$lt:1495522970170000},'rule':{$ne:"raw"}}} 
  
    //{ find:"_DomassistSzelengowicz",filter:{'timestamp':{$gt:1496872800000,$lt:1495522970170000},'rule':{$ne:"raw"}}}
    Time time_1(date,"00:00:00.000");
    long timestamp=time_1.get_timestamp_ms();
    long timestamp2=timestamp+86400000;
    Poco::MongoDB::Document::Ptr gteltDoc=new Poco::MongoDB::Document;
    gteltDoc->add("$gte",timestamp);
    gteltDoc->add("$lt",timestamp2);
    Poco::MongoDB::Document::Ptr notRawDoc=new Poco::MongoDB::Document;
    notRawDoc->add("$ne","raw");
    Poco::MongoDB::Document::Ptr timestampDoc=new Poco::MongoDB::Document;
    timestampDoc->add("timestamp",gteltDoc);
    timestampDoc->add("rule",notRawDoc);
    
    std::string result="";
    Poco::MongoDB::Connection connection(host, port);
    Poco::MongoDB::Database db(db_name);
    Poco::SharedPtr<Poco::MongoDB::QueryRequest> command = db.createCommand();
    command->selector().add("distinct",collection);
    command->selector().add("key","rule");
    command->selector().add("query",timestampDoc);
  
    // command->selector().add("find", collection);
    // command->selector().add("filter", timestampDoc);
    Poco::MongoDB::ResponseMessage response;
    connection.sendRequest(*command, response);
    if (response.hasDocuments()){
      result = response.documents()[0]->toString();
    }  
    //std::cout<<result<<std::endl;
    return result;
  }

  std::string Mongodb::get_all_batteries_of_collection(const std::string & host,
						       int port,
						       const std::string & collection,
						       const std::string & db_name){


    Poco::MongoDB::Document::Ptr existDoc=new Poco::MongoDB::Document;
    existDoc->add("$exists",true);
    Poco::MongoDB::Document::Ptr batteryDoc=new Poco::MongoDB::Document;
    batteryDoc->add("BatteryLevel",existDoc);
    Poco::MongoDB::Document::Ptr matchDoc=new Poco::MongoDB::Document;
    matchDoc->add("$elemMatch",batteryDoc);
    // Poco::MongoDB::Document::Ptr Doc=new Poco::MongoDB::Document;
    // matchDoc->add("$elemMatch",batteryDoc);
    // Poco::MongoDB::Document::Ptr eventDoc=new Poco::MongoDB::Document;
    // eventDoc->add("events",roleDoc);
  

    int cpt=0;

    std::string result="[";
    Poco::MongoDB::Connection connection(host, port);
    //std::cout<<"collections "<<collection<<std::endl;
    Poco::MongoDB::Cursor cursor(db_name, collection);
    cursor.query().selector().addNewDocument("$query").add("rule", "raw").add("events",matchDoc);
    cursor.query().returnFieldSelector().add("timestamp", 1);
    cursor.query().returnFieldSelector().add("rule", 1);
    cursor.query().returnFieldSelector().add("events", 1);
    cursor.query().returnFieldSelector().add("_id", 0);
    //cursor.query().returnFieldSelector().add("events",matchDoc);
    cursor.query().selector().addNewDocument("$orderby").add("timestamp", 1);

    //db.getCollection('_45109619').find({rule:"raw", events: {"$elemMatch":{BatteryLevel :{$exists : true}}} })
    Poco::MongoDB::ResponseMessage& response = cursor.next(connection);
    for (;;){
      for (Poco::MongoDB::Document::Vector::const_iterator it = response.documents().begin(); it != response.documents().end(); ++it){
	cpt++;
	//std::cout << (*it)->toString() << std::endl;
	result+=(*it)->toString();
	result+=",";
      }
      if (response.cursorID() == 0){
	break;
      }
      response = cursor.next(connection);
    };
    if(cpt>0)
      result=result.substr(0,result.size()-1);
    result+="]";
    //std::cout<<result<<std::endl;
    return result;
  }
}
//db.getCollection('_Domassist0122').find({events:{$elemMatch: {role : { location : "Livingroom", kind : "Presence" } }}})

//db.getCollection('_Domassist0122').find({$or:[{rule:"noUbiquity"},{rule:"WebsocketEndWarning"}]})
