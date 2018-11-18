#pragma once
#include "scanner.h"
#include "usefulFunctions.h"
//#include "tokenizer"
//#include "character.h"
#include <string>
#include <map>


typedef enum 
{
	kToken_UNKNOWN, 
	kToken_IF, 
	kToken_THEN, 
	kToken_ELSE, 
	kToken_ELSEIF, 
	kToken_WHILE, 
	kToken_LOOP, 
	kToken_ENDLOOP, 
	kToken_PRINT, 
	kToken_RETURN, 
	kToken_EXIT, 
	kToken_EQUALS, 
	kToken_LPAREN, 
	kToken_RPAREN, 
	kToken_LESSTHAN, 
	kToken_GREATERTHAN, 
	kToken_DIVIDE, 
	kToken_MULTIPLY, 
	kToken_PLUS, 
	kToken_MINUS, 
	kToken_BANG, 
	kToken_AND, 
	kToken_DOT, 
	kToken_SEMICOLON, 
	kToken_EQUALITY, 
	kToken_LESSEQUAL, 
	kToken_GREATEREQUAL, 
	kToken_NOTEQUAL, 
	kToken_INCREMENT, 
	kToken_EXP, //EXPONENT
	kToken_DECREMENT, 
	kToken_PLUSEQUALS, 
	kToken_MINUSEQUALS, 
	kToken_OR, 
	kToken_QUOTE, 
	kToken_SPACE, 
	kToken_TAB, 
	kToken_NEWLINE, 
	kToken_STRING,
	kToken_BOOL, 
	kToken_IDENTIFIER, 
	kToken_WHITESPACE, 
	kToken_NUMBER, 
	kToken_COMMENT,
	kToken_EOF
	
} TokenID;

typedef struct{
	std::string cargo, sourceText;
	int lineIndex, colIndex; 
	TokenID type;
} Token;


class Lexer
{
public:
	Lexer();
	~Lexer();

	
	Token lexerhandler(std::string doInit = "NULL");
	std::string tokenWrapper(Token self, bool showLineNumbers, bool align);

private:
	void lexerInit(std::string srcTxtArg);
	TokenID isKeyword(std::string i_keyword);
	bool isWhitespaceChar(std::string i_char);
	bool isIdentifierStartChar(std::string i_char);
	bool isIdentifierChar(std::string i_char);
	void getCharPackage();
	bool isNumberStart(std::string num, std::string &finishedcargo, int &loops);
	bool is_number(const std::string& s);
	TokenID isTwoCharOperator(std::string op);
	TokenID isOneCharSymbol(std::string sy);
	void abort(Token x, std::string msg);
	TokenID isTypeStartChars(std::string x);
	Token lexerMain();
	TokenID typeLookAhead(TokenID y, int &o_look);
private:
	std::string c1, c2;
	UsefulFunc *myljust;

	std::string tempSourceText;
	int tempLineIndex, tempcolIndex;
std::string srcTxtSv;
	int lnDex = 0, clDex = 0;
	Scanner *myscanner;

	std::map<std::string, TokenID>  mKeywordMap;
	std::map<std::string, TokenID> mOperatorMap;
		std::map<std::string, TokenID> mTypeMap;



};