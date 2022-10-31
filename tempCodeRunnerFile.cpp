#include <iostream>
#include <random>
#include <regex>
#include <fstream> 
#include <ctime>
#include <time.h>
#include <iomanip>
#include <sstream>

#include "hash/sha256.h"

using namespace std;

extern "C" char* strptime(const char* str, const char* format, struct tm* time) {
  istringstream input(str);
  input.imbue(locale(setlocale(LC_ALL, nullptr)));
  input >> get_time(time, format);
  if (input.fail()) {
    return nullptr;
  }
  return (char*)(str + input.tellg());
}




/// expression

regex numberEx("[-+]?([0-9]*\\.[0-9]+|[0-9]+)");
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
    private:
    UREC *head;
    UREC *acc;

    public:
    void setHead(); //done
    void menu(); // done
    void openAcc(); // done
    void registerAcc(); // done
    void add(INFO inf, UREC *point); // done
    void save(); // done
    void retrieve(string path, int mode); // done
    bool validate(int mode, string value);  // done
    
    //for Oppended Accounts
    bool checkPin(); // done
    void checkBal(); // done
    void withdraw(); // done
    void deposit(int amount);  // not yet
    void fundTransfer(int sent, int recieved);      
    void changePin(); // not yet
    void accountMenu(); // not yet
    // TODO Add features.    
};

void User::setHead(){
    head = NULL;
    acc = NULL;
}

