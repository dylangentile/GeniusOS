#pragma once
#include "lexer.h"
#include <vector>
#include <string>
class Statement
{
public:
	Statement();
	virtual ~Statement();
	virtual void print(){}
};

class VarStatement : public Statement
{
public:
	VarStatement();
	~VarStatement();
	std::string mName;
	Token mValue, mType;
	void print();

	
};

class FuncStatement : public Statement
{
public:
	FuncStatement();
	~FuncStatement();
	std::string mName;
	std::vector<Statement*> mStatementVector;
	void printem();
private:
	
};