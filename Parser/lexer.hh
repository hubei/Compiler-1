#ifndef _LEXER_HH_
#define _LEXER_HH_

enum {
  T_BOOL,
  T_CHAR,
  T_INT,
  T_VOID,
  T_ARRAY,
  T_STRUCT,
  T_STRUCT_DEF,
  T_FUNC
};

extern int yylineno;
extern char* yytext;
//extern YYSTYPE yylval;
extern FILE* yyin;
extern int yyparse(void);
extern void yyerror(const char*);

/*
extern "C" {
  void yyerror(const char *);
  //int yyparse(void);
}*/

#endif // !_LEXER_HH_
