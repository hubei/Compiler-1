//
//  Parser.cpp
//  CCompiler
//
//  Created by Ryan Goodfellow on 2/12/12.
//  Copyright (c) 2012 Washington State University. All rights reserved.
//

#include "parser.hh"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char** argv)
{
    if(argc < 1)
    {
      cout << "Please provide input file" << endl;
    }

    string infile = string(argv[1]);
    cout << "infile: " << infile << endl;
    
    Parser p;
    p.Parse(infile);
}

void yyerror(const char*s)
{
    cout << "ERROR!:->  " << endl;
    cout << "line: " << yylineno << endl;
    cout << s << "token: " << yytext << endl;
}


int Parser::Parse(string sourceFile)
{
    cout << "Parsing file: " << sourceFile << endl;
    yyin = fopen(sourceFile.c_str(), "r");
    
    yyparse();
    
    
    return 0;
}

Parser::Parser()
{
    
}




