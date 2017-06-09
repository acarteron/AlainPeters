#include "requests/handleget.hh"
#include "Utils.hpp"
#include "database/mongodb.hh"
#include "files/files.hh"
#include <Poco/URI.h>

#include <iostream>

#include "html/html.hh"

HandleGet::HandleGet(){
}

void HandleGet::handleRequest(Poco::Net::HTTPServerRequest& request,
			      Poco::Net::HTTPServerResponse& response){
  poco_log("Request from " + request.clientAddress().toString()+" URI: "+request.getURI()+" content-type : "+request.getContentType());
  
  Poco::Net::HTMLForm form(request, request.stream()/*, partHandler*/);

  std::pair<std::string,std::string> res=switch_URI(request);
  
  response.setChunkedTransferEncoding(true);
  response.setContentType(res.first);
  
  std::ostream& ostr = response.send();
  ostr << res.second;
}
void HandleGet::poco_log(std::string log_){
  Poco::Util::Application& app = Poco::Util::Application::instance();
  app.logger().information(log_);
}

std::pair<std::string,std::string> HandleGet::switch_URI(Poco::Net::HTTPServerRequest& request){
  std::string URI_=request.getURI();
  // do a find rule in segment
  Poco::URI uri(request.getURI());
  std::vector < std::string >  segments;
  uri.getPathSegments(segments);
  for(size_t i(0);i<segments.size();++i)
    std::cout<<segments[i]<<std::endl;

  if(segments.size()==0){
    return std::make_pair("text/html",main_page());
  }
  
  //if(Utils::find_in_vector_str(segments,"collections")==0){

  //redo url mapping
  if(segments[0].compare("collections")==0&&segments.size()==1){
    return std::make_pair("application/json","{\"collections\":"+Mongodb::get_collections(mongo_host,mongo_port)+"}");
  }else{
    if(segments[0].compare("streams")==0&&segments.size()==2){
      return std::make_pair("application/json",get_streams_collection(segments[1]));
    }else{
      if(segments[0].compare("rules")==0&&segments.size()==2){
	return std::make_pair("application/json",
			      get_rules_list_collection(segments[1]));
      }else{
	if(segments[0].compare("streams")==0&&segments.size()==3){	  
	  return std::make_pair("application/json",
				get_streams_rules_collection(segments));
	}else{
	  if(segments[0].compare("batteries")==0&&segments.size()==2){	  
	    return std::make_pair("application/json",
				  get_all_batteries_of_collection(segments[1]));
	  }
	  return get_file(URI_);
	}
      }
    }    
  }
}
std::string HandleGet::get_streams_collection(std::string collection){
  std::string ret="{\"streams\":"+Mongodb::get_streams(mongo_host,mongo_port,collection)+"}";
  std::cout<<ret<<std::endl;
  return ret;
}
std::string HandleGet::get_all_batteries_of_collection(std::string collection){
  std::string ret="{\"streams\":"+Mongodb::get_all_batteries_of_collection(mongo_host,
									   mongo_port,
									   collection)+",\"user\":\""+collection+"\"}";
  return ret;
}
std::string HandleGet::get_rules_list_collection(std::string collection){
  std::string ret="{\"rules\":"+Mongodb::get_rules_of_collection(mongo_host,
								 mongo_port,
								 collection)+",\"user\":\""+collection+"\"}";
  return ret;
}
std::string HandleGet::get_streams_rules_collection(std::vector<std::string> segments){
  std::vector<std::string> seg2=Utils::splitString(segments[2],"&");
  std::string ret="{\"rules\":[";
  for(size_t i(0);i<seg2.size();++i){
    ret+="\""+seg2[i]+"\"";
    ret+=",";
  }
  ret=ret.substr(0,ret.size()-1);
  ret+="],";
  for(size_t i(0);i<seg2.size();++i){
    ret+="\""+seg2[i]+"\":"+Mongodb::get_streams_of_rules_and_coll(mongo_host,mongo_port,segments[1],seg2[i]);
    ret+=",";
   }
  ret=ret.substr(0,ret.size()-1);
  ret+="}";
  //std::cout<<ret<<std::endl;
  return ret;
}

