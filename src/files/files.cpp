#include "files/files.hh"
namespace apeters{
File::File(){
  openingMode="in";
}

// Ouverture en lecture 
File::File(std::string file){
  openingMode="in";
  setFileName(file);
  //create_File();
}
File::File(std::string file,std::string mode){
  //fileName=file;
  openingMode=mode;
  setFileName(file);
  //create_File();
}
File::~File(){
  closeFile();
}
void File::setFileName(std::string file){
  fileName=file;
  create_File();
}


void File::create_File(){
  if(openingMode=="out"){
    curentFileO.open(fileName.c_str(),std::fstream::out);  
  }
  else{
    curentFile.open(fileName.c_str(),std::fstream::in);
  }
}
int File::openFile(){
  if(openingMode=="out"){
    return curentFileO.is_open();
  }
  else{
    return curentFile.is_open();
   
  }
}
int File::closeFile(){
  if(openingMode=="out")
    curentFileO.close();
  else
    curentFile.close();
 return 0;
}
std::string File::readFile(){
  std::stringstream sstr;
  sstr << curentFile.rdbuf();
  return sstr.str();
}
int File::writeFile(std::string message){
  curentFileO << message;
  return -1;
}
std::string File::readLine(){
  std::string line="";
  getline (curentFile,line);
  if(curentFile.eof())
    line="NONEEOFLOL";
  return line;
}
}
