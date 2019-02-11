#pragma once
#include "statement.h"
#include <map>
#include <stack>
typedef enum{
	kType_UNKNOWN,
	kType_64INT,
	kType_64DOUBLE,
	kType_STRING,
	kType_BOOL,
	kType_OBJECT
}StackFType;


typedef struct {
	StackFType mType;
	long long ival;
	double dval;
	std::string sval;
	bool bval;
	void *oval;	
}Variant;


class StackFrame
{
public:
	StackFrame();
	~StackFrame();
	std::map<std::string, Variant> mMap;
	
};


class Interpreter
{
public:
	Interpreter();
	~Interpreter();
	std::string interpret(FuncStatement *gFunc);
	std::stack<StackFrame*> theStack;
private:
	std::string retMsg;
	
};