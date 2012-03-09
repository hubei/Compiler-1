// ast.cc --- 
// 
// Filename: ast.cc
// Description: 
// Author: Ryan Goodfellow
// Copyright: Washington State University
// Created: Tue Mar  6 20:44:08 2012 (-0800)
// Version: 
// Last-Updated: Thu Mar  8 16:25:04 2012 (-0800)
//           By: Ryan Goodfellow
//     Update #: 68
// 


#include "ast.hh"


// /////////////////////////////////////////////////////////////////
// 
//  Ast::AstNode function definitions
//
// /////////////////////////////////////////////////////////////////

template <class Derived>
void Ast::AstNode<Derived>::accept(AstVisitor &visitor)
{
  visitor.visit(static_cast<Derived*>(this));
}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::Program function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::Program::Program(Ast::ExtDecl *child)
{

}

void Ast::Program::addExtDecl(Ast::ExtDecl *extDecl)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::ExtDecl function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::ExtDecl::ExtDecl(FuncDef *funcDef)
{

}

Ast::ExtDecl::ExtDecl(Declaration *decl)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::FuncDef function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::FuncDef::FuncDef(Ast::Typ *typ, Ast::Declarator *declarator, Ast::Block *block)
{

}


// /////////////////////////////////////////////////////////////////
// 
//  Ast::Declaration function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::Declaration::Declaration(Ast::Typ *typ)
{

}

Ast::Declaration::Declaration(Ast::Typ *typ, Ast::DeclrList * declrList)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::Typ function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::Typ::Typ(int typ)
{

}

Ast::Typ::Typ(Ast::DeclList *declList)
{

}

Ast::Typ::Typ(std::string id, Ast::DeclList *declList)
{

}

Ast::Typ::Typ(std::string id)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::Declarator function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::Declarator::Declarator(std::string id)
{

}

Ast::Declarator::Declarator(Ast::Declarator *d, Ast::ArrayDec *a)
{

}

Ast::Declarator::Declarator(std::string id, Ast::FuncParam *f)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::DeclrList funciton definitions
//
// /////////////////////////////////////////////////////////////////

Ast::DeclrList::DeclrList(Ast::Declarator *d)
{

}

Ast::DeclrList::DeclrList(Ast::Declarator *d, Ast::AsgnExpr *a)
{

}

Ast::DeclrList::DeclrList(Ast::DeclrList *dl, Ast::Declarator *d)
{

}

// /////////////////////////////////////////////////////////////////
// 
// Ast::Parameters function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::Parameters::Parameters(Ast::ParamDecl *pd)
{

}

Ast::Parameters::Parameters(Ast::Parameters *p, Ast::ParamDecl *pd)
{

}

// /////////////////////////////////////////////////////////////////
// 
// Ast::ParamDecl function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::ParamDecl::ParamDecl(Ast::Typ *t, Ast::Declarator *d)
{

}

Ast::ParamDecl::ParamDecl(Ast::Typ *t, Ast::AbsDecl *a)
{

}

Ast::ParamDecl::ParamDecl(Ast::Typ *t)
{

}

// /////////////////////////////////////////////////////////////////
// 
// Ast::AbsDecl function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::AbsDecl::AbsDecl()
{

}


// /////////////////////////////////////////////////////////////////
// 
// Ast::Block function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::Block::Block()
{

}

Ast::Block::Block(Ast::StatementList *s)
{

}

// /////////////////////////////////////////////////////////////////
// 
// Ast::StatementList function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::StatementList::StatementList(Ast::Statement *s)
{

}

Ast::StatementList::StatementList(Ast::StatementList *sl, Ast::Statement *s)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::DeclList function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::DeclList::DeclList(Ast::Declaration *d)
{

}

Ast::DeclList::DeclList(Ast::DeclList *dl, Ast::Declaration *d)
{

}

// /////////////////////////////////////////////////////////////////
// 
// Ast::BasicStatement function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::BasicStatement::BasicStatement(Ast::Block *b)
{

}

Ast::BasicStatement::BasicStatement(Ast::Declaration *b)
{

}

Ast::BasicStatement::BasicStatement(Ast::ExprStmt *e)
{

}

// /////////////////////////////////////////////////////////////////
// 
// Ast::IfStatement function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::IfStatement::IfStatement(Ast::Expression *e, Ast::Statement *s)
{

}

Ast::IfStatement::IfStatement(Ast::Expression *e, Ast::Statement *ifs, 
			      Ast::Statement *es)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::WhileStatement function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::WhileStatement::WhileStatement(Ast::Expression *e, Ast::Statement *s)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::DoStatement function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::DoStatement::DoStatement(Ast::Statement *s, Ast::Expression *e)
{

}

// /////////////////////////////////////////////////////////////////
//
//  Ast::ForStatement function definitions
// 
// /////////////////////////////////////////////////////////////////

Ast::ForStatement::ForStatement(Ast::ExprStmt *e, Ast::ExprStmt *e1,
				Ast::Expression *e2, Ast::Statement *s)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::ReturnStatement function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::ReturnStatement::ReturnStatement(Ast::Expression *e)
{

}

// /////////////////////////////////////////////////////////////////
//
//  Ast::ArgumentList function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::ArgumentList::ArgumentList(Ast::AsgnExpr *a)
{

}

Ast::ArgumentList::ArgumentList(Ast::ArgumentList *al, Ast::AsgnExpr *a)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::ExprStmt function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::ExprStmt::ExprStmt()
{

}

