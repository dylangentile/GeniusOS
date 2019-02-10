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
	virtual void print(int down) = 0;
	virtual bool compare(std::string nameID) = 0;
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
	bool compare(std::string nameID);


	
};

class FuncStatement : public Statement
{
public:
	FuncStatement();
	~FuncStatement();
	std::string mName;
	Token mType;
	std::vector<Statement*> mStatementVector;
	
	bool compare(std::string nameID);
	void print(int down);
	
};