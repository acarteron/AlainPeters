#ifndef HTML_HH
#define HTML_HH

#include <string>
#include <vector>

#include "files/files.hh"

class html{
private:
  std::string page;

  std::vector<std::string> header;
  std::vector<std::string> body;

  Files file;

  void open_file(std::string filename_);
  void close_file();
  
public:
  void set_css_link(std::string/*,unsigned int */ );
  void set_style(std::string/*,unsigned int */ );
  void set_script(std::string/*, unsigned int*/);
  void set_script_link(std::string/*, unsigned int*/);
  void set_head(std::string);

  std::string get_head();
  
};

#endif
