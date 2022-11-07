#include "validation.h"





tm* User::setTime(){                                                  ////Function to set real-time in receipt of user
    time_t t = time(0);
    tm* time = localtime(&t);
    return time;
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
       cout<<" _____  ______ _____ _____  _____ _______ _____         _______ _____ ____  _   _ "<<endl;
       cout<<"|  __ \\|  ____/ ____|_   _|/ ____|__   __|  __ \\     /\\|__   __|_   _/ __ \\| \\ | |"<<endl;
       cout<<"| |__) | |__ | |  __  | | | (___    | |  | |__) |   /  \\  | |    | || |  | |  \\| |"<<endl;
       cout<<"|  _  /|  __|| | |_ | | |  \\___ \\   | |  |  _  /   / /\\ \\ | |    | || |  | | . ` |"<<endl;
       cout<<"| | \\ \\| |___| |__| |_| |_ ____) |  | |  | | \\ \\  / ____ \\| |   _| || |__| | |\\  |"<<endl;
       cout<<"|_|  \\_\\______\\_____|_____|_____/   |_|  |_|  \\_\\/_/    \\_\\_|  |_____\\____/|_| \\_|"<<endl;
            
    if(isCardInserted()){                                   //if usb is detected to be registered this will appear
          cout << "Please insert different card to register.\nThis card was already registered. \nPlease proceed to sign-in." << endl;
        system("pause"); return;                                     
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


    cout << "Year Ex. 2001 [YYYY]: ";                               //gets user's birthyear
    getline(cin, input);
    if(validate(1)){registerAcc();}                                // will validate if input is correct
    year = stoi(input);
    buffer.append(input);
    if(validate(4)){registerAcc();}
    usr->inf.birthDay = buffer;
    buffer = "";


   
      cout << "Please enter your unique pincode: ";                       //asks user of what pincode they want
    input = asteriskPass();
    if(validate(1)){registerAcc();}
      cout << "\nPlease re-enter your pincode: ";                        //buffer
    buffer = asteriskPass();
    if(validate(5)){registerAcc();}
    userKey = input;
    usr->inf.pincode = sha256(input);

    cout << "\nPlease enter initial deposit: ";                        // asks how much user want to deposit
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

        buffer = "";
        buffer = get_uuid(); 

        int uuid = stoi(buffer);
        cout << "Your unique id is: " << uuid << endl; 
        usr->inf.accountNumber = uuid;
        add(usr);
        acc.inf = usr->inf;
        saveToAcc();
        save();

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
    fp.seekg(0, ios::end);
    if(fp.tellg() == 0){
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

void User::withdraw(){                                           // Function for withdrawal

    decryptStandard(CARD_PATH_ENCRYPTION, userKey);                                             // variable for user's amount input
    cout << "Remaining Balance: " << acc.inf.savings << endl;    //display remaining balance
    cout << "How much do you want to withdraw [1-" << acc.inf.savings << "]: ";  //asking user for amount of withdrawal
    getline(cin, input);

    if(validate(1))
        return;
        
    if(stoi(input) > acc.inf.savings){                           //if user's input amount is greater than its savings
        cout << "INSUFFICIENT SAVINGS!" << endl;                    // system will prompt insufficient savings
        system("pause");
        withdraw();
    }
    acc.inf.savings = acc.inf.savings - stof(input);           // if input is lesser than saving
    UREC *pointer = locate(acc.inf.accountNumber);
    pointer->inf.savings = acc.inf.savings;
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Your money is safe with us" << endl;                    //user will proceed
    cout << "THANK YOU FOR WITHDRAWING AT STUDENTS BANK INC." << endl;
    save();
    saveToAcc();
    withdrawReceipt();                                                     // will display balance before exit
    system("pause");
}

void User::checkBal(){                                             // Function for displaying remaining balance for savings
    retrieveAcc();
    cout <<"\nHi!, "<< acc.inf.name << endl;
    cout << " \nCURRENT BALANCE: " << acc.inf.savings << endl;
    system("pause");
}

void User::deposit(){                                              //Function for money deposit                                               // variable for user's amount input
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Please enter the amount you want to deposit: ";       // will ask user for amount of deposit
    getline(cin, input);
    if(validate(1))
        return;
    acc.inf.savings = acc.inf.savings + stof(input);               // If money in savings will add up
    UREC *pointer = locate(acc.inf.accountNumber);
    pointer->inf.savings = acc.inf.savings;
    cout << "DEPOSIT SUCCESSFUL!" << endl;                         // User can proceed
    save();
    saveToAcc();                                                  
    depositReceipt();                                               // will display remaining balance before exit
    system("pause");
}



void User::fundTransfer(){                                         // Function for fund transfer, user is sender
    FUND:                                   
    retrieveAcc();
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Please enter the recipient's account number: ";       // will ask user for the recipients' account number
    getline(cin, input);
    if(validate(1))
        goto FUND;
    if(stoi(input) == acc.inf.accountNumber ){                // Just to make sure user won't send money to itself
        cout << "You can't send money to yourself" << endl;
        goto FUND;
    }

    UREC *point = locate(stoi(input));                        // will locate the account number that user input
    if(point == NULL){                                             // if null
        cout << "\e[1;1H\e[2J" << endl;
        cout << "User not found!" << endl;                         // account not found 
        cout << "The user must need to register first!" << endl;   
        system("pause");
        goto FUND;                                          // will just call the function again
    }

    FUNDT:
    cout << "\e[1;1H\e[2J" << endl;
    cout << "You are transfering funds to an individual named: " << point->inf.name << endl;  //displays recipient's name
    cout << "With and account number of " << point->inf.accountNumber << endl;                //displays recipient's account number
    cout << "Do you still want to continue? [Y] yes or [N] no: ";
    getline(cin, buffer);

    if(validate(1)){
        goto FUNDT;
    }
    if(buffer == "y" || buffer == "Y"){
        FUNDA:
        cout << "Please enter the amount you want to transfer [1-" << acc.inf.savings << "]: ";  // displays user's savings
        getline(cin, input);
        if(validate(1)){
            goto FUNDA;
        }
        if(stof(input) > acc.inf.savings){                                                   // will check if the input amount of user is greater than his/her savings
            cout << "INSUFFICIENT SAVINGS!" << endl;
            system("pause");
            goto FUNDA;
        }
        if(stof(input) < 100){
            cout << "Fund transfering must be a minimum of 100 php"<<endl;                   // fund transfering minimum of 100 pesos
            goto FUNDA;
        }

        if(stof(input) < 1){                                                                 // will check if the amount is valid/invalid
            cout << "INVALID AMOUNT!" << endl;
            system("pause");
            goto FUNDA;
        }

        acc.inf.savings = acc.inf.savings - stof(input);                                    // if true, the savings of user's account will decrease
        UREC *p = locate(acc.inf.accountNumber);
        p->inf.savings = acc.inf.savings;
        point->inf.savings = point->inf.savings + stof(input);                              // the recipient's savings account will increase
        cout << "\e[1;1H\e[2J" << endl;
        cout << "THANK YOU FOR TRUSTING STUDENT BANK INC." << endl;
        cout << "Fund transfered successfully!" << endl;
        decryptStandard("../records.txt.cpt", mainKey);
        save();
        saveToAcc();                                    // fund transfer successfully
        fundTransferReceipt(point);                                                                          // wil display remaining balance before exit
        system("pause");
        return;
    }

    return;


}

void User::changePin(){                                          // Function for changing pin
    CPIN:                           // variables used
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Change Pin..." << endl;
    cout << "Please enter your current pin: ";                   // asks for user's old pin
    input = asteriskPass();                                     // asterisk password
    if(validate(1)){
        goto CPIN;
    }
    if(sha256(input) != acc.inf.pincode){                       //will check if input pin does not match to system pin
        cout << "PIN does not match" << endl; 
        system("pause");
        goto CPIN;
    }else{
        cout << "Please enter your new pin: ";                  // if true, prompt user to new pin
        buffer = asteriskPass();                           
        if(!(buffer.length() == 6 || buffer.length() == 4)){       // new pin must be 4 or 6-digit
            cout << "Pincode must only be a 4 or 6 digit number!" << endl; 
            goto CPIN;
        }
        if(sha256(input)==buffer){                              // will check if user puts old pin 
            cout <<"Please don't use your old pin"<<endl;      // user can't use its old pin
            system("pause");
            goto CPIN;
        }
        cout << "Please re-enter in your new pin: ";          // if true, user can re-enter its new pin
        input = asteriskPass();
        if(buffer != input){                                   // will check if the new pin and reenter new pin does not match
            cout << "PIN does not match" << endl;
            system("pause");
        }else{

            acc.inf.pincode = sha256(buffer);   // if true, then the re-enter pin will be saved
            decryptStandard(CARD_PATH_ENCRYPTION, userKey);
            encryptStandard(CARD_PATH, buffer);
            userKey = buffer;
            UREC *p = locate(acc.inf.accountNumber);
            p->inf.pincode = acc.inf.pincode;
            cout << "PIN changed sucessfully!" << endl;
            buffer = "";
            save();
            saveToAcc();
            
        }
    }
}


void User::accountMenu(){
    cout << "\e[1;1H\e[2J" << endl;
    cout << "Welcome to Student Banks Inc." << endl;

    
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
                    
                }
                break;
            }
        }

    }
}
