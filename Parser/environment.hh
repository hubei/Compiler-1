#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <map>
#include <string>

class Symbol
{
 public:
  std::string name;
  int typ;
  std::string value;

  Symbol(std::string name, int type, std::string value);
  Symbol();

};

class Environment
{
 public:
  std::map<std::string, Symbol> table;
  Environment *prev;

  Environment(Environment *prev = NULL);
};


#endif
