//
//  Parser.h
//  CCompiler
//
//  Created by Ryan Goodfellow on 2/12/12.
//  Copyright (c) 2012 Washington State University. All rights reserved.
//

#ifndef CCompiler_Parser_h
#define CCompiler_Parser_h

#include <iostream>
#include <fstream>
#include <string>

void yyerror(char*s);

#include "ast.hh"
#include "y.tab.h"
#include "lexer.hh"

class Parser
{
public:
    Parser();
    int Parse(std::string sourceFile);
};

#endif
