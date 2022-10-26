#include <iostream>
#include <random>
#include <regex>
#include <fstream> 
#include <ctime>

using namespace std;

/// global variables

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

    string get_uuid();
}LIST;


//Generate a unique transactio ID
string list::get_uuid() {
    static random_device dev;
    static mt19937 rng(dev());

    uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    string res;
    for (int i = 0; i < 16; i++) {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}


// Data structure for Users

typedef struct info{
    string name;
    int contact;
    int accoutNumber;
    float deposit;
}INFO;

typedef struct userRecords{
    LIST *recipt;
    INFO inf;
    struct userRecords *next;

}UREC;

class User {
    private:

    int pincode;

    public:
    int getPincode();
    int setPincode();
    void menu();
    void openAcc();
    void registerAcc();
    bool validate(int mode, string value);
};


void RECIPT::setTime(){
    time_t now = time(0);
    Date = ctime(&now);
}


bool User::validate(int mode, string value){
    switch (mode)
    {
    case 1:
            if(regex_match(value, nameEx))
                return false;
        break;
    
    default:
        break;
    }
    return true;
}



void User::registerAcc(){
    string name;

    cout << "Please enter your name" << endl;
    getline(cin, name);

    if(validate(1, name)){cout << "the name you entered is not a valid one." << endl; return;}



}

void User::openAcc(){
    cout << "Open Account" << endl;
}



void User::menu(){
    string choice;


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


int main(int argc, char *argv[]){
    User *us = new User;
    while (1)
    {
        cout << "\e[1;1H\e[2J" << endl;
        us->menu();
    }
 

}