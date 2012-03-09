%{
#include "ast.hh"
#include <iostream>
#include "lexer.hh"

extern void yyerror(const char *);
int yylex();

%}


%union {
  
  Ast::Program *prog;
  Ast::ExtDecl *extDecl;
  Ast::FuncDef *funcDef;
  Ast::Declaration *declaration;
  Ast::Typ *typ;
  Ast::Declarator *declr;
  Ast::DeclrList *declrList;
  Ast::Parameters *parameters;
  Ast::ParamDecl *paramDecl;
  Ast::AbsDecl *absDecl;
  Ast::Block *blk;
  Ast::StatementList *statementList;
  Ast::DeclList *declList;
  Ast::Statement *statement;
  Ast::ArgumentList *argumentList;
  Ast::ExprStmt *exprStmt;
  Ast::Expression *expression;
  Ast::AsgnExpr *asgnExpr;
  Ast::AsgnOp *asgnOp;
  Ast::BinaryExp<Ast::BinEx::Or> *orExpr;
  Ast::BinaryExp<Ast::BinEx::And> *andExpr;
  Ast::BinaryExp<Ast::BinEx::Eq> *eqExpr;
  Ast::BinaryExp<Ast::BinEx::Rel> *relExpr;
  Ast::BinaryExp<Ast::BinEx::Add> *addExpr;
  Ast::BinaryExp<Ast::BinEx::Mul> *mulExpr;
  Ast::UnaryExpr *unaryExpr;
  Ast::PostfixExpr *postfixExpr;
  Ast::PrimaryExpr *primaryExpr;

  int intval;
  const char *strval;
}

%token<strval> IDENTIFIER
%token<intval> INTEGER
%token INC DEC
%token EQ GE LE NE
%token AND OR
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN
%token<intval> TYPE STRUCT
%token BREAK DO ELSE FOR IF RETURN WHILE

%type<prog> program
%type<extDecl> ext_decl
%type<funcDef> func_def
%type<declaration> decl
%type<typ> type
%type<declr> declarator
%type<declrList> declarator_list
%type<parameters> params
%type<paramDecl> param_decl
%type<absDecl> abs_decl
%type<blk> block
%type<statementList> stmts
%type<declList> decls
%type<statement> stmt
%type<argumentList> args
%type<exprStmt> expr_stmt
%type<expression> expr
%type<asgnExpr> asgn_expr
%type<asgnOp> asgn_op
%type<orExpr> or_expr
%type<andExpr> and_expr
%type<eqExpr> eq_expr
%type<relExpr> rel_expr
%type<addExpr> add_expr
%type<mulExpr> mul_expr
%type<unaryExpr> unary_expr
%type<postfixExpr> postfix_expr
%type<primaryExpr> primary_expr


%start program

%%

program
        : ext_decl 
	{
	  if($$ == NULL) 
	  {
	    $$ = new Ast::Program($1); 
	  }
	  else
	  {
	    $$->addExtDecl($1);
	  }
	}
	| program ext_decl
	{
	  if($$ == NULL) 
	  {
	    $$ = new Ast::Program($2); 
	  }
	  else
	  {
	    $$->addExtDecl($2);
	  }
	}
	;

ext_decl
	: func_def
	{
	  $$ = new Ast::ExtDecl($1);
	}
	| decl
	{
	  $$ = new Ast::ExtDecl($1);
	}
	;

func_def
	: type declarator block
	{
	  $$ = new Ast::FuncDef($1, $2, $3);
	}
	;

decl
	: type ';'
	{
	  $$ = new Ast::Declaration($1);
	}
	| type declarator_list ';'
	{
	  $$ = new Ast::Declaration($1, $2);
	}
	;

type
	: TYPE
	{
	  $$ = new Ast::Typ($1);
	}
	| STRUCT '{' decls '}'
	{
	  $$ = new Ast::Typ($3);
	}
	| STRUCT IDENTIFIER '{' decls '}'
	{
	  $$ = new Ast::Typ($2, $4);
	}
	| STRUCT IDENTIFIER
	{
	  $$ = new Ast::Typ($2);
	}
	;

