#include <iostream>
#include <random>
#include <regex>
#include <fstream> 
#include <ctime>
#include <time.h>
#include <iomanip>
#include <sstream>


using namespace std;

extern "C" char* strptime(const char* str, const char* format, struct tm* time) {
  std::istringstream input(str);
  input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
  input >> std::get_time(time, format);
  if (input.fail()) {
    return nullptr;
  }
  return (char*)(str + input.tellg());
}




/// expression

regex numberEx("[-+]?([0-9]*\.[0-9]+|[0-9]+)");
regex nameEx("^[a-zA-Z\\s]*$");

// Data structure for Recipts
typedef struct recipt{
    string Date;
    float cashIn, cashOut;

    void setTime();
}RECIPT;

typedef struct list{
    RECIPT rec;
    string transactionID;
    struct list *next;

}LIST;


//Generate a unique transactio ID
string get_uuid() {

    static mt19937 rng(time(0));

    uniform_int_distribution<int> dist(0, 9);

    const char *v = "0123456789";
    string res;
    for (int i = 0; i < 5; i++) {
        res += v[dist(rng)];
    }
    return res;
}


// Data structure for Users

typedef struct info{
    string name, birthDay, contact;
    int accountNumber, pincode;
    float deposit;

}INFO;



typedef struct userRecords{
    LIST *recipt;
    INFO inf;
    struct userRecords *next;

}UREC;

class User {
    private:
    UREC *head;

    public:
    void setHead();
    void menu();
    void openAcc();
    void registerAcc();
    void add(INFO inf);
    bool validate(int mode, string value);
};

void User::setHead(){
    head = NULL;
}
void User::add(INFO inf){
    UREC *pointer, *follower, *temp;
    pointer = follower = head;

    temp = new UREC;
    temp->inf = inf; 

    while (pointer != NULL)
    {
        follower = pointer;
        pointer = pointer->next;
    }

    if(head == pointer){
        head = temp;
    }else{
        follower->next = temp;
        temp->next = pointer;
    }

}

void RECIPT::setTime(){
    time_t now = time(0);
    Date = ctime(&now);
}

// TODO optimze Validation
bool User::validate(int mode, string value){
    struct tm tm;
    
    switch (mode)
    {
    case 1:
        if(!(regex_match(value, nameEx))){
            cout << "the name you entered is not a valid one." << endl;
            return true;
        }
    break;
    case 2:
        if(!(regex_match(value, numberEx))){
            cout << "Please enter a number!" << endl;
            return true;
        }
        if(value.length() != 10){
            cout << " Please enter in a valid number! Ex. +639123456789" << endl;
            return true;
        }
    break;
    case 3:
        if(!(strptime(value.c_str(), "%m/%d/%Y", &tm))){
            cout << " Please enter in a valid date! month/day/year." << endl;
            return true;
        }
    break;
     case 4:
        if(!(regex_match(value, numberEx))){
            cout << "Please enter a number!" << endl;
            return true;
        }
    break;
    default:
        return false;
        break;
    }
    return false;
}



void User::registerAcc(){
    INFO usr;


    string buffer,bd, pincode,deposit,choice, uuid;
    time_t t = time(0);
    tm* now = localtime(&t);


    cout << "Please enter your name: ";
    getline(cin, usr.name);
    if(validate(1, usr.name)){cout << "HI";return;}
    

    cout << "Please enter in yout phone number: +63";
    getline(cin, buffer);
    if(validate(2, buffer)){return;}
    usr.contact.append("+63");
    usr.contact.append(buffer);


    cout << "please enter in your birthday\nMonth [1-12]:  ";    
    getline(cin, buffer);
    if(validate(4, buffer)){return;}
    bd.append(buffer + "/");
    
    cout << "Day [01-30]: ";
    getline(cin, buffer);
    if(validate(4, buffer)){return;}
    bd.append(buffer + "/");

    cout << "Year Ex. 2001: ";
    getline(cin, buffer);
    if(validate(4, buffer)){return;}
    bd.append(buffer);
    if(validate(3, bd)){return;}
    if((now->tm_year + 1900) - stoi(buffer) < 12){cout << "Anyone who's 13 below cannot use the atm!"<< endl; return;}
    usr.birthDay = bd;
    
    cout << "Please enter in your pincode: ";
    getline(cin, pincode);
    if(validate(4, pincode)){return;}
    if(!(pincode.length() == 6 || pincode.length() == 4)){cout << "Pincode must only be a 4 or 6 digit number!" << endl; return;}
    cout << "Please re-enter your pincode: ";
    getline(cin, buffer);
    if(buffer != pincode){cout << "The pincode that you've entered does not match" << endl; return;}
    usr.pincode = stoi(pincode);

    cout << "Please enter initial deposit: ";
    getline(cin, buffer);
    if(validate(4, buffer)){return;}
    if(stoi(buffer) < 5000){cout << "initial deposit must be a minimum of 5000!" << endl; return;}
    usr.deposit = stoi(buffer);

    // confirmation notice
    cout << "\e[1;1H\e[2J" << endl;
    cout << "\nPlease confirm your information!" << endl;
    cout << "Name: " << usr.name << endl;
    cout << "Number: " << usr.contact << endl;
    cout << "birthday: " << usr.birthDay << endl;
    cout << "initial Deposit: " << usr.deposit << endl;
    cout << "\n\nType [Y] if all of the information are correct.\nType [N] if you want to re-enter our information: ";
    getline(cin, choice);
    if(choice == "Y" || choice == "y"){buffer = get_uuid(); cout << "Your uniqe id is: " << buffer << endl; usr.accountNumber = stoi(buffer);system("pause"); menu();}

    add(usr);

}

void User::openAcc(){
    cout << "Open Account" << endl;
}



void User::menu(){
    string choice;


    cout << "\e[1;1H\e[2J" << endl;
    cout << "Welcome to atm" << endl;
    cout << "[1]. Registration" << endl;
    cout << "[2]. Sign in" << endl;
    cout << "[3]. Exit" << endl;
    cout << "Pease enter [1-3]: ";

    getline(cin, choice);

    
    if(!(regex_match(choice, numberEx))){
        cout << "Please enter a number!" << endl;
        return;
    }
        
    int c = stoi(choice);

    switch (c)
    {
    case 1:
        registerAcc();
        system("pause");
        break;
    case 2:
        openAcc();
        break;
    case 3:
        exit(0);
        break;
    default:
        cout << "Please enter a valid choice!" << endl;
        break;
    }


}


int main(){

    User *us = new User;
    while (1)
    {
        us->menu();
    }

}