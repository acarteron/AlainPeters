#include "files/files.hh"

Files::Files(){
  openingMode="in";
}

// Ouverture en lecture 
Files::Files(std::string file){
  openingMode="in";
  setFileName(file);
  //create_File();
}
Files::Files(std::string file,std::string mode){
  //fileName=file;
  openingMode=mode;
  setFileName(file);
  //create_File();
}
Files::~Files(){
  closeFile();
}
void Files::setFileName(std::string file){
  fileName=file;
  create_File();
}


void Files::create_File(){
  if(openingMode=="out"){
    curentFileO.open(fileName.c_str(),std::fstream::out);  
  }
  else{
    curentFile.open(fileName.c_str(),std::fstream::in);
  }
}
int Files::openFile(){
  if(openingMode=="out"){
    return curentFileO.is_open();
  }
  else{
    return curentFile.is_open();
   
  }
}
int Files::closeFile(){
  if(openingMode=="out")
    curentFileO.close();
  else
    curentFile.close();
 return 0;
}
std::string Files::readFile(){
  std::stringstream sstr;
  sstr << curentFile.rdbuf();
  return sstr.str();
}
int Files::writeFile(std::string message){
  curentFileO << message;
  return -1;
}
std::string Files::readLine(){
  std::string line="";
  getline (curentFile,line);
  if(curentFile.eof())
    line="NONEEOFLOL";
  return line;
}
