#include "filehandling.h"

string str;

bool validateNumberInput(){
    if(!(regex_match(str, numberEx))){
        cout << "Please enter a number!" << endl;
        return false;
    }
}



