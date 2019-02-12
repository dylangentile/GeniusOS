#include "statement.h"

#include <iostream>
using namespace std;

Statement::Statement(){
	sType = kState_UNKNOWN;
}

Statement::~Statement(){

}

VarStatement::VarStatement(){
	sType = kState_VAR;
}

VarStatement::~VarStatement(){

}




void
VarStatement::print(int down){
	cout << mType.cargo << ": "<< mName << "=" << mValue.cargo << "\n";
}



bool
VarStatement::compare(string nameID){
	if(mName == nameID){
		return true;
	}
	return false;
}







FuncStatement::FuncStatement()
{
	mName = "default_name";
	sType = kState_FUNC;
}

FuncStatement::~FuncStatement()
{
}

bool
FuncStatement::compare(string nameID){
	if(mName == nameID){
		return true;
	}
	bool theret = false;
	vector<Statement*>::iterator it;
	for(it = mStatementVector.begin(); it != mStatementVector.end(); it++){
		Statement *mystatement = *it;
		if(mystatement->compare(nameID)){
			theret = true;
			break;
		}
	}
	return theret;


}


void
FuncStatement::print(int down){

	vector<Statement*>::iterator it;
	cout << "Function: " << mType.cargo << " " << mName << "\n";
	for(it = mStatementVector.begin(); it != mStatementVector.end(); it++){
		Statement *mystatement = *it;
		for(int i = 0; i < down; i++){
		cout << "\t";
		}
		mystatement->print(down + 1);
	}


}



EquationStatement::EquationStatement(){

}
EquationStatement::~EquationStatement(){



}
void
EquationStatement::print(int down){
	vector<string>::iterator it;
	for(it = opTokens.begin(); it != opTokens.end(); it++){
		string myToken = *it;
		for(int i = 0; i < down; i++){
		cout << "\t";
		}
		cout << myToken;

	}
}