#ifndef VERILOG_PREPROCESSOR_H
#define VERILOG_PREPROCESSOR_H

#include <list>

#include <util/hash_cont.h>
#include <util/irep.h>
#include <util/string_hash.h>
#include <util/preprocessor.h>

class verilog_preprocessort:public preprocessort
{
public:
  virtual void preprocessor();

  verilog_preprocessort(
    std::istream &_in,
    std::ostream &_out,
    message_handlert &_message_handler,
    const std::string &_filename):
    preprocessort(_in, _out, _message_handler, _filename)
  {
    condition=true;
  }

  virtual ~verilog_preprocessort() { }

protected:
  typedef hash_map_cont<std::string, std::string, string_hash>
    definest;
    
  definest defines;
  
  virtual void directive();
  virtual void replace_macros(std::string &s);
  virtual void include(const std::string &filename);

  static std::string build_path(
    const std::string &path,
    const std::string &filename);
  
  // for ifdef, else, endif
  
  bool condition;
  
  class conditionalt
  {
  public:
    bool condition;
    bool previous_condition;
    bool else_part;
    
    conditionalt()
    { else_part=false; }
     
    bool get_cond()
    {
      return previous_condition &&
             (else_part?(!condition):condition);
    }
  };

  std::list<conditionalt> conditionals;

  // for include

  class filet
  {
  public:
    bool close;
    std::istream *in;
    std::string filename;
    unsigned line, last_line;
    
    filet() { close=false; line=1; last_line=0; column=1; }
    ~filet() { if(close) delete in; }
    
    bool get(char &ch);
    void getline(std::string &dest);

    // a minimal scanner
    
    typedef enum { INITIAL, C_COMMENT, CPP_COMMENT,
                   DASH, C_COMMENT2 } statet;
    
    statet state;  
    unsigned column;
    bool cpp_comment_empty;

    void print_line(std::ostream &out, unsigned level)
    { out << "`line " << line << " \"" 
          <<filename << "\" " << level << std::endl; }
  };

  std::list<filet> files;  
};

#endif
