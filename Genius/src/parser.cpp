#include "parser.h"

//using namespace std;
/*
void
Node::add(Node self, Token addToNode){
	Node *mynode = new Node;
	mynode.token = addToNode;
	mynode.level = 0;
	self.addNode(self, mynode);
}
void
Node::addNode(Node self, Node oldnode){
	oldnode.level = self.level + 1;
	self.children.insert(oldnode);
}
string Node::toString(Node self){
	string s;
	s = "    " + to_string(self.level);
	if(self.token.type == kToken_EMPTY){
		s += "ROOT\n";
	}
	else
	{
		s += self.token.cargo + "\n";
	}

}
*/


Parser::Parser(){

	mylexer = new Lexer;
	theToken.cargo = "GENIUSCOMPILERIMEMPTY";


}

Parser::~Parser(){

	delete mylexer;


}



Token Parser::fetchToken(){
	if(verbose){
		//if(theToken.cargo != "GENIUSCOMPILERIMEMPTY"){
		//	cout << " " + "   (" + mylexer->show(theToken);
		//}
	}
		return mylexer->lexerhandler();
}


std::string Parser::parse(std::string srcFile, bool verbosity){
	verbose = v;


	theToken = mylexer->lexerhandler(srcFile); 



}





