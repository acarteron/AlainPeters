#ifndef DATA_UTILS_HH
#define DATA_UTILS_HH

//#include <nlohmann/json.hpp>
#include <json.hpp>

namespace data{
  class Utils{
  public:
    static std::string extract_StreamType(const std::string & body,
					  const std::string & type){
      nlohmann::json j=nlohmann::json::parse(body);
      return j[type].dump();
    }
  };
};

#endif // DATA_UTILS_HH
