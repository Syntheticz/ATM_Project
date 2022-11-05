

#include "validation.h" /// expression

void RECEIPT::setTime(){                                                  ////Function to set real-time in receipt of user
    time_t now = time(0);
    Date = ctime(&now);
}

string get_uuid() {                                                      //will generate a unique transaction number

    static mt19937 rng(time(0));                                         // random number generator

    uniform_int_distribution<int> dist(0, 9);

    const char *v = "0123456789";
    string res;
    for (int i = 0; i < 5; i++) {
        res += v[dist(rng)];
    }
    return res;
}


UREC* User::locate(int accountNumber){                         // will locate account number
    UREC *pointer = head;                                      // set head pointer to null
    while(pointer != NULL){
        if(accountNumber == pointer->inf.accountNumber)        // if the account number is registered to our system
         return pointer;                                       // it will return pointer
        pointer = pointer->next;                               // then the pointer will point next
    }
    return NULL;                                               // then return null
}


void User::add(UREC *temp){                                      // function for users if they want to register/open atm
    UREC *pointer, *follower, *t;
    pointer = follower = head;

    t = new UREC;
    t->inf = temp->inf;

    while (pointer != NULL)
    {
        follower = pointer;
        pointer = pointer->next;
    }

    if(head == pointer){
        head = t;
    }else{
        follower->next = t;
        t->next = pointer;
    }

}


void User::registerAcc(){                                    // Function for registering/opening acc/atm
    
    if(isCardInserted()){                                   //if usb is detected to be registered this will appear
        cout << "Please insert different card to register.\nThis card was already registered. \nPlease proceed to sign-in." << endl;
        system("pause");                                     
        return;
    }

    UREC *usr = new UREC;

    time_t t = time(0);                                      // setting real-time
    tm* now = localtime(&t);

    cout << "\e[1;1H\e[2J" << endl;
    cout << "Please enter your name: ";                     // gets user's name
    getline(cin, input);
    if(validate(2)){registerAcc();}                                         // will validate if user's passed name validation
    usr->inf.name = input;
    system("cls");

    
    cout <<"Welcome to Student Bank Inc., "<<input<<endl;
    cout << "Please enter your phone number: +639";          // gets user's contact number
    getline(cin, input); 
    if(validate(3)){registerAcc();}                          // will validate user's contact number but actually only counts if digits<10
    usr->inf.contact.append("+639");
    usr->inf.contact.append(input);

    buffer = "";
    cout << "Please enter your birthday\nMonth [1-12] [MM]:  ";    //gets user's birthdate 
    getline(cin, input);
    month = stoi(input);
    if(validate(1)){registerAcc();}                                // will validate if input is correct
    buffer.append(input + "/");
    
    cout << "Day [01-30] [dd]: ";                                  //gets user's birthmonth 
    getline(cin, input);
    day = stoi(input);
    if(validate(1)){registerAcc();}                                // will validate if input is correct
    buffer.append(input + "/");

    //TODO fix age restrictions
    cout << "Year Ex. 2001 [YYYY]: ";                               //gets user's birthyear
    getline(cin, input);
    if(validate(1)){registerAcc();}                                // will validate if input is correct
    year = stoi(input);
    buffer.append(input);
    if(validate(4)){registerAcc();}
    usr->inf.birthDay = buffer;
    buffer = "";


   
    cout << "Please enter in your pincode: ";
    input = asteriskPass();
    if(validate(1)){registerAcc();}
    cout << "\nPlease re-enter your pincode: ";
    buffer = asteriskPass();
    if(validate(5)){registerAcc();}
    userKey = input;
    usr->inf.pincode = sha256(input);

    cout << "\nPlease enter initial deposit: ";
    getline(cin, input);
    if(validate(6)){registerAcc();}
    usr->inf.savings = stoi(input);

    // confirmation notice
    cout << "\e[1;1H\e[2J" << endl;
    cout << "\nPlease confirm your information!" << endl;
    cout << "Name: " << usr->inf.name << endl;
    cout << "Number: " << usr->inf.contact << endl;
    cout << "birthday: " << usr->inf.birthDay << endl;
    cout << "initial Deposit: " << usr->inf.savings << endl;
    cout << "\n\nType [Y] if all of the information are correct.\nType [N] if you want to re-enter our information: ";
    getline(cin, input);
    if(input == "Y" || input == "y"){

        buffer = get_uuid(); 
        cout << "Your unique id is: " << buffer << endl; 
        usr->inf.accountNumber = stoi(buffer);
        add(usr);
        acc.inf = usr->inf;
        saveToAcc();
    }
}

string User::asteriskPass(){
    char pin[6];
    int i=0;
    char a;
    for (i=0;;){
        a=getch();
        if(a>='0'&& a<='9'){
            pin[i]=a;
            ++i;
            cout<<"*";
        }
        if(a=='\r'){
            pin[i]='\0';
            break;
        }
        if(a=='\b'&&i>=1){
            cout<<"\b \b";
            --i;
        }

    }
    string finals = string(pin);
    return finals;
}

void User::openAcc(){
    cout << "\e[1;1H\e[2J" << endl;
    fstream fp;
    do
    {
        cout << "\e[1;1H\e[2J" << endl;
        cout << "Please insert your card!" << endl;
        fp.open("g:/pincode.code", ios::in);
        cout << "\e[1;1H\e[2J" << endl;
    } while (!fp);
    fp.seekg(0, ios::end);
    if(fp.tellg() == 0){
        fp.close();
        cout << "There is no registered user on this card!" << endl;
        cout << "Do you want to register? type [Y] for yes and [N] for no: ";

        getline(cin, input);
        if(input == "y" || input == "Y"){
            registerAcc();
            acc.inf = temp->inf;          
            fp.open("g:/pincode.code", ios::out);
            if(fp.is_open()){
                fp << acc.inf.pincode;
            }
            fp.close();

            
            }else{
                return;
            }
    }
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Card detected..." << endl;

    checkPin();

    while(1){
        accountMenu();
    }


   
}

void User::checkPin(){
    START:
    cout << "Please enter your PIN: ";
    input = asteriskPass();
    if(validate(1)){cout << "Please enter a valid PIN!" << endl; system("pause"); goto START;}
    if(validatePin()){cout << "\e[1;1H\e[2J" << endl; cout << "\nWrong Pin!" << endl; system("pause"); goto START;}
    userKey = input;
    retrieveAcc();

    
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
    cout << acc.inf.name << " your current balance is " << acc.inf.savings << endl;
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
    cout << "Please enter your current pin: ";
    getline(cin, pin);
    cout <<"*"<< pin<<endl;
    if(!(regex_match(pin, numberEx))){
        cout << "PLEASE ENTER NUMBERS ONLY!" << endl;
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
        cout << "PLEASE ENTER NUMBERS ONLY!" << endl;
        return;
    }
    

    switch (stoi(c))
    {
    case 1:
        checkPin();
        checkBal();
        break;
    case 2:
        checkPin();
        withdraw();
        break;
    case 3:
        checkPin();
        deposit();
        break;
    case 4:
        checkPin();
        fundTransfer();
        break;
    case 5:
        checkPin();
        changePin();
        break;
    case 6:
        /* code */
        break;
    case 7:
        save();
        saveToAcc();
        exit(0);
        break;
    default:
        cout << "Please enter numbers 1-7 only!" << endl;
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
    cout << "Please enter [1-3]: ";

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
        if(head != NULL){ save();}
        exit(0);
        break;
    default:
        cout << "Please enter numbers 1-3 only!" << endl;
        break;
    }


}

