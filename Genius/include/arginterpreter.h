#pragma once

class ArgReader
{
public:
	ArgReader();
	~ArgReader();
	void readArgs(int argNum, char const *args[]);
public:
	bool verbosity;
	bool quickly;


};