/* Definitions */
%{
	#include "y.tab.h"    
    #include <stdio.h>
    
    void comment();
    
%}

L [A-Za-z_]
D [0-9]
D1 [1-9]
H [0-9a-fA-F_]

BAD [#|%|~]
STRING L?\"(\\.|[^\\"])*\"



%%

"/*" { comment(); }

"|" return '|';
"+" return '+';
";" return ';';
"!" return '!';
"-" return '-';
"*" return '*';
"." return '.';
"," return ',';
"=" return '=';
"[" return '[';
"]" return ']';
"(" return '(';
")" return ')';
"}" return '}';
"{" return '{';
":" return ':';
"%" return '%';
"^" return '^';
"&" return '&';
"~" return '~';
"/=" return DIVEQ;
"%=" return MODEQ;
"+=" return ADDEQ;
"-=" return SUBEQ;
"<<=" return SLEQ;
">>=" return SREQ;
"&=" return ANDEQ;
"^=" return CAREQ;
"|=" return PIPEQ;
"*=" return MULEQ;
"++" return INCR;
"--" return DECR;
"->" return PTRDR;
"bool" return BOOL;
"break" return BREAK;
"if" return IF;
"else" return ELSE;
"int" return INTEGER;
"return" return RETURN;
"struct" return STRUCT;
"void" return VOID;
"char" return CHAR;
"while" return WHILE;
"continue" return CONTINUE;
"do" return DO;
"for" return FOR;
{L}({L}|{D})* return ID;
"<=" return LE;
">=" return GE;
"==" return EQ;
"!=" return NE;
"<" return LT;
">" return GT;
"&&" return AND;
"||" return OR;
"<<" return SHIFTL;
">>" return SHIFTR;
{D1}({D})* return DECIMAL;
"0" return DECIMAL;
0({D})* return OCTAL;
0x({H})* return HEX;
{BAD} return BAD;
{STRING} return STRING;
"/" {  }
[ \t\v\n\f]  {  }
L?'(\\.|[^\\'])+'	{ return STRING; }

%%
/* Subroutines  */

int yywrap(void) {
    return 1;
}

void comment()
{
	char c, c1;
    
    loop:
	while ((c = yyinput()) != '*' && c != 0) 
    {  
        //putchar(c);
    }
        
	if ((c1 = yyinput()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}
    
	//if (c != 0)
    //putchar(c1);
}

/*int main(void) {
 printf("Hi",1);
 yylex();
 return 0;
 }*/