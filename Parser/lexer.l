%{
#include "ast.hh"
#include "y.tab.h"
#include "lexer.hh"

%}

D	[0-9]
H	[0-9A-Fa-f]
L	[A-Za-z_]

%%
"/*"([^\*]|\*[^/])*"*/"	{}

"_Bool"		{ yylval.intval = T_BOOL; return TYPE; }
"break"		return BREAK;
"char"		{ yylval.intval = T_CHAR; return TYPE; }
"do"		return DO;
"else"		return ELSE;
"for"		return FOR;
"if"		return IF;
"int"		{ yylval.intval = T_INT; return TYPE; }
"return"	return RETURN;
"struct"	return STRUCT;
"void"		{ yylval.intval = T_VOID; return TYPE; }
"while"		return WHILE;

{L}({L}|{D})*	{ yylval.strval = yytext; return IDENTIFIER; }
"0"{D}+		{
			yylval.intval = (int)strtol(yytext + 1, NULL, 8);
			return INTEGER;
		}
"0x"{H}+	{
			yylval.intval = (int)strtol(yytext + 2, NULL, 16);
			return INTEGER;
		}
{D}+		{
			yylval.intval = (int)strtol(yytext, NULL, 10);
			return INTEGER;
		}
'[^\\']'	{ yylval.intval = (int)yytext[1]; return INTEGER; }
'\\.'		{
			yylval.intval = (int)strtol(yytext + 1, NULL, 8);
			return INTEGER;
		}

"+="		return ADD_ASSIGN;
"-="		return SUB_ASSIGN;
"*="		return MUL_ASSIGN;
"/="		return DIV_ASSIGN;
"++"		return INC;
"--"		return DEC;
"&&"		return AND;
"||"		return OR;
"<="		return LE;
">="		return GE;
"=="		return EQ;
"!="		return NE;
";"		return ';';
"{"		return '{';
"}"		return '}';
","		return ',';
":"		return ':';
"="		return '=';
"("		return '(';
")"		return ')';
"["		return '[';
"]"		return ']';
"."		return '.';
"-"		return '-';
"+"		return '+';
"*"		return '*';
"/"		return '/';
"%"		return '%';
"<"		return '<';
">"		return '>';
"!"		return '!';

[ \t]		;
"\n"		yylineno++;
.		yyerror("invalid input");

%%

int
yywrap()
{
	return 1;
}
