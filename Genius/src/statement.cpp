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











FuncStatement::FuncStatement()
{
	mName = "default_name";
	sType = kState_FUNC;
}

FuncStatement::~FuncStatement(){

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