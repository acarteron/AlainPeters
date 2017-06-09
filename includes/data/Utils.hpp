#ifndef DATA_UTILS_HH
#define DATA_UTILS_HH

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

namespace data{
  class Utils{
  public:
    static std::string extract_StreamType(const std::string & body,
					  const std::string & type){
      Poco::JSON::Parser      parser;
      Poco::Dynamic::Var      str_var;
      Poco::JSON::Object::Ptr str_obj;
      Poco::Dynamic::Var      streamevent_var;
      str_var = parser.parse(body);
      parser.reset();
      str_obj = str_var.extract<Poco::JSON::Object::Ptr>();
      streamevent_var = str_obj->get(type);
      return streamevent_var.toString();
    }
  };
};

#endif // DATA_UTILS_HH
