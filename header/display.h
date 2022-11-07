#include "functions.h"


void User::withdrawReceipt(){
    system("cls");
    string uuid = get_uuid();
    tm* tm = setTime();
    cout<<"|*******************************************************|\n";
    cout<<"|                   STUDENT BANK INC.                   |\n";
    cout<<"|                    Ermita, Manila                     |\n";
    cout<<"|                   WITHDRAWAL RECEIPT                  |\n";
    cout<<"|=======================================================|\n";
    cout<<"|   Date: "<<__DATE__ <<"        Time:  "<< tm->tm_hour<<":"<< tm->tm_min<<":"<<tm->tm_sec<<"\t\t|"<<endl;  
    cout<<"|   Location: TUP - MANILA   Terminal ID: "<<uuid<<"         |"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|=======================================================|\n";
    cout<<"|                                                       |\n";
    cout<<"|   Receipt No:   " << uuid <<"\t\t\t\t\t|"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|   Account number: " << acc.inf.accountNumber<< "\t\t\t\t|\n";
    cout<<"|   Account name:  " << acc.inf.name <<"\t\t\t\t|\n";
    cout<<"|   Withdrawn Amount: "<< input << " PHP\t\t\t\t|\n";
    cout<<"|   Remaining Balance: " << acc.inf.savings <<"\t\t\t\t|\n";
    cout<<"|                                                       |\n";
    cout<<"|      ===========================================      |\n";
    cout<<"|        THANK YOU FOR TRUSTING STUDENT BANK INC.       |\n";
    cout<<"|         YOUR MONEY WILL ALWAYS BE SAFE ON US!         |\n";
    cout<<"|                                                       |\n";
    cout<<"|             \"money is not everything                  |\n";
    cout<<"|             but everyone needs money\"                 |\n";
    cout<<"|             ============================              |\n";
    cout<<"|                                                       |\n";
    cout<<"|*******************************************************|\n";


}
void User::depositReceipt(){
    system("cls");
    string uuid = get_uuid();
    tm* tm = setTime();
    cout<<"|*******************************************************|\n";
    cout<<"|                   STUDENT BANK INC.                   |\n";
    cout<<"|                    Ermita, Manila                     |\n";
    cout<<"|                    DEPOSIT RECEIPT                    |\n";
    cout<<"|=======================================================|\n";
    cout<<"|   Date: "<<__DATE__ <<"        Time:  "<< tm->tm_hour<<":"<< tm->tm_min<<":"<<tm->tm_sec<<"\t\t|"<<endl;  
    cout<<"|   Location: TUP - MANILA   Terminal ID: "<<uuid<<"         |"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|=======================================================|\n";
    cout<<"|                                                       |\n";
    cout<<"|   Receipt No:   " << uuid <<"\t\t\t\t\t|"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|   Account number: " << acc.inf.accountNumber<< "\t\t\t\t|\n";
    cout<<"|   Account name:  " << acc.inf.name <<"\t\t\t\t|\n";
    cout<<"|   Deposited Amount: "<< input << " PHP\t\t\t\t|\n";
    cout<<"|   Current Balance: " << acc.inf.savings <<"\t\t\t\t|\n";
    cout<<"|                                                       |\n";
    cout<<"|      ===========================================      |\n";
    cout<<"|        THANK YOU FOR TRUSTING STUDENT BANK INC.       |\n";
    cout<<"|         YOUR MONEY WILL ALWAYS BE SAFE ON US!         |\n";
    cout<<"|                                                       |\n";
    cout<<"|             \"money is not everything                  |\n";
    cout<<"|             but everyone needs money\"                 |\n";
    cout<<"|             ============================              |\n";
    cout<<"|                                                       |\n";
    cout<<"|*******************************************************|\n";


}
void User::fundTransferReceipt(UREC *point){
    string uuid = get_uuid();
    tm* tm = setTime();
    cout<<"|*******************************************************|\n";
    cout<<"|                   STUDENT BANK INC.                   |\n";
    cout<<"|                    Ermita, Manila                     |\n";
    cout<<"|                 FUND TRANSFER RECEIPT                 |\n";
    cout<<"|=======================================================|\n";
    cout<<"|   Date: "<<__DATE__ <<"    Time:  "<< tm->tm_hour<<":"<< tm->tm_min<<":"<<tm->tm_sec<<"\t\t|"<<endl;  
    cout<<"|   Location: TUP - MANILA   Terminal ID: "<<uuid<<"         |"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|=======================================================|\n";
    cout<<"|                                                       |\n";
    cout<<"|   Receipt No:   "<< uuid <<"\t\t\t\t\t|"<<endl;
    cout<<"|                                                       |\n";
    cout<<"|   Recipent Account number: " << point->inf.accountNumber<< "\t\t\t|\n";
    cout<<"|   Senter Account number: " << acc.inf.accountNumber<< "\t\t\t|\n";
    cout<<"|   Sender name:  " << acc.inf.name <<"\t\t\t\t|\n";
    cout<<"|   Recipent name:  " << point->inf.name <<"\t\t\t\t|\n";
    cout<<"|   Sent Amount: "<< input << " PHP\t\t\t\t|\n";
    cout<<"|   Current Balance: " << acc.inf.savings <<"\t\t\t\t|\n";
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