#include "statement.h"

#include <iostream>
using namespace std;

Statement::Statement(){

}

Statement::~Statement(){

}

VarStatement::VarStatement(){


}

VarStatement::~VarStatement(){

}




void
VarStatement::print(){
	cout << "\n" << mType.cargo << ": "<< mName << "=" << mValue.cargo;


}











FuncStatement::FuncStatement(){

}

FuncStatement::~FuncStatement(){

}




void
FuncStatement::printem(){

	vector<Statement*>::iterator it;
	for(it = mStatementVector.begin(); it != mStatementVector.end(); it++){
		Statement *mystatement = *it;
		mystatement->print();
	}


}