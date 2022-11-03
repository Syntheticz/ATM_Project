#include <iostream>
#include <iostream>
#include <random>
#include <regex>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "../sha256.h"
using namespace std;

regex numberEx("[-+]?([0-9]*\\.[0-9]+|[0-9]+)");
regex nameEx("^[a-zA-Z\\s]*$");

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

class User{
    private:
    string key;

    protected:
    UREC *head;
    UREC acc;

    string input, buffer;
    public:


    void setHead();
    void menu();
    void openAcc();
    void registerAcc();
    void add(INFO inf);
    bool validate(int mode);
    
    //for Oppended Accounts
    bool checkPin();
    void checkBal();
    void withdraw();
    void deposit();
    void fundTransfer();      
    void changePin();

    //File Handling
    void save();
    void saveToAcc();
    void retrieve();
    void retrieveAcc();

    //Cryptography
    void encryptOnOpen();
    void encryptStandard(string path);
    void encryptOnClose();
    void decryptOnOpen();
    void decryptStandard(string path);
    void setKey(string key);

    UREC* locate(int accountNumber);
    void accountMenu();
    // TODO Add features.    
};

void User::setHead(){
    head = NULL;
}

void User::setKey(string key){
    this->key = key;
}
