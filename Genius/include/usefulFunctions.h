#pragma once

#include <string>
#include <iostream>
#include <fstream>

class UsefulFunc
{
public:
	UsefulFunc();
	~UsefulFunc();

public:

	std::string rjust(int x, std::string s, std::string filler = " ");
	std::string ljust(int x, std::string s, std::string filler = " ");
	std::string recursiveOut(int x, std::string s);
	bool writeOut(std::string outputText, std::string outputTo, bool makeCheck = true);
};


std::string retVersion();

