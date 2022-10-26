#include <iostream>
#include <regex>
#include <fstream>
#include <ctime>

using namespace std;

// Data Structure

typedef struct info{
    string name;
    int contact;
    int accoutNumber;
    float deposit;
}INFO;

// For Recipts
typedef struct recipt{
    string transactionID, Date;
    float cashIn, cashOut;

    void setTime();
}RECIPT;

typedef struct list{
    RECIPT rec;
    struct list *next;
}LIST;


class User {
    private:
    int pincode;

    public:
    int getPincode();
    int setPincode();
    void menu();
    void openAcc();
    void registerAcc();
    void validate();
};


void RECIPT::setTime(){
    time_t now = time(0);
    Date = ctime(&now);
}

void User::validate(){
    
}


void User::registerAcc(){
    cout << "Register" << endl;
}

void User::openAcc(){
    cout << "Open Account" << endl;
}



void User::menu(){
    string choice;
    regex ex("[-+]?([0-9]*\.[0-9]+|[0-9]+)");

    cout << "Welcome to atm" << endl;
    cout << "[1]. Registration" << endl;
    cout << "[2]. Sign in" << endl;
    cout << "[3]. Exit" << endl;
    cout << "Pease enter [1-3]: ";

    getline(cin, choice);

    
    if(!(regex_match(choice, ex))){
        cout << "Please enter a number!" << endl;
        return;
    }
        
    int c = stoi(choice);

    switch (c)
    {
    case 1:
        registerAcc();
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
    // User *us = new User;
    // while (1)
    // {
    //     cout << "\e[1;1H\e[2J" << endl;
    //     us->menu();
    // }
 

}