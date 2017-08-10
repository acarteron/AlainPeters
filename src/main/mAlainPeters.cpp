#include <iostream>
#include "libAlainPeters.hh"

#include "database/mongodb.hh"
int main(int argc, char** argv){
  /*	std::cout<<apeters::Mongodb::get_collections("172.18.0.2",27017,"Streams")<<std::endl;
	apeters::Mongodb::remove_rules("172.18.0.2",27017,"global","rules","breakfast");
	std::cout<<apeters::Mongodb::get_rules("172.18.0.2",27017,"global","rules")<<std::endl;
	std::cout<<apeters::Mongodb::get_streams("172.18.0.2",27017,"_DomassistLafon","Streams")<<std::endl;
	std::cout<<"get rule collection "<<apeters::Mongodb::get_rules_of_collection("172.18.0.2",27017,"_DomassistLafon","Streams")<<std::endl;
	std::cout<<"get stream date "<<apeters::Mongodb::get_streams_of_rules_and_coll_at_a_date("172.18.0.2",27017,"_DomassistLafon","DoorAlert","2017-08-10","Streams")<<std::endl;
	std::cout<<"get rule collection date "<<apeters::Mongodb::get_rules_of_collection_at_a_date("172.18.0.2",27017,"_DomassistLafon","2017-08-10","Streams")<<std::endl;*/
  std::string date="2017-08-10";
  libAlainPeters liba;
  liba.do_what_you_do(date);
  std::cout<<"Daily Report:"<<std::endl;
  std::cout<<liba.getDailyReport_as_string()<<std::endl;
	
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

