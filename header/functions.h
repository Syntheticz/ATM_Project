

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
         return pointer;  pointer = pointer->next;             // it will return pointer            
    }                                                          // then the pointer will point next
    return NULL;                                               // then return null
}


void User::add(INFO inf){                                      // function for users if they want to register/open atm
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


void User::registerAcc(){                                    // Function for registering/opening acc/atm
    
    if(isCardInserted()){                                   //if usb is detected to be registered this will appear
        cout << "Please insert different card to register.\nThis card was already registered. \nPlease proceed to sign-in." << endl;
        system("pause"); return;                                     
    }

    INFO usr;

    time_t t = time(0);                                      // setting real-time
    tm* now = localtime(&t);

    cout << "\e[1;1H\e[2J" << endl;
    cout << "Please enter your name: ";                     // gets user's name
    getline(cin, input);
    if(validate(2)){registerAcc();}                                         // will validate if user's passed name validation
    usr.name = input;
    system("cls");

    
    cout <<"Welcome to Student Bank Inc., "<<input<<endl;
    cout << "Please enter your phone number: +639";          // gets user's contact number
    getline(cin, input); 
    if(validate(3)){registerAcc();}                          // will validate user's contact number but actually only counts if digits<10
    usr.contact.append("+639");
    usr.contact.append(input);

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
    usr.birthDay = buffer;
    buffer = "";


   
    cout << "Please enter your unique pincode: ";                       //asks user of what pincode they want
    input = asteriskPass();
    if(validate(1)){registerAcc();}
    cout << "\nPlease re-enter your pincode: ";                        //buffer
    buffer = asteriskPass();
    if(validate(5)){registerAcc();}
    userKey = input;
    usr.pincode = sha256(input);                                        //pincode will compare to buffer then save to system

    cout << "\nPlease enter initial deposit: ";                        // asks how much user want to deposit
    getline(cin, input);
    if(validate(6)){registerAcc();}                                   //minimum 5,000 maximum 100,000
    usr.savings = stoi(input);                                        //store deposit

    // confirmation notice
    cout << "\e[1;1H\e[2J" << endl;
    cout << "\nPlease confirm your information!" << endl;                // Function for confirmation
    cout << "Name: " << usr.name << endl;                                // will list all user's detail
    cout << "Number: " << usr.contact << endl;
    cout << "birthday: " << usr.birthDay << endl;
    cout << "initial Deposit: " << usr.savings << endl;
    cout << "\n\nType [Y] if all of the information are correct.\nType [N] if you want to re-enter our information: ";
    getline(cin, input);
    if(input == "Y" || input == "y"){

        buffer = get_uuid(); 
        cout << "Your unique id is: " << buffer << endl; 
        usr.accountNumber = stoi(buffer);
        add(usr); acc.inf = usr; saveToAcc();      // if user confirms, all details will save                                   
    }
}

string User::asteriskPass(){                                              //asterisk password
    char a, pin[6];
    int i=0;
    for (i=0;;){
        a=getch();
        if(a>='0'&& a<='9'){                                            //if user put digits it will turn to asterisk
            pin[i]=a;                                                   //stores a in pass 
            ++i;
            cout<<"*";                                                  // but user can't put letters
        }
        if(a=='\r'){                                                   //if enter is pressed
            pin[i]='\0';                                               //null means end of string.
            break;                                                     // break the loop
        }
        if(a=='\b'&&i>=1){                                             //if user typed backspacei || i should be greater than 1.
                                                    
            cout<<"\b \b";                                             //rub the character behind the cursor.
            --i;
        }

    }
    string aPin = string(pin);                                     // aPin will turn to string pin
    return aPin;                                                   // will return aPin
}

void User::openAcc(){   //Function for user putting usb drive
    START:                                           
    cout << "\e[1;1H\e[2J" << endl;
    fstream fp;
    do
    {
        cout << "\e[1;1H\e[2J" << endl;
        cout << "Please insert your card!" << endl;
        fp.open("g:/pincode.code", ios::in);                       //file read
        cout << "\e[1;1H\e[2J" << endl;
    } while (!fp);
        fp.seekg(0, ios::end);
      if(fp.tellg() == 0){                                         //If system didn't track that the usb is registered
          fp.close();                                              // The path will closed
          cout << "There is no registered user on this card!" << endl;    
          cout << "Do you want to register? type [Y] for yes and [N] for no: ";  // will ask if user wants to register if no, it will just loop again
          getline(cin, input);
          if(input == "y" || input == "Y"){
             registerAcc();                                          // if yes, user will go to registerAcc function
                acc.inf = temp->inf;                                    // the account info will store as temp info
             fp.open("g:/pincode.code", ios::out);                   // file write
              if(fp.is_open()){
                fp << acc.inf.pincode;
            }
        }
        fp.close();
    }
    fp.close();


    cout << "\e[1;1H\e[2J" << endl;
    cout << "Card detected..." << endl;                            // card detecting 
    if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause");goto START;}  //if pin does not match it will just loop

    accountMenu();                                                  // if pin matched, it will proceed to account menu
}

bool User::checkPin(){                                             // Function checking pin before you access your private details
    cout << "Please enter your PIN: ";                             // will ask user for their pin
    input = asteriskPass();                                        // asterisk password
    if(validatePin()){cout << "Wrong Pin!" << endl; return false;} // will return false if pin is unmatched
    userKey = input;                                               // will compare the system pin to the input made by user
    retrieveAcc();
    if(sha256(input) == acc.inf.pincode){                          // and when pin matched
        cout << "PIN MATCHED!" << endl;
        return true;                                               //will return true
    }
    return false;                                                // if not will return false
}

void User::withdraw(){                                           // Function for withdrawal
    string amount;                                               // variable for user's amount input
    cout << "Remaining Balance: " << head->inf.savings << endl;    //display remaining balance
    cout << "How much do you want to withdraw [1-" << head->inf.savings << "]: ";  //asking user for amount of withdrawal
    getline(cin, amount);

    if(!(regex_match(amount, numberEx))){
        cout << "PLEASE ENTER NUMBERS ONLY!" << endl;
        withdraw();
    }
    if(stoi(amount) > head->inf.savings){                           //if user's input amount is greater than its savings
        cout << "INSUFFICIENT SAVINGS!" << endl;                    // system will prompt insufficient savings
        system("pause");  withdraw();
    }
    head->inf.savings = head->inf.savings - stof(amount);           // if input is lesser than saving
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Your money is safe with us" << endl;                    //user will proceed
    cout << "THANK YOU FOR WITHDRAWING AT STUDENTS BANK INC." << endl;
    checkBal(); system("pause");                                                     // will display balance before exit
}

void User::checkBal(){                                             // Function for displaying remaining balance for savings
    cout <<"Hi!, "<< acc.inf.name << endl;
    cout << " \nCURRENT BALANCE: " << acc.inf.savings << endl;
    system("pause");
}

void User::deposit(){                                              //Function for money deposit
    string amount;                                                 // variable for user's amount input
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Please enter the amount you want to deposit: ";       // will ask user for amount of deposit
    getline(cin, amount);
    if(!(regex_match(amount, numberEx))){
        cout << "PLEASE ENTER NUMBERS ONLY!" << endl;
        deposit();
    }
    head->inf.savings = head->inf.savings + stof(amount);          // If money in savings will add up
    cout << "DEPOSIT SUCCESSFUL!" << endl;                         // User can proceed
    checkBal();                                                    // will display remaining balance before exit
}



void User::fundTransfer(){                                         // Function for fund transfer, user is sender
                                           
    string amount, accountNum, c;                                  // variables used
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Please enter the recipient's account number: ";       // will ask user for the recipients' account number
    getline(cin, accountNum);
    if(!(regex_match(accountNum, numberEx))){
        cout << "PLEASE ENTER NUMBERS ONLY!" << endl;
        fundTransfer();
    }
    if(stoi(accountNum) == acc.inf.accountNumber ){                // Just to make sure user won't send money to itself
        cout << "You can't send money to yourself" << endl;
        fundTransfer();
    }

    UREC *point = locate(stoi(accountNum));                        // will locate the account number that user input
    if(point == NULL){                                             // if null
        cout << "\e[1;1H\e[2J" << endl;
        cout << "User not found!" << endl;                         // account not found 
        cout << "The user must need to register first!" << endl;   
        system("pause"); fundTransfer();                           // will just call the function again                        
    }

   
    cout << "\e[1;1H\e[2J" << endl;
    cout << "You are transfering funds to an individual named: " << point->inf.name << endl;  //displays recipient's name
    cout << "With and account number of " << point->inf.accountNumber << endl;                //displays recipient's account number
    cout << "Do you still want to continue? [Y] yes or [N] no: ";
    getline(cin, c);
    if(c == "y" || c == "Y"){
        cout << "Please enter the amount you want to transfer [1-" << acc.inf.savings << "]: ";  // displays user's savings
        getline(cin, amount);
        if(!(regex_match(amount, numberEx))){
            cout << "PLEASE ENTER NUMBERS ONLY!" << endl;
            system("pause");  fundTransfer();
        }
        if(stof(amount) > acc.inf.savings){                                                   // will check if the input amount of user is greater than his/her savings
            cout << "INSUFFICIENT SAVINGS!" << endl;
            system("pause"); fundTransfer();
        }
        if(stof(amount) > 100){
            cout << "Fund transfering must be a minimum of 100 php"<<endl;                   // fund transfering minimum of 100 pesos
            fundTransfer();
        }

        if(stof(amount) < 1){                                                                 // will check if the amount is valid/invalid
            cout << "INVALID AMOUNT!" << endl;
            system("pause"); fundTransfer();
        }

        acc.inf.savings = acc.inf.savings - stof(amount);                                    // if true, the savings of user's account will decrease
        point->inf.savings = point->inf.savings + stof(amount);                              // the recipient's savings account will increase
        cout << "\e[1;1H\e[2J" << endl;
        cout << "THANK YOU FOR TRUSTING STUDENT BANK INC." << endl;
        cout << "Fund transfered successfully!" << endl;                                     // fund transfer successfully
        checkBal(); system("pause"); return;                                                                        // wil display remaining balance before exit
    }

    return;


}

void User::changePin(){                                          // Function for changing pin
    string oldPin, buffer, cPin;                                 // variables used
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Change Pin..." << endl;
    cout << "Please enter your current pin: ";                   // asks for user's old pin
    oldPin = asteriskPass();                                     // asterisk password
    if(!(regex_match(oldPin, numberEx))){
        cout << "PLEASE ENTER NUMBERS ONLY!" << endl;       
        changePin();
    }
    if(sha256(oldPin) != acc.inf.pincode){                       //will check if input pin does not match to system pin
        cout << "PIN does not match" << endl; 
        system("pause"); changePin();
    }else{
        cout << "Please enter your new pin: ";                  // if true, prompt user to new pin
        cPin = asteriskPass();                           
        if(!(cPin.length() == 6 || cPin.length() == 4)){       // new pin must be 4 or 6-digit
            cout << "Pincode must only be a 4 or 6 digit number!" << endl; 
            changePin();
        }
        if(sha256(oldPin)==cPin){                              // will check if user puts old pin 
            cout <<"Please don't use your old pin"<<endl;      // user can't use its old pin
            system("pause");
        }
        cout << "Please re-enter in your new pin: ";          // if true, user can re-enter its new pin
        buffer = asteriskPass();
        if(buffer != cPin){                                   // will check if the new pin and reenter new pin does not match
            cout << "PIN does not match" << endl;
            system("pause");
        }else{
            acc.inf.pincode = sha256(buffer);                 // if true, then the re-enter pin will be saved
            cout << "PIN changed sucessfully!" << endl;
            saveToAcc();system("pause");
        }
    }
}


void User::accountMenu(){                                                            // Function of the system once the user is already registered
    if(!(checkPin())){cout << "WRONG PIN!" << endl; system("pause"); accountMenu();} // will ask user for pin before proceed, if unmatched it will just loop
    START:
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Welcome to Student Banks Inc." << endl;
    cout << "[1] Balance Inquiry" << endl;
    cout << "[2] Withdraw" << endl;
    cout << "[3] Deposit" << endl;
    cout << "[4] Fund Transfer" << endl;
    cout << "[5] Change PIN code" << endl;
    cout << "[6] More options..." << endl;
    cout << "[7] Exit" << endl;
    cout << "Please numbers [1-7] only!: ";
    string c;
    getline(cin, c);
    if(!(regex_match(c, numberEx))){
        cout << "PLEASE ENTER NUMBERS ONLY!" << endl; return;
    }
    

    switch (stoi(c))                 //Every choices needs to put pin first, if pin does not match, user doesn't need to put pin from the start
    {                                // it will just go to the menu immediately
    case 1:
        if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause"); goto START;}
        checkBal(); break;
    case 2:
        if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause"); goto START;}
        withdraw();break;
    case 3:
        if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause"); goto START;}
        deposit(); break;
    case 4:
        if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause"); goto START;}
        fundTransfer(); break;
    case 5:
        if(!(checkPin())){cout << "Wrong Pin!" << endl; system("pause"); goto START;}
        changePin(); break;
    case 6:
        /* code */
        break;
    case 7:
        save(); saveToAcc();exit(0); break;
    default:
        cout << "Please enter numbers 1-7 only!" << endl;break;
    }

}


void User::menu(){                           //Function for menu of the entire system
    string choice;

    cout << "\e[1;1H\e[2J" << endl;
    cout << "Welcome to atm" << endl;
    cout << "[1]. Registration" << endl;
    cout << "[2]. Sign in" << endl;
    cout << "[3]. Exit" << endl;
    cout << "Please enter [1-3]: ";

    getline(cin, choice);
    
    if(!(regex_match(choice, numberEx))){
        cout << "PLEASE ENTER NUMBERS ONLY!" << endl;
        return;
    }
        
    int c = stoi(choice);               // string to int

    switch (c)
    {
    case 1: // case 1 for registration
        cout << "REGISTRATION" << endl; registerAcc(); system("pause"); break;
    case 2: // case 2 for signing in
        cout << "SIGN-IN" << endl;openAcc();break;
    case 3: // case 3 for exit
        cout << "THANK YOU FOR USING STUDENT BANK INC." << endl;save();exit(0); break;
    default:
        cout << "Please enter numbers 1-3 only!" << endl;break;
    }


}

