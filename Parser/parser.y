%{
  #include <stdio.h>
  #include "environment.h"

  Environment *top;
  Environment *saved;
  Symbol s;

%}

%token STRING
%token BOOL
%token BREAK
%token IF
%token ELSE
%token INTEGER
%token RETURN
%token STRUCT
%token VOID
%token WHILE
%token CHAR
%token ID
%token SPECIAL
%token DO
%token AND
%token OR
%token LT
%token GT 
%token LE
%token GE
%token EQ
%token NE
%token DECIMAL
%token OCTAL
%token HEX
%token BAD
%token FOR
%token ';'
%token '+'
%token '!'
%token '-'
%token '*'
%token '.'
%token ','
%token '='
%token '['
%token ']'
%token ')'
%token '('
%token '{'
%token '}'
%token ':'
%token '|'
%token '^'
%token '&'
%token '~'
%token MULEQ
%token DIVEQ
%token MODEQ
%token ADDEQ
%token SUBEQ
%token SLEQ
%token SREQ
%token ANDEQ
%token CAREQ
%token PIPEQ
%token SHIFTL
%token SHIFTR
%token INCR
%token DECR
%token PTRDR
%token CONTINUE


%start tunit

%%


tunit                   : begin          { top = NULL; }
                        | tunit begin    { top = NULL; }
;

begin                   : function_definition     //nothing
                        | decl                    //nothing
;

                                                                            //Function def complete add
                                                                            //it to current symbol table
function_definition     : decl_specs declarator decl_list compound_stat     { top->table[s.name] = s; }
                        |            declarator decl_list compound_stat     { top->table[s.name] = s; }
                        | decl_specs declarator           compound_stat     { top->table[s.name] = s; }
                        |            declarator           compound_stat     { top->table[s.name] = s; }
;

decl                    : decl_specs init_declarator_list ';'     { top->table[s.name] = s; }
                        | decl_specs                      ';'     { top->table[s.name] = s; }
;

decl_list               : decl
                        | decl_list decl
;

decl_specs              : type_spec 
                        | type_spec decl_specs
;

type_spec               : struct_spec | VOID | CHAR | INTEGER | BOOL
;

struct_spec             : STRUCT ID '{' struct_decl_list '}'
                        | STRUCT    '{' struct_decl_list '}'
                        | STRUCT ID
;

struct_decl_list        : struct_decl
                        | struct_decl_list struct_decl
;

init_declarator_list    : init_declarator
                        | init_declarator_list ',' init_declarator
;

init_declarator         : declarator
                        | declarator '=' initializer
;

struct_decl             : spec_qualifier_list declarator_list ';'
;

spec_qualifier_list     : type_spec spec_qualifier_list
                        | type_spec
;

declarator_list         : declarator
                        | declarator_list ',' declarator
;

declarator              : pointer direct_declarator
                        |         direct_declarator
;

direct_declarator       : ID
                        | '(' declarator ')'                      
                        | direct_declarator '[' const_exp ']'
                        | direct_declarator '['           ']'
                        | direct_declarator '(' param_list ')'
                        | direct_declarator '(' id_list ')'
                        | direct_declarator '('         ')'
;

pointer                 : '*'                        
                        | '*' pointer
;

param_list              : param_decl
                        | param_list ',' param_decl
;

param_decl              : decl_specs declarator
                        | decl_specs abstract_declarator
                        | decl_specs
;

id_list                 : ID
                        | id_list ',' ID
;

initializer             : assignment_exp
                        | '{' initializer_list '}'
                        | '{' initializer_list ',' '}'
;

initializer_list        : initializer
                        | initializer_list ',' initializer
;

type_name               : spec_qualifier_list abstract_declarator
                        | spec_qualifier_list
;

abstract_declarator     : pointer
                        | pointer direct_abstract_declarator
                        |         direct_abstract_declarator
;

direct_abstract_declarator: '(' abstract_declarator ')'
                        | direct_abstract_declarator '[' const_exp ']'
                        |                            '[' const_exp ']'
                        | direct_abstract_declarator '['           ']'
                        |                            '['           ']'
                        | direct_abstract_declarator '(' param_list ')'
                        |                            '(' param_list ')'
                        | direct_abstract_declarator '('            ')'
                        |                            '('            ')'
