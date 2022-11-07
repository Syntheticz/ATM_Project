

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
    
    setFontStyle(40);
    string Menu[7] =  {"  BALANCE INQUIRY  ", " WITHDRAW ", " DEPOSIT ", " FUND TRANSFER ", " CHANGE PIN ", " MORE TRANSACTIONS ", " EXIT "};
    int pointer = 0;
    const char ENTER = 13;//ASCII code for ENTER Key
    char ch = ' ';
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while(true){
        system("cls");
        ShowConsoleCursor(false);

         for(int i=0; i<7; ++i){
            //This will highlight the choice in the menu
            if(i==pointer){
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 1);
                cout << Menu[i] << endl;
            }else{
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 15); // set color of the text to white
                cout << Menu[i] << endl;
            }
             SetConsoleTextAttribute(hConsole, 15);
        }
        //This will check the key stroke that is being pressed in keyboard
        while(true){
            if(GetAsyncKeyState(VK_UP) != 0){
                --pointer;
                if(pointer == -1){
                    pointer = 7;
                }
                break;
            }else if(GetAsyncKeyState(VK_DOWN) != 0){
                ++pointer;
                if(pointer == 7){
                    pointer = 0;
                }
                break;
            }else if(ch=getch() == ENTER){
                switch(pointer){
                    case 0:
                    {
                        ShowConsoleCursor(true);
                        checkBal();
                        cout <<" Balance Inquiry\n";
                        system("pause");
                        break;
                    }
                    case 1:
                    {
                        
                        ShowConsoleCursor(true);
                        withdraw();
                        cout <<"WITHDRAW\n";
                        system("pause");
                        break;
                    }
                     case 2:
                    {
                        
                        ShowConsoleCursor(true);
                        deposit();
                        cout <<"DEPOSIT\n";
                        system("pause");
                        break;
                    }
                     case 3:
                    {
                        
                        ShowConsoleCursor(true);
                        fundTransfer();
                        cout <<"FUND TRANSFER\n";
                        system("pause");
                        break;
                    }
                     case 4:
                    {
                        
                        ShowConsoleCursor(true);
                        changePin(); 
                        cout <<"CHANGE PIN\n";
                        system("pause");
                        break;
                    }
                     case 5:
                    {
                        
                        ShowConsoleCursor(true);
                        withdraw();
                        cout <<"MORE TRANSACTIONS\n";
                        system("pause");
                        break;
                    }
                    case 6:
                    {
                        ShowConsoleCursor(true);
                        cout <<"THANK YOU FOR USING STUDENT BANK INC.\n";
                        system("pause");
                        exit(0);
                    }
                } break;
    }  }    }
}
void gotoxy(int x,int y){
    COORD coord = {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void SetColor(int ForgC){
  WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

void setFontStyle(int FontSize){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = FontSize;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Times New Roman"); // font style
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}




 void User::menu(){                           //Function for menu of the entire system

    setFontStyle(40);
    string Menu[3] =  {"  REGISTRATION  ", " SIGN-IN ", " EXIT "};
    int pointer = 0;
    const char ENTER = 13;//ASCII code for ENTER Key
    char ch = ' ';
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while(true){
        system("cls");
        ShowConsoleCursor(false);   
        
                gotoxy(12,1);cout<<"             .----------------.  .----------------.  .----------------. "<<endl;
                gotoxy(12,2);cout<<"             | .--------------. || .--------------. || .--------------. |"<<endl;
                gotoxy(12,3);cout<<"             | |    _______   | || |   ______     | || |      _____   | |"<<endl;
                gotoxy(12,4);cout<<"             | |   /  ___  |  | || |  |_   _ \\    | || |     |_   _|  | |"<<endl;
                gotoxy(12,5);cout<<"             | |   | (__ \\_|  | || |   | |_) |    | || |       | |    | |"<<endl;
                gotoxy(12,6);cout<<"             | |   '.___`-.   | || |   |  __'.    | || |       | |    | |"<<endl;
                gotoxy(12,7);cout<<"             | |  | \\____) |  | || |  _| |__) |   | || |      _| |_   | |"<<endl;
                gotoxy(12,8);cout<<"             | |  |_______.'  | || |  |_______/   | || |     |_____|  | |"<<endl;
                gotoxy(12,9);cout<<"             | |              | || |              | || |              | |"<<endl;
                gotoxy(12,10);cout<<"            | '--------------' || '--------------' || '--------------' |"<<endl;
                gotoxy(12,11);cout<<"            '----------------'  '----------------'  '----------------' "<<endl;
                                                                                                    
        gotoxy(52,20);cout << "MAIN MENU\n\n";
        // gotoxy(35, 16);
        // cout<<"\nUSE UP OR DOWN ARROW KEYS TO NAVIGATE THROUGH MENU\n";


        for(int i=0; i<3; ++i){
            //This will highlight the choice in the menu
            if(i==pointer){
                gotoxy(47,25+i);
                SetConsoleTextAttribute(hConsole, 1);
                cout << Menu[i] << endl;
            }else{
                gotoxy(47,25+i);
                SetConsoleTextAttribute(hConsole, 15); // set color of the text to white
                cout << Menu[i] << endl;
            }
             SetConsoleTextAttribute(hConsole, 15);
        }
        //This will check the key stroke that is being pressed in keyboard
        while(true){
            if(GetAsyncKeyState(VK_UP) != 0){
                --pointer;
                if(pointer == -1){
                    pointer = 3;
                }
                break;
            }else if(GetAsyncKeyState(VK_DOWN) != 0){
                ++pointer;
                if(pointer == 3){
                    pointer = 0;
                }
                break;
            }else if(ch=getch() == ENTER){
                switch(pointer){
                    case 0:
                    {
                        ShowConsoleCursor(true);
                        retrieveAcc();
                        cout <<" REGISTRATION\n";
                        system("pause");
                        break;
                    }
                    case 1:
                    {
                        
                        ShowConsoleCursor(true);
                        openAcc();
                        cout <<"SIGN-IN\n";
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        ShowConsoleCursor(true);
                        cout <<"THANK YOU FOR USING STUDENT BANK INC.\n";
                        system("pause");
                        exit(0);
                    }
                    // case 3:
                    // {
                    //     ShowConsoleCursor(true);
                    //     //userDisplayStudents();
                    //     cout <<" Add Student Record\n";
                    //     system("pause");
                    //     break;

                    // }
                    // case 4:
                    // {
                    //     ShowConsoleCursor(false);
                    //     //STUDENTS.saveRecords();
                    //     //exitMessage();
                    //     cout <<" Return home\n";
                    //     system("pause");
                    //     exit(0);
                    // }
                }
                break;
            }
        }

    }
}


