
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

regex numberEx("[-+]?([0-9]*\\.[0-9]+|[0-9]+)");          //will check if user put character instead digits
regex nameEx("^[a-zA-Z\\s]*$");                           //will check if user put digits instead character

typedef struct receipt{                                  // structure for user's receipt (resibo)
    string Date;
    float cashIn, cashOut;

    void setTime();
}RECEIPT;                                                // name of struct for receipt

typedef struct list{                                   
    RECEIPT rec;
    string transactionID;
    struct list *next;

}LIST;

typedef struct info{                                   // structure for informations of user
    string name, birthDay, contact, pincode;           // string for name, birthday, contact, and pincode of users
    int accountNumber;                                 // for account numbers of users
    float savings;                                     

}INFO;                                                 // name of structure for info of user

typedef struct userRecords{                            // struct for the records of user
    LIST *receipt;                                     // contains struct for receipt of user
    INFO inf;                                          // contains struct for info of user
    struct userRecords *next;                          // pointer for user's record
}UREC;                                                 // name of struct


//OOP class for user's atm
class User{
    private:
    UREC *head;
    UREC acc;

    UREC *temp;

    string input, buffer, mainKey, userKey;
    public:

    //Getters and Setters
    void setHead();
    void setMainKey(string key);
    void setUserKey(string key);

    void menu();
    void openAcc();
    void registerAcc();
    void add(INFO inf);

    
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
    void saveUserKey();

    //Validations
    bool validate(int mode);
    bool validatePin();
    bool isCardInserted();

    //Cryptography
    void encryptOnOpen();
    void encryptStandard(string path, string key);
    void encryptOnClose();
    void decryptOnOpen();
    void decryptStandard(string path, string key);

    UREC* locate(int accountNumber);
    void accountMenu();
    // TODO Add features.    
};

void User::setHead(){
    head = NULL;
}

void User::setMainKey(string key){
    mainKey = key;
}

void User::setUserKey(string key){
    userKey = key;
}
