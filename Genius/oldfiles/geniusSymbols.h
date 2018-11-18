#pragma once
#include <vector>
#include <string>

using namespace std;

class geniusSymbols
{
public:
	geniusSymbols();
	~geniusSymbols();
	vector<string> Keywords;
	Keywords.push_back("if");
	Keywords.push_back("then");
	Keywords.push_back("else");
	//Keywords.push_back("elseif");
	Keywords.push_back("while");
	Keywords.push_back("loop");
	Keywords.push_back("endloop");
	Keywords.push_back("print");
	Keywords.push_back("return");
	Keywords.push_back("exit");
	

	vector<string> OneCharSymbols{'=','(',')','<','>','/','*','+','-','!','&','.',';'};

	vector<string> TwoCharSymbols{'==','<=','>=','<>','!=','++','**','--','+=','-=','||'};
	vector<string> StringStartChars{"'",'"'};
	vector<string> WhitespaceChars{' ', '\t','\n'};

	/*vector<string> TokenTypes;
	TokenTypes.push_back("String");
	TokenTypes.push_back("Identifier");
	TokenTypes.push_back("Number");
	TokenTypes.push_back("Whitespace");
	TokenTypes.push_back("Comment");
	TokenTypes.push_back("Eof");
*/
};