declarator
	: IDENTIFIER
	{
	  $$ = new Ast::Declarator($1);
	}
	| declarator '[' ']'
	{
	  $$ = new Ast::Declarator($1, new Ast::ArrayDec());
	}
	| declarator '[' expr ']'
	{
	  $$ = new Ast::Declarator($1, new Ast::ArrayDec($3));
	}
	| IDENTIFIER '(' ')'
	{
	  $$ = new Ast::Declarator($1, new Ast::FuncParam());
	}
	| IDENTIFIER '(' params ')'
	{
	  $$ = new Ast::Declarator($1, new Ast::FuncParam($3));
	}
	;

declarator_list
	: declarator
	{
	  $$ = new Ast::DeclrList($1);
	}
	| declarator '=' asgn_expr
	{
	  $$ = new Ast::DeclrList($1, $3);
	}
	| declarator_list ',' declarator
	{
	  $$ = new Ast::DeclrList($1, $3);
	}
	;

params
	: param_decl
	{
	  $$ = new Ast::Parameters($1);
	}
	| params ',' param_decl
	{
	  $$ = new Ast::Parameters($1, $3);
	}
	;

param_decl
	: type declarator
	{
	  $$ = new Ast::ParamDecl($1, $2);
	}
	| type abs_decl
	{
	  $$ = new Ast::ParamDecl($1, $2);
	}
	| type
	{
	  $$ = new Ast::ParamDecl($1);
	}
	;

abs_decl
	: '[' ']'
	{
	  $$ = new Ast::AbsDecl();
	}
	;

block
	: '{' '}'
	{
	  $$ = new Ast::Block();
	}
	| '{' stmts '}'
	{
	  $$ = new Ast::Block($2);
	}
	;

stmts
	: stmt
	{
	  $$ = new Ast::StatementList($1);
	}
	| stmts stmt
	{
	  $$ = new Ast::StatementList($1, $2);
	}
	;

decls
	: decl
	{
	  $$ = new Ast::DeclList($1);
	}
	| decls decl
	{
	  $$ = new Ast::DeclList($1, $2);
	}
	;

stmt
	: block
	{
	  $$ = new Ast::BasicStatement($1);
	}
	| decl
	{
	  $$ = new Ast::BasicStatement($1);
	}
	| expr_stmt
	{
	  $$ = new Ast::BasicStatement($1);
	}
	| IF '(' expr ')' stmt
	{
	  $$ = new Ast::IfStatement($3, $5);
	}
	| IF '(' expr ')' stmt ELSE stmt
	{
	  $$ = new Ast::IfStatement($3, $5, $7);
	}
	| WHILE '(' expr ')' stmt
	{
	  $$ = new Ast::WhileStatement($3, $5);
	}
	| DO stmt WHILE '(' expr ')' ';'
	{
	  $$ = new Ast::DoStatement($2, $5);
	}
	| FOR '(' expr_stmt expr_stmt expr ')' stmt
	{
	  $$ = new Ast::ForStatement($3, $4, $5, $7);
	}
	| RETURN expr ';'
	{
	  $$ = new Ast::ReturnStatement($2);
	}
	;

args
	: asgn_expr
	{
	  $$ = new Ast::ArgumentList($1);
	}
	| args ',' asgn_expr
	{
	  $$ = new Ast::ArgumentList($1, $3);
	}
	;

expr_stmt
	: ';'
	{
	  $$ = new Ast::ExprStmt();
	}
	| expr ';'
	{
	  $$ = new Ast::ExprStmt($1);
	}
	;

expr
	: asgn_expr
	{
	  $$ = new Ast::Expression($1);
	}
	| expr ',' asgn_expr
	{
	  $$ = new Ast::Expression($1, $3);
	}
	;

asgn_expr
	: or_expr
	{
	  $$ = new Ast::AsgnExpr($1);
	}
	| unary_expr asgn_op asgn_expr
	{
	  $$ = new Ast::AsgnExpr($1, $2, $3);
	}
	;
asgn_op
	: '='
	{
	  $$ = new Ast::AsgnOp();
	}
	| ADD_ASSIGN
	{
	  $$ = new Ast::AsgnOp('+');
	}
	| SUB_ASSIGN
	{
	  $$ = new Ast::AsgnOp('-');
	}
	| MUL_ASSIGN
	{
	  $$ = new Ast::AsgnOp('*');
	}
	| DIV_ASSIGN
	{
	  $$ = new Ast::AsgnOp('*');
	}
	;

