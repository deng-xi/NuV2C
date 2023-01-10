#ifndef CPROVER_EXPRESSION_DATATYPE_H
#define CPROVER_EXPRESSION_DATATYPE_H

#include <ansi-c/expr2c_class.h>

class datatypet:public expr2ct
{
public:
  datatypet(const namespacet &_ns):expr2ct(_ns) {}
  virtual ~datatypet() { }

protected:
  virtual std::string convert_rec(
    const typet &src,
    const c_qualifierst &qualifiers,
    const std::string &declarator);

};

#endif
