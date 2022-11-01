#include <iostream>
#include <iostream>
#include <random>
#include <regex>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "../hash/sha256.h"
using namespace std;


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

typedef struct info{
    string name, birthDay, contact, pincode;
    int accountNumber;
    float savings;

}INFO;

typedef struct userRecords{
    LIST *recipt;
    INFO inf;
    struct userRecords *next;
}UREC;

class User {
    protected:
    UREC *head;
    UREC acc;

    public:
    void setHead();
    void menu();
    void openAcc();
    void registerAcc();
    void add(INFO inf);
    void retrieve();
    bool validate(int mode, string value);
    
    //for Oppended Accounts
    bool checkPin();
    void checkBal();
    void withdraw();
    void deposit();
    void fundTransfer();      
    void changePin();

    UREC* locate(int accountNumber);
    void accountMenu();
    // TODO Add features.    
};