;

type_name               : ID
;

stat                    : exp_stat
                        | compound_stat
                        | selection_stat
                        | iteration_stat
                        | jump_stat
;

exp_stat                : exp ';'
                        |     ';'
;

compound_stat           : '{' decl_list stat_list '}'    { saved = top; top = new Environment(saved); }
                        | '{'           stat_list '}'    { saved = top; top = new Environment(saved); }
                        | '{' decl_list           '}'    { saved = top; top = new Environment(saved); }
                        | '{'                     '}'    { saved = top; top = new Environment(saved); }
;

stat_list               : stat
                        | stat_list stat
;

selection_stat          : IF '(' exp ')' stat
                        | IF '(' exp ')' stat ELSE stat
;

iteration_stat          : WHILE '(' exp ')' stat
                        | DO stat WHILE '(' exp ')' ';'
                        | FOR '(' exp ';' exp ';' exp ')' stat
                        | FOR '(' exp ';' exp ';'     ')' stat
                        | FOR '(' exp ';'     ';' exp ')' stat
                        | FOR '(' exp ';'     ';'     ')' stat
                        | FOR '('     ';' exp ';' exp ')' stat
                        | FOR '('     ';' exp ';'     ')' stat
                        | FOR '('     ';'     ';' exp ')' stat
                        | FOR '('     ';'     ';'     ')' stat
;

jump_stat               : BREAK ';'
                        | CONTINUE ';'
                        | RETURN exp ';'
                        | RETURN     ';'
;

exp                     : assignment_exp
                        | exp ',' assignment_exp
;

assignment_exp          : conditional_exp
                        | unary_exp assignment_operator assignment_exp
;

assignment_operator     : '=' | MULEQ | DIVEQ | MODEQ | ADDEQ | SUBEQ | SLEQ
                        | SREQ | ANDEQ | CAREQ | PIPEQ
;

conditional_exp         : logical_or_exp
                        | logical_or_exp '?' exp ':' conditional_exp
;

const_exp               : conditional_exp
;

logical_or_exp          : logical_and_exp
                        | logical_or_exp OR logical_and_exp
;

logical_and_exp         : inclusive_or_exp
                        | logical_and_exp AND inclusive_or_exp
;

inclusive_or_exp        : exclusive_or_exp
                        | inclusive_or_exp '|' exclusive_or_exp
;

exclusive_or_exp        : and_exp
                        | exclusive_or_exp '^' and_exp
;

and_exp                 : equality_exp
                        | and_exp '&' equality_exp
;

equality_exp            : relational_exp
                        | equality_exp EQ relational_exp
                        | equality_exp NE relational_exp
;

relational_exp          : shift_expression
                        | relational_exp LT shift_expression
                        | relational_exp GT shift_expression
                        | relational_exp LE shift_expression
                        | relational_exp GE shift_expression
;

shift_expression        : additive_exp
                        | shift_expression SHIFTL additive_exp
                        | shift_expression SHIFTR additive_exp
;

additive_exp            : mult_exp
                        | additive_exp '+' mult_exp
                        | additive_exp '-' mult_exp
;

mult_exp                : cast_exp
                        | mult_exp '*' cast_exp
                        | mult_exp '/' cast_exp
                        | mult_exp '%' cast_exp
;

cast_exp                : unary_exp
                        | '(' type_name ')' cast_exp
;

unary_exp               : postfix_exp
                        | INCR unary_exp
                        | DECR unary_exp
                        | unary_operator cast_exp
;

unary_operator          : '&' | '*' | '+' | '-' | '~' | '!'
;


postfix_exp             : primary_exp
                        | postfix_exp '[' exp ']'
                        | postfix_exp '(' argument_exp_list ')'
                        | postfix_exp '('                   ')'
                        | postfix_exp '.' ID
                        | postfix_exp PTRDR ID
                        | postfix_exp INCR
                        | postfix_exp DECR
;

primary_exp             : ID
                        | const                        
                        | '(' exp ')'
;

argument_exp_list       : assignment_exp
                        | argument_exp_list ',' assignment_exp
;

const                   : DECIMAL
                        | STRING
;
                        

%%
























