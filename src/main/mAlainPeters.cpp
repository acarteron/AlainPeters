#include <iostream>
#include "libAlainPeters.hh"
int main(int argc, char** argv){
  std::string date="2017-08-03";
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

