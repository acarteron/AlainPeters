/**
 * \class database/mongodb
 *
 * \brief 
 *
 * \note 
 *
 * \author Adrien Carteron
 *
 * \version 0.1 
 *
 * \date lun. mai 29 16:22:05 CEST 2017 
 *
 * Contact: acarteron@openmailbox.org
 *
 * Created on: lun. mai 29 16:22:05 CEST 2017
 *
 *
 */

#ifndef MONGODB_HH
#define MONGODB_HH

//#include "data/streamevent.hh"

#include <vector>
#include <Poco/MongoDB/Document.h>

class Mongodb{

private:
  static const std::string db_name;

  //static Poco::MongoDB::Document::Ptr build_stream_document(StreamEvent&);
public:
  /** \brief Void constructor
   * 
   * add desc 
   * 
   */
  Mongodb();

  static std::string get_collections(const std::string &,
				     int);
  static std::string get_streams(const std::string &,
				 int,
				 const std::string &);
  static std::string get_streams_of_rules_and_coll(const std::string &,
						   int,
						   const std::string &,
						   const std::string &);
  static std::string get_streams_of_rules_and_coll_at_a_date(const std::string &,
							     int,
							     const std::string &,
							     const std::string &,
							     const std::string&);
  static std::string get_rules_of_collection(const std::string &,
					     int,
					     const std::string &);
  static std::string get_rules_of_collection_at_a_date(const std::string &,
						       int,
						       const std::string &,
						       const std::string &);

 
  static std::string get_all_batteries_of_collection(const std::string &,
						     int,
						     const std::string &);
  
};

#endif // MONGODB_HH
