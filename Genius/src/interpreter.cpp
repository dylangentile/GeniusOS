#include "interpreter.h"
#include "lexer.h"
#include <sstream>
using namespace std;

StackFrame::StackFrame(){

}
StackFrame::~StackFrame(){

}


Interpreter::Interpreter(){
	retMsg = "";
}

Interpreter::~Interpreter(){

}

string
Interpreter::interpret(FuncStatement *gFunc){




	cout << "--------------Enter Stack Frame\n\n";

	StackFrame *gSF = new StackFrame;
	theStack.push(gSF);

	vector<Statement*> &statementVector = gFunc->mStatementVector;
	vector<Statement*>::iterator it;

	for(it = statementVector.begin(); it != statementVector.end(); it++)
	{
		Statement *thestatement = *it;
		if(thestatement->sType == kState_VAR)
		{

			VarStatement *varStatment = dynamic_cast<VarStatement*>(thestatement);

			Variant tVar;
			if(varStatment->mType.type == kToken_NUMBER)
			{
				tVar.mType = kType_64INT;
				if(varStatment->mValue.cat == kCat_VALUEUNSET)
				{
					tVar.ival = 0;
				} 
				else 
				{
					stringstream ss;
					ss << varStatment->mValue.cargo;
					ss >> tVar.ival;
				}
			}
			if(varStatment->mType.type == kToken_BOOL)
			{
				tVar.mType = kType_BOOL;
				if(varStatment->mValue.cat == kCat_VALUEUNSET){
					tVar.bval = false;
				}
				else
				{
					if(varStatment->mValue.cargo == "true")
					{
						tVar.bval = true;
					}
					else 
					{
						tVar.bval = false;
					}
				}
			}
			if(varStatment->mType.type == kToken_STRING)
			{
				tVar.mType = kType_STRING;
				if(varStatment->mValue.cat == kCat_VALUEUNSET)
				{
					tVar.sval = "";
				} else {
					tVar.sval = varStatment->mValue.cargo;
				}
			}



			gSF->mMap.insert(make_pair(varStatment->mName, tVar));
		}
		else if(thestatement->sType == kState_FUNC){
			FuncStatement *funcStatment = dynamic_cast<FuncStatement*>(thestatement);
			retMsg = interpret(funcStatment);
		}
	}


	map<std::string, Variant>::iterator itVar;

	for(itVar = gSF->mMap.begin(); itVar != gSF->mMap.end(); itVar++)
	{
		cout << "\n" << itVar->first << ": ";
	
		if(itVar->second.mType == kType_64INT){
			cout << to_string(itVar->second.ival);
		}
		if(itVar->second.mType == kType_64DOUBLE){
			cout << to_string(itVar->second.dval);
		}
		if(itVar->second.mType == kType_STRING){
			cout << itVar->second.sval;
		}
		if(itVar->second.mType == kType_BOOL){
			if(itVar->second.bval){
				cout << "true";
			}else{
				cout << "false";
			}
		}
	}
	theStack.pop();


	cout << "\n-------------Exit Stack Frame\n\n";

	return retMsg;	
}