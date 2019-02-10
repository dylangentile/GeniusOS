#pragma once
#include "lexer.h"
#include <vector>
#include <string>

typedef enum{
	kState_UNKNOWN,
	kState_FUNC,
	kState_VAR



}Statetype;



class Statement
{
public:
	Statement();
	virtual ~Statement();
	virtual void print(int down){}
	Statetype sType;
};

class VarStatement : public Statement
{
public:
	VarStatement();
	~VarStatement();
	std::string mName;
	Token mValue, mType;
	void print(int down);

	
};

class FuncStatement : public Statement
{
public:
	FuncStatement();
	~FuncStatement();
	std::string mName;
	Token mType;
	std::vector<Statement*> mStatementVector;
	

	void print(int down);
	
};