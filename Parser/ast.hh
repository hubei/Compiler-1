// ast.hh --- 
// 
// Filename: ast.hh
// Description: 
// Author: Ryan Goodfellow
// Copyright: Washington State University
// Created: Tue Mar  6 20:18:58 2012 (-0800)
// Version: 
// Last-Updated: Thu Mar  8 16:23:41 2012 (-0800)
//           By: Ryan Goodfellow
//     Update #: 96
// 

#ifndef _AST_HH_
#define _AST_HH_

#include <string>

namespace Ast
{
  
  // Forward declarations
  class Program;
  class ExtDecl;
  class FuncDef;
  class Declaration;
  class Typ;
  class Declarator;
  class DeclrList;
  class Parameters;
  class ParamDecl;
  class AbsDecl;
  class Block;
  class StatementList;
  class DeclList;
  class Statement;
  class BasicStatement;
  class IfStatement;
  class WhileStatement;
  class DoStatement;
  class ForStatement;
  class ReturnStatement;
  class ArgumentList;
  class ExprStmt;
  class Expression;
  class AsgnExpr;
  class AsgnOp;

  template <class T>
  class BinaryExp;
  namespace BinEx
  {
    class Or;
    class And;
    class Eq;
    class Rel;
    class Add;
    class Mul;
  }

  class UnaryExpr;
  class PostfixExpr;
  class PrimaryExpr;

  class ArrayDec;
  class FuncParam;



// /////////////////////////////////////////////////////////////////
// 
// AstVisitor:
// 
// Traverses an ast tree.  This is an abstract class and
// does not actually do anything the purpose is to set the 
// interface for derived classes to perform some type of 
// functionality when each node is visited
//
// /////////////////////////////////////////////////////////////////
  class AstVisitor
  {
    virtual void visit(Program *) = 0;
    virtual void visit(ExtDecl *) = 0;
  };

  
// /////////////////////////////////////////////////////////////////
// 
// AstNode:
//
// Base class for all AST nodes.  This class implements the visitor
// pattern through the accept function.  This class also uses the
// curiously recurring visitor pattern to achieve static
// polymorphism in conjunction with the visitor pattern
//
// /////////////////////////////////////////////////////////////////
  template <class Derived>
  class AstNode
  {
  public:
    void accept(AstVisitor &visitor);
  };


// /////////////////////////////////////////////////////////////////
// 
// Program:
//
// This AstNode class represents the program non temrinal in the 
// simple C gramatical structure
//
// /////////////////////////////////////////////////////////////////
  class Program : AstNode<Program>
  {
  public:
    Program(ExtDecl *child);

