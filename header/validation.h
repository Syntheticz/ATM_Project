#include "filehandling.h"


extern "C" char* strptime(const char* str, const char* format, struct tm* time) {
  istringstream input(str);
  input.imbue(locale(setlocale(LC_ALL, nullptr)));
  input >> get_time(time, format);
  if (input.fail()) {
    return nullptr;
  }
  return (char*)(str + input.tellg());
}


bool User::validate(int mode){
    //Date Variables
    struct tm timeStruct;
    time_t t = time(0);
    tm* now = localtime(&t);
    fstream fp;

    switch (mode)
    {
    case 1:
        //Validate if the input is a number
        if(!(regex_match(input, numberEx))){
            cout << "Please enter a number!" << endl;
            system("pause");
            return true;
        }
        break;
    case 2:
        //Validate if the input is a valid name
        if(!(regex_match(input, nameEx))){
            cout << "the name you entered is not a valid one." << endl;
            system("pause");
            return true;
        }
        break;
    case 3:
        //Validate contact number
        validate(1);
        if(input.length() != 10){
            cout << " Please enter in a valid number! Ex. +639123456789" << endl;
            return true;
        }
        break;
    case 4:
        //Validate date
        if(!(strptime(buffer.c_str(), "%m/%d/%Y", &timeStruct))){
            cout << " Please enter in a valid date! month/day/year." << endl;
            return true;
        }
        if((now->tm_year + 1900) - stoi(buffer) < 12){
            cout << "Anyone who's 13 below cannot use the atm!"<< endl; 
            return true;
        }
        break;
    case 5:
        //Validate Pincode
        validate(1);
        if(input.length() > 6 || input.length() < 4){
            cout << "Pincode must only be a 4 or 6 digit number!" << endl; 
            system("pause");
            return true;
            }
        if(buffer.length() > 1 && buffer != input){
            cout << "The pincode that you've entered does not match" << endl; 
            system("pause");
            return true;
        }
        break;
    case 6:
        //validate initial Deposit
        validate(1);
        if(stoi(input) < 5000){
            cout << "initial deposit must be a minimum of 5000!" << endl;
            system("pause");
            return true;
        }
        break;
     case 7:
        fp.open("key.ink", ios::in);
        if(fp){ fp >> buffer;}
        fp.close();
        if(sha256(key) != buffer){
            return true;
        }
        break;
    default:
        return true;
        break;
    }
    return false;
}




