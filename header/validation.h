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


bool User::validate(int mode){                          //Returns True if invalid
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
            cout << "\nPLEASE ENTER NUMBERS ONLY!" << endl;
            system("pause");
            return true;
        }
        break;
    case 2:
        //Validate if the input is a valid name
        if(!(regex_match(input, nameEx))){
            cout << "INVALID NAME" << endl;
            system("pause");
            return true;
        }
        break;
    case 3:
        //Validate contact number
        validate(1);
        if(input.length() != 9){
            cout << " INVALID CONTACT NUMBER! Ex. +639123456789" << endl;
            system("pause");
            return true;
        }
        break;
    case 4:
        //Validate date
        if (!isValidDate(day, month, year)){
            cout << "INVALID DATE"<<endl;
            system("pause");
            return true;


        }
        // if(!(strptime(buffer.c_str(), "%m/%d/%Y", &timeStruct))){
        //     cout << " Please enter in a valid date! month/day/year." << endl;
        //     system("pause");
        //     return true;
        // }
        if((now->tm_year + 1900) - year < 12){
            cout << "Anyone who's 13 below cannot use the atm!"<< endl; 
            system("pause");
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
            cout << "PINCODE DOES NOT MATCH!" << endl; 
            system("pause");
            return true;
        }
        break;
    case 6:
        //validate initial Deposit
        validate(1);
        if(stoi(input) < 5000){
            cout << "Initial deposit must be a minimum of 5,000php!" << endl;
            system("pause");
            return true;
           
        }
        if (stoi(input) > 100000){
            cout<<"Maximum deposit amount must only be 100,000php"<<endl;
            system("pause");
            return true;
         
        }
        if(stof(input) == 0){
            cout << "Please enter a valid amount!" << endl;
            system("pause");
            return true;
           
        }
        break;
     case 7:
        fp.open("key.ink", ios::in);
        if(fp){ fp >> buffer;}
        fp.close();
        if(sha256(mainKey) != buffer){
            return true;
        }
        break;
    default:
        return true;
        break;
    }
    return false;
}


bool User::validatePin(){                   //Returns true if invalid
    fstream fp;
    fp.open(KEY_CODE_PATH, ios::in);
    if(fp){
        fp >> buffer;
    }else{
        cout << "key is missing!" << endl;
        system("pause");
        return true;                        
    }   
    fp.close();

    fp.open(CARD_PATH_ENCRYPTION, ios::in);
    if(!fp){
        cout << "Account file is missing!" << endl;
        system("pause");
        return true;                        
    }
    fp.close();
    
    if(sha256(input) != buffer){
        return true;
    }
    return false;
}

bool User::isCardInserted(){
    fstream fp, fs;
    fp.open("g:/Card.txt.cpt", ios::in);
    if(fp){
        return true;
    }
    return false;
}

      
bool User::isLeap(int year){
    // Return true if year
    // is a multiple of 4 and
    // not multiple of 100.
    // OR year is multiple of 400.
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));}
        
 // Returns true if given
// year is valid or not.
bool User::isValidDate(int d, int m, int y){
    // If year, month and day
    // are not in given range
    if(m > 12 || m < 1)
        return false;

    if (y > MAX_VALID_YR || y < MIN_VALID_YR){
        return false;
        if (m < 1 || m > 12)
        return false;
        if (d < 1 || d > 31)
        return false;
    }
    // Handle February month
    // with leap year
    if (m == 2){
        if (isLeap(y))
        return (d <= 29);
    }else{
         return (d <= 28);
    }
        // Months of April, June,
        // Sept and Nov must have
        // number of days less than
        // or equal to 30.
        if (m == 4 || m == 6 || m == 9 || m == 11){
           return (d <= 30);
        
            return true;
        }
    
}