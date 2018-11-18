#include <string>
#include <vector>
/*
class Splitstring : public string {
    vector<string> flds;
public:
    Splitstring(char *s) : string(s) { };
    vector<string>& split(char delim, int rep=0);
};
*/
class UsefulFunc{
public:
	UsefulFunc();
	~UsefulFunc();
	std::string rjust(int x, std::string s, std::string filler = " ");
	std::string ljust(int x, std::string s, std::string filler = " ");
};

