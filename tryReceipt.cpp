 #include <iostream>
using namespace std;
// #include <random>
// #include <regex>
// #include <ctime>
// #include <time.h>
// #include <iomanip>
// #include <sstream>
// #include <fstream>

// #include "sha256.h"
// #include "header/functions.h"
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    static int terminalID = 0001;       // static because it exists until the end of the program once initialized

void withdrawReceipt(){

   

    cout<<"|*******************************************************|\n";
    cout<<"|                   STUDENT BANK INC.                   |\n";
    cout<<"|                    Ermita, Manila                     |\n";
    cout<<"|                   WITHDRAWAL RECEIPT                  |\n";
    cout<<"|=======================================================|\n";
    cout<<"|   Date: "<<__DATE__ <<"    Time:  "<< tm.tm_hour<<":"<< tm.tm_min<<":"<<tm.tm_sec<<"\t\t\t|"<<endl;  
    cout<<"|   Location: TUP - MANILA   Terminal ID: "<<terminalID<<"             |"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|=======================================================|\n";
    cout<<"|                                                       |\n";
    cout<<"|   Receipt No:   "<<  tm.tm_year + 1900<< tm.tm_mon + 1<< tm.tm_mday<< tm.tm_hour<< tm.tm_min<< tm.tm_sec<<"\t\t\t\t|"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|   Account number:                                     |\n";
    cout<<"|   Account name:                                       |\n";
    cout<<"|   Withdrawn Amount:  PHP                              |\n";
    cout<<"|   Remaining Balance:                                  |\n";
    cout<<"|                                                       |\n";
    cout<<"|      ===========================================      |\n";
    cout<<"|        THANK YOU FOR TRUSTING STUDENT BANK INC.       |\n";
    cout<<"|         YOUR MONEY WILL ALWAYS BE SAFE ON US!         |\n";
    cout<<"|                                                       |\n";
    cout<<"|             \"money is not everything                  |\n";
    cout<<"|             but everything needs money\"               |\n";
    cout<<"|             ============================              |\n";
    cout<<"|                                                       |\n";
    cout<<"|*******************************************************|\n";

    terminalID++; //increment terminal id

}
void depositReceipt(){
           
    cout<<"|*******************************************************|\n";
    cout<<"|                   STUDENT BANK INC.                   |\n";
    cout<<"|                    Ermita, Manila                     |\n";
    cout<<"|                    DEPOSIT RECEIPT                    |\n";
    cout<<"|=======================================================|\n";
    cout<<"|   Date: "<<__DATE__ <<"    Time:  "<< tm.tm_hour<<":"<< tm.tm_min<<":"<<tm.tm_sec<<"\t\t\t|"<<endl;  
    cout<<"|   Location: TUP - MANILA   Terminal ID: "<<terminalID<<"             |"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|=======================================================|\n";
    cout<<"|                                                       |\n";
    cout<<"|   Receipt No:   "<<  tm.tm_year + 1900<< tm.tm_mon + 1<< tm.tm_mday<< tm.tm_hour<< tm.tm_min<< tm.tm_sec<<"\t\t\t\t|"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|   Account number:                                     |\n";
    cout<<"|   Account name:                                       |\n";
    cout<<"|   Deposit Amount:  PHP                                |\n";
    cout<<"|   Current Balance:                                    |\n";
    cout<<"|                                                       |\n";
    cout<<"|      ===========================================      |\n";
    cout<<"|        THANK YOU FOR TRUSTING STUDENT BANK INC.       |\n";
    cout<<"|         YOUR MONEY WILL ALWAYS BE SAFE ON US!         |\n";
    cout<<"|                                                       |\n";
    cout<<"|             \"money is not everything                  |\n";
    cout<<"|             but everything needs money\"               |\n";
    cout<<"|             ============================              |\n";
    cout<<"|                                                       |\n";
    cout<<"|*******************************************************|\n";

    terminalID++; //increment terminal id  

}
void fundTransferReceipt(){
    cout<<"|*******************************************************|\n";
    cout<<"|                   STUDENT BANK INC.                   |\n";
    cout<<"|                    Ermita, Manila                     |\n";
    cout<<"|                 FUND TRANSFER RECEIPT                 |\n";
    cout<<"|=======================================================|\n";
    cout<<"|   Date: "<<__DATE__ <<"    Time:  "<< tm.tm_hour<<":"<< tm.tm_min<<":"<<tm.tm_sec<<"\t\t\t|"<<endl;  
    cout<<"|   Location: TUP - MANILA   Terminal ID: "<<terminalID<<"             |"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|=======================================================|\n";
    cout<<"|                                                       |\n";
    cout<<"|   Receipt No:   "<<  tm.tm_year + 1900<< tm.tm_mon + 1<< tm.tm_mday<< tm.tm_hour<< tm.tm_min<< tm.tm_sec<<"\t\t\t\t|"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|   Recipient's Account No:                             |\n";
    cout<<"|   Recepient's Name:                                   |\n";
    cout<<"|   Sender's Account No:                                |\n";
    cout<<"|   Sender's Name:                                      |\n";
    cout<<"|   Amount Transfered:  PHP                             |\n";
    cout<<"|   Current Balance:                                    |\n";
    cout<<"|                                                       |\n";
    cout<<"|      ===========================================      |\n";
    cout<<"|        THANK YOU FOR TRUSTING STUDENT BANK INC.       |\n";
    cout<<"|         YOUR MONEY WILL ALWAYS BE SAFE ON US!         |\n";
    cout<<"|                                                       |\n";
    cout<<"|             \"money is not everything                  |\n";
    cout<<"|             but everything needs money\"               |\n";
    cout<<"|             ============================              |\n";
    cout<<"|                                                       |\n";
    cout<<"|*******************************************************|\n";




}
int main(){
      withdrawReceipt();
      return 0;

}