void User::add(INFO inf, UREC *point){
    UREC *pointer, *follower, *temp;
    pointer = follower = point;

    temp = new UREC;
    temp->inf = inf; 

    while (pointer != NULL)
    {
        follower = pointer;
        pointer = pointer->next;
    }

    if(point == pointer){
        point = temp;
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
    usr.pincode = sha256(pincode);

    cout << "Please enter initial deposit: ";
    getline(cin, buffer);
    if(validate(4, buffer)){return;}
    if(stoi(buffer) < 5000){cout << "initial deposit must be a minimum of 5000!" << endl; return;}
    usr.savings = stoi(buffer);

    // confirmation notice
    cout << "\e[1;1H\e[2J" << endl;
    cout << "\nPlease confirm your information!" << endl;
    cout << "Name: " << usr.name << endl;
    cout << "Number: " << usr.contact << endl;
    cout << "birthday: " << usr.birthDay << endl;
    cout << "initial Deposit: " << usr.savings << endl;
    cout << "\n\nType [Y] if all of the information are correct.\nType [N] if you want to re-enter our information: ";
    getline(cin, choice);
    if(choice == "Y" || choice == "y"){buffer = get_uuid(); cout << "Your uniqe id is: " << buffer << endl; usr.accountNumber = stoi(buffer);system("pause"); 
    add(usr, head); menu();}


}

void User::openAcc(){
    cout << "\e[1;1H\e[2J" << endl;
    fstream fp;
    do
    {
        cout << "\e[1;1H\e[2J" << endl;
        cout << "Please insert your card!" << endl;
        fp.open("record.txt", ios::in);
    } while (!fp);
    fp.close();
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Card detected..." << endl;
    retrieve("record.txt", 0);
    system("pause");
    
    accountMenu();
}

void User::save(){
    fstream fp;
    UREC *pointer = head;
    fp.open("records.txt", ios::out);
    if(!fp){
        cout<<" Error while creating the file ";     
    }else{  
        while(pointer != NULL){
            fp << pointer->inf.name << "\n" << pointer->inf.accountNumber << " " << pointer->inf.pincode << " " << pointer->inf.birthDay << " " << pointer->inf.savings << endl;
            pointer = pointer->next;
        }
        fp.close();
            }
}

//TODO Fix the point being NULL

void User::retrieve(string path, int mode){
    fstream fp;
    INFO rec;
    UREC *temp = mode ? head : acc;

    fp.open(path, ios::in);
    if(!fp){
        cout<<" Error while creating the file "; 
    }else{
        if(fp.is_open()){
            while(true){
                getline(fp, rec.name, '\n');
                fp >> rec.accountNumber >> rec.pincode >> rec.birthDay >> rec.savings;
                fp.ignore();
                if(!fp.eof()){
                    add(rec, temp);
                    cout << temp->inf.pincode << endl;
                    system("pause");
                }else{
                    break;
                }
               

            }
            fp.close();

        }
    }
}


bool User::checkPin(){
    string pin;
    cout << "Please enter your PIN: ";
    getline(cin, pin);
    if(!(regex_match(pin, numberEx))){
        cout << "Please enter a number!" << endl;
        return false;
    }

    if(sha256(pin) == acc->inf.pincode){
        return true;
    }
    return false;
}
/*  Change Pin Function
  - open user file (read)
   - enter old pin
    - if old pin = inf.pin
      - enter new pin
        - check if new pin is all number
          - re enter new pin
           - if newPin = rePin
            - change pin successfully
              - close file (write)
           - else newPin != rePin
             - go back to new Pin
           - if newPin = Old pin
             - go back to enter new pin
        - else not go back entering new pin

    - if not, go back enter old pin
  


*/
void User::changePin(){
       INFO inf;
       fstream fp;
       string newPin, oldPin, rePin;
       int i;
       bool valid = false;

       fp.open("record.txt", ios::in); //open file first


       do{
           system("cls");
           cout << "Enter your Old Pincode: " << endl;
           getline(cin, oldPin);

           if (oldPin == inf.pincode){ // if the same
              do{
                     cout << "Enter new 4-6 Digits Pincode: " << endl;
                     getline(cin,newPin);
                 if(!(regex_match(newPin, numberEx))){ // want to check for numbers only
                     cout << "Pincode must only contain numbers!" << endl;
                     changePin();// should go back entering 4-6digits
                    }
                 if (newPin == oldPin){ // check if new and old pin is the same
                      cout << "Please do not enter your old pin"<< endl;
                      changePin(); // should go back entering 4-6digits
                    }
                    else { // if newPin != old newPin
                        cout << "Re-enter your pin" << endl;
                          getline(cin,rePin);
                          if (rePin == newPin){
                             cout << "Change pin successfully" << endl;
                           }
                           else{ //if rePin != newPin
                              cout << "The pin you re-enter is incorrect"<<endl;
                              changePin();// should go back to repin
                           }
                        }
                } while(valid != true);  
                    
                     
                    
               
            
            }else {
               cout << "You entered a wrong pincode!" <<endl;
              } break;

        }while(valid != true);
    
    
       
}

void User::withdraw(){
    string amount;
    cout << "Remaining Balance: " << acc->inf.savings << endl;
    cout << "Much do you want to withdraw [1-" << acc->inf.savings << "]: ";
    getline(cin, amount);
    if(!(regex_match(amount, numberEx))){
        cout << "Please enter a number!" << endl;
        withdraw();
    }
    if(stoi(amount) > acc->inf.savings){
        cout << "Error: The amount you entered is more than your savings!" << endl;
        system("pause");
        withdraw();
    }
    acc->inf.savings = acc->inf.savings - stoi(amount);
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Withdrawn successfully..." << endl;
    system("pause");
}

void User::checkBal(){
    cout << "Current balance: " << acc->inf.savings << endl;
}


void User::accountMenu(){
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Welcome to Student Banks Inc." << endl;
    cout << "[1] Balance Inquiry" << endl;
    cout << "[2] Withdraw" << endl;
    cout << "[3] Deposit" << endl;
    cout << "[4] Fund Transfer" << endl;
    cout << "[5] Change PIN code" << endl;
    cout << "[6] More options..." << endl;
    cout << "[7] Exit" << endl;

    string c;
    getline(cin, c);
     if(!(regex_match(c, numberEx))){
        cout << "Please enter a number!" << endl;
        return;
    }
    

    switch (stoi(c))
    {
    case 1:
        checkBal();
        break;
    case 2:
        withdraw();
        break;
    case 3:
        /* code */
        break;
    case 4:
        /* code */
        break;
    case 5:
        changePin();
        break;
    case 6:
        /* code */
        break;
    case 7:
        exit(0);
        break;
    default:
        break;
    }

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
        save();
        exit(0);
        break;
    default:
        cout << "Please enter a valid choice!" << endl;
        break;
    }


}


int main(){
    User us;
    us.setHead();
    us.retrieve("records.txt", 1);
    while (1)
    {
        us.menu();
    }

    system("cd crypt && ccrypt -e ../record.txt -K 1234");

}