or_expr
	: and_expr
	{
	  $$ = Ast::BinExFactory::CreateOr($1);
	}
	| or_expr OR and_expr
	{
	  $$ = Ast::BinExFactory::CreateOr($1, $3);
	}
	;

and_expr
	: eq_expr
	{
	  $$ = Ast::BinExFactory::CreateAnd($1);
	}
	| and_expr AND eq_expr
	{
	  $$ = Ast::BinExFactory::CreateAnd($1, $3);
	}
	;

eq_expr
	: rel_expr
	{
	  $$ = Ast::BinExFactory::CreateEq($1);
	}
	| eq_expr EQ rel_expr
	{
	  $$ = Ast::BinExFactory::CreateEq($1, $3, true);
	}
	| eq_expr NE rel_expr
	{
	  $$ = Ast::BinExFactory::CreateEq($1, $3, false);
	}
	;

rel_expr
	: add_expr
	{
	  $$ = Ast::BinExFactory::CreateRel($1);
	}
	| rel_expr '<' add_expr
	{
	  $$ = Ast::BinExFactory::CreateRel($1, $3, "<");
	}
	| rel_expr '>' add_expr
	{
	  $$ = Ast::BinExFactory::CreateRel($1, $3, ">");
	}
	| rel_expr LE add_expr
	{
	  $$ = Ast::BinExFactory::CreateRel($1, $3, "<=");
	}
	| rel_expr GE add_expr
	{
	  $$ = Ast::BinExFactory::CreateRel($1, $3, ">=");
	}
	;

add_expr
	: mul_expr
	{
	  $$ = Ast::BinExFactory::CreateAdd($1);
	}
	| add_expr '+' mul_expr
	{
	  $$ = Ast::BinExFactory::CreateAdd($1, $3, '+');
	}
	| add_expr '-' mul_expr
	{
	  $$ = Ast::BinExFactory::CreateAdd($1, $3, '-');
	}
	;

mul_expr
	: unary_expr
	{
	  $$ = Ast::BinExFactory::CreateMul($1);
	}
	| mul_expr '*' unary_expr
	{
	  $$ = Ast::BinExFactory::CreateMul($1, $3, '*');
	}
	| mul_expr '/' unary_expr
	{
	  $$ = Ast::BinExFactory::CreateMul($1, $3, '/');
	}
	| mul_expr '%' unary_expr
	{
	  $$ = Ast::BinExFactory::CreateMul($1, $3, '%');
	}
	;

unary_expr
	: postfix_expr
	{
	  $$ = new Ast::UnaryExpr($1);
	}
	| INC unary_expr
	{
	  $$ = new Ast::UnaryExpr($2, "++");
	}
	| DEC unary_expr
	{
	  $$ = new Ast::UnaryExpr($2, "--");
	}
	| '-' unary_expr
	{
	  $$ = new Ast::UnaryExpr($2, "-");
	}
	;

postfix_expr
	: primary_expr
	{
	  $$ = new Ast::PostfixExpr($1);
	}
	| postfix_expr '[' expr ']'
	{
	  $$ = new Ast::PostfixExpr($1, $3);
	}
	| postfix_expr '(' ')'
	{
	  $$ = new Ast::PostfixExpr($1);
	}
	| postfix_expr '(' args ')'
	{
	  $$ = new Ast::PostfixExpr($1, $3);
	}
	| postfix_expr '.' IDENTIFIER
	{
	  $$ = new Ast::PostfixExpr($1, $3);
	}
	| postfix_expr INC
	{
	  $$ = new Ast::PostfixExpr($1, "++");
	}
	| postfix_expr DEC
	{
	  $$ = new Ast::PostfixExpr($1, "--");
	}
	;

primary_expr
	: IDENTIFIER
	{
	  $$ = new Ast::PrimaryExpr($1);
	}
	| INTEGER
	{
	  $$ = new Ast::PrimaryExpr($1);
	}
	| '(' expr ')'
	{
	  $$ = new Ast::PrimaryExpr($2);
	}
	;

%%
