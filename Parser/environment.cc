#include "environment.h"

using std::string;
using std::map;

Symbol::Symbol(string name, int typ, string value)
  :name(name),
   typ(typ),
   value(value)
{  }

Symbol::Symbol()
  :name(""),
   typ(-1),
   value("")
{  }

Environment::Environment(Environment *prev)
  :table(),
   prev(prev)
{  }