    void addExtDecl(ExtDecl *extDecl);
  };

// /////////////////////////////////////////////////////////////////
// 
// ExtDecl:
//
// This AstNode repressents the external declaration non terminal
// in the simple C gramatical structure
//
// /////////////////////////////////////////////////////////////////
  class ExtDecl : AstNode<ExtDecl>
  {
  public:
    ExtDecl(FuncDef *funcDef);
    ExtDecl(Declaration *declaration);
  };

// /////////////////////////////////////////////////////////////////
// 
// FuncDef:
//
// This AstNode represents the function definition non terminal
// in the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class FuncDef : AstNode<FuncDef>
  {
  public:
    FuncDef(Typ *typ, Declarator *declarator, Block *block);
  };
  

// /////////////////////////////////////////////////////////////////
// 
//  Declaration:
//
//  This AstNode represents the declaration non terminal in the 
//  simple C gramatical structure
//
// /////////////////////////////////////////////////////////////////
  class Declaration : AstNode<Declaration>
  {
  public:
    Declaration(Typ *typ);
    Declaration(Typ *type, DeclrList *declrList);
  };


// /////////////////////////////////////////////////////////////////
// 
//  Typ:
//
//  The AstNode represents the type non terminal in the simple C
//  gramatical structure
// 
// /////////////////////////////////////////////////////////////////
  class Typ : AstNode<Typ>
  {
  public:
    Typ(int typ);
    Typ(DeclList *declList);
    Typ(std::string id, DeclList *declList);
    Typ(std::string id);
  };

// /////////////////////////////////////////////////////////////////
// 
//  Declarator:
//
//  This AstNode represents the declarator non terminal in the 
//  simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class Declarator : AstNode<Declarator>
  {
  public:
    Declarator(std::string id);
    Declarator(Declarator* d, ArrayDec *a);
    Declarator(std::string id, FuncParam *f);

  };

// /////////////////////////////////////////////////////////////////
// 
//  DeclrList:
// 
//  This AstNode represents the declarator list non terminal in
//  the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class DeclrList : AstNode<DeclrList>
  {
  public:
    DeclrList(Declarator *d);
    DeclrList(Declarator *d, AsgnExpr *a);
    DeclrList(DeclrList *dl, Declarator *d);
  };

// /////////////////////////////////////////////////////////////////
// 
// Parameters:
// 
// This AstNode represents the parameters non terminal in the 
// simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class Parameters : AstNode<Parameters>
  {
  public:
    Parameters(ParamDecl *pd);
    Parameters(Parameters *p, ParamDecl *pd);
  };

// /////////////////////////////////////////////////////////////////
// 
// ParamDecl:
//
// This AstNode represents the parameter declaration non terminal
// in the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class ParamDecl : AstNode<ParamDecl>
  {
  public:
    ParamDecl(Typ *t, Declarator *d);
    ParamDecl(Typ *t, AbsDecl *a);
    ParamDecl(Typ *t);
  };

// /////////////////////////////////////////////////////////////////
// 
// AbsDecl:
//
// This AstNode represents the array declaration non terminal in 
// the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class AbsDecl : AstNode<AbsDecl>
  {
  public:
    AbsDecl();
  };

// /////////////////////////////////////////////////////////////////
// 
//  Block:
//
//  This AstNode represents the block non terminal in the simple C
//  grammar
// 
// /////////////////////////////////////////////////////////////////
  class Block : AstNode<Block>
  {
  public:
    Block();
    Block(StatementList *s);
  };

// /////////////////////////////////////////////////////////////////
// 
//  StatementList:
//
//  This AstNode represents the statement list non terminal in the
//  simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class StatementList : AstNode<StatementList>
  {
  public:
    StatementList(Statement *s);
    StatementList(StatementList *sl, Statement *s);
  };

// /////////////////////////////////////////////////////////////////
// 
//  DeclList:
//
//  This AstNode represents the declaration list non terminal in 
//  the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class DeclList : AstNode<DeclList>
  {
  public:
    DeclList(Declaration *d);
    DeclList(DeclList *dl, Declaration *d);
  };

// /////////////////////////////////////////////////////////////////
// 
//  Statement:
// 
//  Base class for all other statement classes.  Note that this is
//  not an AstNode instance on its own
//
// /////////////////////////////////////////////////////////////////
  class Statement
  {

  };

// /////////////////////////////////////////////////////////////////
// 
//  Statement:
//
//  This AstNode represents the statement non terminal in the
//  simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class BasicStatement : public Statement,  AstNode<BasicStatement>
  {
  public:
    BasicStatement(Block *b);
    BasicStatement(Declaration *d);
    BasicStatement(ExprStmt *e);
  };

// /////////////////////////////////////////////////////////////////
// 
//  IfStatement:
//
//  This AstNode represents the if productions of the statement
//  non terminal in the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class IfStatement : public Statement, AstNode<IfStatement>
  {
  public:
    IfStatement(Expression *e, Statement *s);
    IfStatement(Expression *e, Statement *ifs, Statement *es); 
  };

// /////////////////////////////////////////////////////////////////
// 
// WhileStatement:
//
//  This AstNode represents the while productions of the statement
//  non terminal in the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class WhileStatement : public Statement, AstNode<WhileStatement>
  {
  public:
    WhileStatement(Expression *e, Statement *s);
  };

// /////////////////////////////////////////////////////////////////
// 
//  DoStatement:
//
//  This AstNode represents the do productions of the statement non
//  terminal in the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class DoStatement : public Statement, AstNode<DoStatement>
  {
  public:
    DoStatement(Statement *s, Expression *e);
  };

// /////////////////////////////////////////////////////////////////
// 
//  ForStatement:
//
//  This AstNode represents the for productions of the statement 
//  non terminal in the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class ForStatement : public Statement, AstNode<ForStatement>
  {
  public:
    ForStatement(ExprStmt *e, ExprStmt *e1, Expression *e2, Statement *s);
  };


// /////////////////////////////////////////////////////////////////
// 
//  ReturnStatement:
//
//  This AstNode represents the return productions of the statement
//  non terminal in the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class ReturnStatement : public Statement, AstNode<ReturnStatement>
  {
  public:
    ReturnStatement(Expression *e);
  };

// /////////////////////////////////////////////////////////////////
// 
//  ArgumentList:
//
//  This AstNode represents the argument list non terminal in the 
//  simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class ArgumentList : AstNode<ArgumentList>
  {
  public:
    ArgumentList(AsgnExpr *a);
    ArgumentList(ArgumentList *al, AsgnExpr *a);
  };

// /////////////////////////////////////////////////////////////////
// 
//  ExprStmt:
//
//  This AstNode represents the expression statement non terminal
//  in the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class ExprStmt : AstNode<ExprStmt>
  {
  public:
    ExprStmt();
    ExprStmt(Expression *e);
  };

// /////////////////////////////////////////////////////////////////
// 
//  Expression:
//
//  This AstNode represents the expression non terminal in the 
//  simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class Expression : AstNode<Expression>
  {
  public:
    Expression(AsgnExpr *a);
    Expression(Expression *e, AsgnExpr *a);
  };

// /////////////////////////////////////////////////////////////////
// 
//  AsgnExpr:
//
//  This AstNode represents the assignment expression non terminal
//  in the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class AsgnExpr : AstNode<AsgnExpr>
  {
  public:
    AsgnExpr(BinaryExp<BinEx::Or> *e);
    AsgnExpr(UnaryExpr *u, AsgnOp *o, AsgnExpr *e);
  };

// /////////////////////////////////////////////////////////////////
// 
//  AsgnOp:
//
//  This AstNode represents the assignment operator non terminal
//  in the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class AsgnOp : AstNode<AsgnOp>
  {
  public:
    AsgnOp();
    AsgnOp(char designator);
  };

// /////////////////////////////////////////////////////////////////
// 
//  BinaryExp:
//
//  This AstNode represents binary expression non terminals in the
//  simple C grammar
// /////////////////////////////////////////////////////////////////
  template <class T>
  class BinaryExp : AstNode<BinaryExp<T> >
  {
  public:

  };

// /////////////////////////////////////////////////////////////////
// 
//  BinExFactory:
//
//  This class is responsible for creating binary expressions using
//  the factory pattern.  It returns a complete templated form
//  of the BinExp object.  Not that this is not an AstNode iteslf
//
// /////////////////////////////////////////////////////////////////
  class BinExFactory
  {
  public:
    // -OR-
    static BinaryExp<BinEx::Or> * CreateOr(BinaryExp<BinEx::And> *a);
    static BinaryExp<BinEx::Or> * CreateOr(BinaryExp<BinEx::Or> *o,
					   BinaryExp<BinEx::And> *a);

