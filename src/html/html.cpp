#include "html/html.hh"

void html::open_file(std::string filename_){
  file.setFileName(filename_);
  file.openFile();
}
void html::close_file(){
  file.closeFile();
}

void html::set_css_link(std::string css_/*,unsigned int pound_=1 */){
  std::string css="<link rel=\"stylesheet\" href=\"";
  css+=css_;
  css+="\">\n";
  header.push_back(css);
  // else
  //   header.insert(header.begin(),css);
}
void html::set_style(std::string css_/*,unsigned int pound_=1 */){
  open_file(css_);
  std::string css="<style>\n";
  css+=file.readFile();  
  css+="</style>\n";
  header.push_back(css);
  close_file();
}
void html::set_script(std::string script_/*, unsigned int pound_=1*/){
  open_file(script_);
  std::string script="<script type=\"application/javascript\">\n";
  script+=file.readFile(); 
  script+="</script>\n";
  header.push_back(script);
  close_file();
}
void html::set_script_link(std::string script_/*, unsigned int pound_=1*/){
  std::string style="<script src=\"";
  style+=script_;
  style+="\" type=\"application/javascript\"></script>\n";
  header.push_back(style);
}
void html::set_head(std::string head_){
  header.emplace(header.begin(),head_);
}


std::string html::get_head(){
  std::string head="<head>\n";
  for(size_t i(0);i<header.size();++i)
    head+=header[i];
  head+="</head>\n";
  return head;
}
