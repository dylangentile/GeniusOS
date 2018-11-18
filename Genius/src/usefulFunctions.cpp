#include <vector>
#include <string>
#include "usefulFunctions.h"
using namespace std;

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