Ast::ExprStmt::ExprStmt(Ast::Expression *e)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::Expression function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::Expression::Expression(Ast::AsgnExpr *a)
{

}

Ast::Expression::Expression(Ast::Expression *e, Ast::AsgnExpr *a)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::AsgnExpr function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::AsgnExpr::AsgnExpr(Ast::BinaryExp<Ast::BinEx::Or> *e)
{

}

Ast::AsgnExpr::AsgnExpr(Ast::UnaryExpr *u, Ast::AsgnOp *o, Ast::AsgnExpr *e)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::AsgnOp function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::AsgnOp::AsgnOp()
{

}

Ast::AsgnOp::AsgnOp(char designator)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::BinaryExp function definitions
//
// /////////////////////////////////////////////////////////////////


// /////////////////////////////////////////////////////////////////
//  Ast:BinExFacotry function Definitions
// /////////////////////////////////////////////////////////////////

// -OR-
Ast::BinaryExp<Ast::BinEx::Or> * 
Ast::BinExFactory::CreateOr(Ast::BinaryExp<Ast::BinEx::And> *a)
{

}

Ast::BinaryExp<Ast::BinEx::Or> * 
Ast::BinExFactory::CreateOr(Ast::BinaryExp<Ast::BinEx::Or> *o,
			    Ast::BinaryExp<Ast::BinEx::And> *a)
{

}

// -AND-
Ast::BinaryExp<Ast::BinEx::And> * 
Ast::BinExFactory::CreateAnd(BinaryExp<Ast::BinEx::Eq> *e)
{

}

Ast::BinaryExp<Ast::BinEx::And> * 
Ast::BinExFactory::CreateAnd(BinaryExp<Ast::BinEx::And> *a,
			     BinaryExp<Ast::BinEx::Eq> *e)
{

}

// -EQ-
Ast::BinaryExp<Ast::BinEx::Eq> * 
Ast::BinExFactory::CreateEq(BinaryExp<Ast::BinEx::Rel> *r)
{

}

Ast::BinaryExp<Ast::BinEx::Eq> * 
Ast::BinExFactory::CreateEq(BinaryExp<Ast::BinEx::Eq> *e,
			    BinaryExp<Ast::BinEx::Rel> *r, 
			    bool indicator)
{

}

// -REL-
Ast::BinaryExp<Ast::BinEx::Rel> * 
Ast::BinExFactory::CreateRel(BinaryExp<BinEx::Add> *a)
{

}
 
Ast::BinaryExp<Ast::BinEx::Rel> * 
Ast::BinExFactory::CreateRel(BinaryExp<BinEx::Rel> *r,
			     BinaryExp<BinEx::Add> *a, 
			     std::string indicator)
{

}

// -ADD-
Ast::BinaryExp<Ast::BinEx::Add> * 
Ast::BinExFactory::CreateAdd(BinaryExp<BinEx::Mul> *m)
{

}
 
Ast::BinaryExp<Ast::BinEx::Add> * 
Ast::BinExFactory::CreateAdd(BinaryExp<BinEx::Add> *a,
			     BinaryExp<BinEx::Mul> *m,
			     char indicator)
{

}

// -MUL-
Ast::BinaryExp<Ast::BinEx::Mul> * 
Ast::BinExFactory::CreateMul(UnaryExpr *u)
{

}
 
Ast::BinaryExp<Ast::BinEx::Mul> * 
Ast::BinExFactory::CreateMul(BinaryExp<BinEx::Mul> *m,
			     UnaryExpr *u,
			     char indicator)
{

}

// /////////////////////////////////////////////////////////////////
// 
// Ast::UnaryExpr function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::UnaryExpr::UnaryExpr(Ast::PostfixExpr *p)
{

}

Ast::UnaryExpr::UnaryExpr(Ast::UnaryExpr *u, std::string)
{

}

// /////////////////////////////////////////////////////////////////
// 
//  Ast::PostfixExpr function definitions
//
// /////////////////////////////////////////////////////////////////


Ast::PostfixExpr::PostfixExpr(Ast::PrimaryExpr *p)
{

}

Ast::PostfixExpr::PostfixExpr(Ast::PostfixExpr *pf , Ast::Expression *e)
{

}

Ast::PostfixExpr::PostfixExpr(Ast::PostfixExpr *pf)
{

}

Ast::PostfixExpr::PostfixExpr(Ast::PostfixExpr *pf, Ast::ArgumentList *al)
{

}

Ast::PostfixExpr::PostfixExpr(Ast::PostfixExpr *pf, std::string)
{

}

// /////////////////////////////////////////////////////////////////
// 
// Ast::PrimaryExpr function definitions
//
// /////////////////////////////////////////////////////////////////
Ast::PrimaryExpr::PrimaryExpr(std::string id)
{

}
Ast::PrimaryExpr::PrimaryExpr(int integer)
{

}

Ast::PrimaryExpr::PrimaryExpr(Ast::Expression *e)
{

}























// /////////////////////////////////////////////////////////////////
// 
// Ast::ArrayDec function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::ArrayDec::ArrayDec()
{

}

Ast::ArrayDec::ArrayDec(Ast::Expression *expr)
{

}

// /////////////////////////////////////////////////////////////////
// 
// Ast::FuncParam function definitions
//
// /////////////////////////////////////////////////////////////////

Ast::FuncParam::FuncParam()
{

}

Ast::FuncParam::FuncParam(Ast::Parameters *p)
{

}
