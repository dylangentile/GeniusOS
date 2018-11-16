#pragma once
#include <string>
typedef struct{
	std::string cargo, sourceText;
	int lineIndex, colIndex; 
	std::string type;
} Token;



typedef enum TokenID
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
	kToken_MULITPLY, 
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
	kToken_IDENTIFIER, 
	kToken_WHITESPACE, 
	kToken_NUMBER, 
	kToken_COMMENT,
	kToken_EOF
	
};

class Tokenizer{

public:
	std::string show(Token self, bool showLineNumbers, bool align);

	Tokenizer();
	~Tokenizer();

private:








}