std::pair<std::string,std::string> HandleGet::get_file(const std::string& path_){
  Files file;
  std::string file_path=".";
  std::string content_type="";
  if(path_.find("css")!=std::string::npos){
    content_type="text/css";
  }else{
    if(path_.find("js")!=std::string::npos)
      content_type="application/javascript";
    else{
      if(path_.find("html")!=std::string::npos)
        content_type="text/html";
      else{
        content_type="text/html";
      }
    }
  }
  if(path_.find("/libs")==std::string::npos)
    file_path+="/libs";
  file_path+=path_;
  file.setFileName(file_path);
  return std::make_pair(content_type,file.readFile());
}

std::string HandleGet::main_page(){
  html page;
  page.set_head("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
  page.set_head("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\">");
  page.set_head("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  page.set_head("<title>Maloya</title>\n");

  page.set_head("<script src=\"js/vendor/modernizr-2.8.3-respond-1.4.2.min.js\"></script>");
  
  page.set_css_link("//maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css");
  page.set_css_link("https://cdn.rawgit.com/FezVrasta/dropdown.js/master/jquery.dropdown.css");

  page.set_css_link("//fezvrasta.github.io/snackbarjs/dist/snackbar.min.css");
  page.set_script_link("//code.jquery.com/jquery-1.10.2.min.js");

  page.set_script_link("https://cdnjs.cloudflare.com/ajax/libs/numeric/1.2.6/numeric.min.js");
  page.set_script_link("libs/js/plotly.js");
  
  page.set_script_link("libs/js/Utils.js");
  page.set_script_link("libs/js/rn1.js");
  page.set_script_link("libs/js/Formular.js");
  page.set_script_link("libs/js/Modal.js");
  page.set_script_link("libs/js/Chart.js");
  page.set_script_link("libs/js/RuleChart.js");

  page.set_css_link("libs/css/bootstrap-material-design.css");
  page.set_css_link("libs/css/ripples.min.css");
  // page.set_css_link("libs/css/roboto.css");

  std::string begin="<html class=\"no-js\">";
  begin+=page.get_head();
  //<body onload="loadUsers() ">
  std::string navbar=R"(
<body >
<div class="navbar navbar-default">
<div class="container-fluid">
    <div class="navbar-header">
        <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-responsive-collapse">
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
        </button>
        <a class="navbar-brand" href="/">Maloya viewer</a>
    </div>
    <div class="navbar-collapse collapse navbar-responsive-collapse">
        <ul class="nav navbar-nav">
            <li><a href='javascript:loadUsers("rules")'>Users list</a></li>
            <li><a href='javascript:loadUsers("batteries")'>Batteries</a></li>
            <li><a href='javascript:loadUsers("allbatteries")'>All Batteries</a></li>

            <li><a href='javascript:void(0)'>Rules</a></li>
            
        </ul>
        
        <ul class="nav navbar-nav navbar-right">
            <li class="dropdown">
                <a href="bootstrap-elements.html" data-target="#" class="dropdown-toggle" data-toggle="dropdown">Menu <b class="caret"></b></a>
                <ul class="dropdown-menu">
                    <li><a href='javascript:void(0)'>void</a></li>
                    <li><a href='javascript:void(0)'>void</a></li>
                    <li><a href='javascript:void(0)'>void</a></li>
                    <li class="divider"></li>
                    <li class="dropdown-header">Admin</li>
                    <li><a href="">One more separated link</a></li>
                </ul>
            </li>
        </ul>
    </div>
</div>
</div>
<div class="container-fluid main"><div class="row"> 
<div id="about" class="well page active">
<div id="demo">
</div></div>
</div></div><div id="modals"></div>
    <script type="application/javascript" src="//cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.3.6/js/bootstrap.min.js"></script>
    <script type="application/javascript" src="https://cdn.rawgit.com/FezVrasta/dropdown.js/master/jquery.dropdown.js"></script>
    <script type="application/javascript" src="libs/js/material.js"></script>
    <script type="application/javascript" src="libs/js/ripples.min.js"></script>
     <script>
    	$.material.init();
  </script>
    </body></html>
      )";  
begin+=navbar;
return begin;
}