    // -AND-
    static BinaryExp<BinEx::And> * CreateAnd(BinaryExp<BinEx::Eq> *e);
    static BinaryExp<BinEx::And> * CreateAnd(BinaryExp<BinEx::And> *a,
					     BinaryExp<BinEx::Eq> *e);

    // -EQ-
    static BinaryExp<BinEx::Eq> * CreateEq(BinaryExp<BinEx::Rel> *r);
    static BinaryExp<BinEx::Eq> * CreateEq(BinaryExp<BinEx::Eq> *e,
					   BinaryExp<BinEx::Rel> *r, 
					   bool indicator);

    // -REL-
    static BinaryExp<BinEx::Rel> * CreateRel(BinaryExp<BinEx::Add> *a);
    static BinaryExp<BinEx::Rel> * CreateRel(BinaryExp<BinEx::Rel> *r,
					     BinaryExp<BinEx::Add> *a, 
					     std::string indicator);

    // -ADD-
    static BinaryExp<BinEx::Add> * CreateAdd(BinaryExp<BinEx::Mul> *m);
    static BinaryExp<BinEx::Add> * CreateAdd(BinaryExp<BinEx::Add> *a,
					     BinaryExp<BinEx::Mul> *m,
					     char indicator);

    // -MUL-
    static BinaryExp<BinEx::Mul> * CreateMul(UnaryExpr *u);
    static BinaryExp<BinEx::Mul> * CreateMul(BinaryExp<BinEx::Mul> *m,
					     UnaryExpr *u,
					     char indicator);

  };

// /////////////////////////////////////////////////////////////////
// 
//  UnaryExpr:
//
//  This AstNode represents the unary expression non terminal in
//  the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class UnaryExpr : AstNode<UnaryExpr>
  {
  public:
    UnaryExpr(PostfixExpr *p);
    UnaryExpr(UnaryExpr *u, std::string);
  };

// /////////////////////////////////////////////////////////////////
// 
//  PostfixExpr:
//
//  This AstNode represents the postfix expression non terminal in
//  the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class PostfixExpr : AstNode<PostfixExpr>
  {
  public:
    PostfixExpr(PrimaryExpr *p);
    PostfixExpr(PostfixExpr *pf , Expression *e);
    PostfixExpr(PostfixExpr *pf);
    PostfixExpr(PostfixExpr *pf, ArgumentList *al);
    PostfixExpr(PostfixExpr *pf, std::string);
  };

// /////////////////////////////////////////////////////////////////
// 
//  PrimaryExpr:
//
//  This AstNode represents the postfix expression non terminal in
//  the simple C grammar
//
// /////////////////////////////////////////////////////////////////
  class PrimaryExpr : AstNode<PrimaryExpr>
  {
  public:
    PrimaryExpr(std::string id);
    PrimaryExpr(int integer);
    PrimaryExpr(Expression *e);
  };

















// /////////////////////////////////////////////////////////////////
// 
//  ArrayDec:
//
//  This object keeps track of an array declaration
//
// /////////////////////////////////////////////////////////////////
  class ArrayDec
  {
  public:
    ArrayDec();
    ArrayDec(Expression *expr);
  };

// /////////////////////////////////////////////////////////////////
// 
// FuncParam:
//
//  This object keeps track of function parameters
// /////////////////////////////////////////////////////////////////
  class FuncParam
  {
  public:
    FuncParam();
    FuncParam(Parameters *p);
  };

}
#endif
