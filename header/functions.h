

using namespace std;


#include "validation.h" /// expression





string get_uuid() {                                                      //will generate a unique transaction ID

    static mt19937 rng(time(0));                                         // random number generator

    uniform_int_distribution<int> dist(0, 9);

    const char *v = "0123456789";
    string res;
    for (int i = 0; i < 5; i++) {
        res += v[dist(rng)];
    }
    return res;
}

extern "C" char* strptime(const char* str, const char* format, struct tm* time) {
  istringstream input(str);
  input.imbue(locale(setlocale(LC_ALL, nullptr)));
  input >> get_time(time, format);
  if (input.fail()) {
    return nullptr;
  }
  return (char*)(str + input.tellg());
}


UREC* User::locate(int accountNumber){                         // will locate account number
    UREC *pointer = head;
    while(pointer != NULL){
        if(accountNumber == pointer->inf.accountNumber)
         return pointer;
        pointer = pointer->next;
    }
    return NULL;
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


void RECEIPT::setTime(){
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
    add(usr); menu();}


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
    retrieveAcc();
    system("pause");
    
    accountMenu();
}

bool User::checkPin(){
    string pin;
    cout << "Please enter your PIN: ";
    getline(cin, pin);
    if(!(regex_match(pin, numberEx))){
        cout << "Please enter a number!" << endl;
        return false;
    }

    if(sha256(pin) == acc.inf.pincode){
        return true;
    }
    return false;
}

void User::withdraw(){
    string amount;
    cout << "Remaining Balance: " << head->inf.savings << endl;
    cout << "Much do you want to withdraw [1-" << head->inf.savings << "]: ";
    getline(cin, amount);

    if(!(regex_match(amount, numberEx))){
        cout << "Please enter a number!" << endl;
        withdraw();
    }
    if(stoi(amount) > head->inf.savings){
        cout << "Error: The amount you entered is more than your savings!" << endl;
        system("pause");
        withdraw();
    }
    head->inf.savings = head->inf.savings - stof(amount);
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Withdrawn successfully..." << endl;
    checkBal();
    system("pause");
}

void User::checkBal(){
    cout << acc.inf.name<< " your current balance is " << acc.inf.savings << endl;
    system("pause");
}

void User::deposit(){
    string amount;
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Please enter in the amount that you want to deposit: ";
    getline(cin, amount);
    if(!(regex_match(amount, numberEx))){
        cout << "Please enter a number!" << endl;
        deposit();
    }
    if(stof(amount) == 0){
        cout << "Please enter a valid amount!" << endl;
        deposit();
    }
    head->inf.savings = head->inf.savings + stof(amount);
    cout << "Deposit Successfull!" << endl;
    checkBal();
}



void User::fundTransfer(){
    string amount, accountNum, c;
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Please enter in the account number that you want to transfer fund to: ";
    getline(cin, accountNum);
    if(!(regex_match(accountNum, numberEx))){
        cout << "Please enter a number!" << endl;
        fundTransfer();
    }

    UREC *point = locate(stoi(accountNum));
    if(point == NULL){
        cout << "\e[1;1H\e[2J" << endl;
        cout << "User not found!" << endl;
        system("pause");
        fundTransfer();
    }

    //TODO have this in another function
    cout << "\e[1;1H\e[2J" << endl;
    cout << "You are transfering funds to an individual named: " << point->inf.name << endl;
    cout << "With and account number of " << point->inf.accountNumber << endl;
    cout << "Do you still want to continue? [Y] yes or [N] no: ";
    getline(cin, c);
    if(c == "y" || c == "Y"){
        cout << "Please enter in the amount that you want to transfer [1-" << acc.inf.savings << "]: ";
        getline(cin, amount);
        if(!(regex_match(amount, numberEx))){
            cout << "Please enter a number!" << endl;
            system("pause");
            fundTransfer();
        }
        if(stof(amount) > acc.inf.savings){
            cout << "Entered amount must not be more than your savings!" << endl;
            system("pause");
            fundTransfer();
        }

        if(stof(amount) < 1){
            cout << "Entered amount must be a valid amount!" << endl;
            system("pause");
            fundTransfer();
        }

        acc.inf.savings = acc.inf.savings - stof(amount);
        point->inf.savings = point->inf.savings + stof(amount);
        cout << "\e[1;1H\e[2J" << endl;
        cout << "Fund transfered successfully!" << endl;
        checkBal();
        system("pause");
        return;
    }

    return;


}

void User::changePin(){
    string pin, buffer;
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Change Pin..." << endl;
    cout << "Please enter in your current pin: ";
    getline(cin, pin);
    if(!(regex_match(pin, numberEx))){
        cout << "Please enter a number!" << endl;
        changePin();
    }
    if(sha256(pin) != acc.inf.pincode){
        cout << "PIN does not match" << endl;
        system("pause");
        changePin();
    }else{
        cout << "Please enter in your new pin: ";
        getline(cin, pin);
        if(!(pin.length() == 6 || pin.length() == 4)){cout << "Pincode must only be a 4 or 6 digit number!" << endl; changePin();}
        cout << "Please re-enter in your new pin: ";
        getline(cin, buffer);
        if(buffer != pin){
            cout << "PIN does not match" << endl;
            system("pause");
        }else{
            acc.inf.pincode = sha256(pin);
            cout << "PIN changed sucessfully!" << endl;
            saveToAcc();
            system("pause");
        }
    }
}

// TODO make user not to enter pin again when wrong on the below choices
void User::accountMenu(){
     if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause"); accountMenu();}
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Welcome to Student Banks Inc." << endl;
    cout << "[1] Balance Inquiry" << endl;
    cout << "[2] Withdraw" << endl;
    cout << "[3] Deposit" << endl;
    cout << "[4] Fund Transfer" << endl;
    cout << "[5] Change PIN code" << endl;
    cout << "[6] More options..." << endl;
    cout << "[7] Exit" << endl;
    cout << "Please enter in [1-7]: ";
    string c;
    getline(cin, c);
    if(!(regex_match(c, numberEx))){
        cout << "Please enter a number!" << endl;
        return;
    }
    

    switch (stoi(c))
    {
    case 1:
        if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause"); accountMenu();}
        checkBal();
        break;
    case 2:
        if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause"); accountMenu();}
        withdraw();
        break;
    case 3:
        if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause"); accountMenu();}
        deposit();
        break;
    case 4:
        if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause"); accountMenu();}
        fundTransfer();
        break;
    case 5:
        if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause"); accountMenu();}
        changePin();
        break;
    case 6:
        /* code */
        break;
    case 7:
        exit(0);
        break;
    default:
        cout << "Please enter in a valid choice!" << endl;
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

