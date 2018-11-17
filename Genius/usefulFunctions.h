#include <string>
#include <vector>
using namespace std;
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
	string rjust(int x, string s, string filler = " ");
	string ljust(int x, string s, string filler = " ");
};

