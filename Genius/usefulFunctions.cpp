#include <vector>
#include <string>
#include "usefulFunctions.h"
using namespace std;

/*
vector<string>& Splitstring::split(char delim, int rep) //https://stackoverflow.com/questions/14414451/python-c-is-the-any-python-split-like-method-in-c
{ 
    if (!flds.empty()) flds.clear();
    string work = data();
    string buf = "";
    int i = 0;
    while (i < work.length()) {
        if (work[i] != delim)
            buf += work[i];
        else if (rep == 1) {
            flds.push_back(buf);
            buf = "";
        } else if (buf.length() > 0) {
            flds.push_back(buf);
            buf = "";
        }
        i++;
    }
    if (!buf.empty())
        flds.push_back(buf);
    return flds;
}
*/
UsefulFunc::UsefulFunc(){

}

UsefulFunc::~UsefulFunc(){

}



string UsefulFunc::rjust(int x, string s, string filler){
    for(int i = 0; i < x - s.size(); i++)
    {
            s = filler + s;
    }
    return s;
}
string UsefulFunc::ljust(int x, string s, string filler){
    for(int i = 0; i < x-s.size(); i++)
    {
        s = s + filler;
    }
    return s;
}