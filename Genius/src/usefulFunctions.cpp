#include "usefulFunctions.h"
using namespace std;

string retVersion(){
    return "0.0.2";
}

UsefulFunc::UsefulFunc(){

}

UsefulFunc::~UsefulFunc(){

}



string 
UsefulFunc::rjust(int x, string s, string filler){
    for(int i = 0; i < x - s.size(); i++)
    {
            s = filler + s;
    }
    return s;
}
string 
UsefulFunc::ljust(int x, string s, string filler){
    for(int i = 0; i < x-s.size(); i++)
    {
        s = s + filler;
    }
    return s;
}
string 
UsefulFunc::recursiveOut(int x, string s){
    string retValue = s;
    for (int i = 1; i < x; i++){
        retValue += s;
    }
    return retValue;
}

bool 
UsefulFunc::writeOut(std::string outputText, std::string outputTo, bool makeCheck){
    ofstream outfile;
    outfile.open(outputTo);
    outfile << outputText;
    outfile.close();
    if(makeCheck == true){
        string check;
        ifstream fileCheck;
        fileCheck.open(outputTo);
        fileCheck >> check;
        fileCheck.close();

        if(check != outputText){
            return false;
        }
    }

    return true;
}

