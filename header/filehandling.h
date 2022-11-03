#include "dataStructure.h"

void User::save(){
    decryptStandard("../records.txt.cpt");
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
    encryptOnClose();
}


void User::retrieve(){

    decryptOnOpen();
    fstream fp;
    INFO rec;
    fp.open("records.txt", ios::in);
    if(!fp){
        cout<<" Error while creating the file "; 
    }else{
        if(fp.is_open()){
            while(true){
                getline(fp, rec.name, '\n');
                fp >> rec.accountNumber >> rec.pincode >> rec.birthDay >> rec.savings;
                fp.ignore();
                if(!fp.eof()){
                    add(rec);
                }else{
                    break;
                }
               

            }
            fp.close();
            encryptStandard("../records.txt");
        }
    }
}

void User::saveToAcc(){
    fstream fp;
    UREC pointer = acc;
    
    decryptStandard("../record.txt.cpt");   //change path to removable storage
    fp.open("record.txt", ios::out);
    if(!fp){
        cout<<" Error while creating the file ";     
    }else{  
        while(!(fp.eof())){
            fp << pointer.inf.name << "\n" << pointer.inf.accountNumber << " " << pointer.inf.pincode << " " << pointer.inf.birthDay << " " << pointer.inf.savings << endl;    
        }
    }
        fp.close();
    encryptStandard("../record.txt");
}

void User::retrieveAcc(){
    fstream fp;
    decryptStandard("../record.txt.cpt");
    //change path to removable storage
    fp.open("record.txt", ios::in);
    if(!fp){
        cout<<" Error while creating the file "; 
    }else{
        if(fp.is_open()){
            while(!(fp.eof())){
                getline(fp, acc.inf.name, '\n');
                fp >> acc.inf.accountNumber >> acc.inf.pincode >> acc.inf.birthDay >> acc.inf.savings;
                fp.ignore();
            }
            fp.close();
        }
    }
    encryptStandard("../record.txt");
}


// Encryption method: AES (Advance Encryption Standard)
void User::encryptOnOpen(){
    fstream fp;
    fp.open("key.ink", ios::in);
    if(fp){return;}
    fp.close();
    do
    {
       fp.open("key.key", ios::in);
       if(!fp){
            cout << "Key not Found!" << endl;
       }
    } while (!fp);
    system("cd crypt && ccrypt -e ../records.txt -k ../key.key");
    if(fp.is_open()){
        while(!(fp.eof())){
            getline(fp, input);  
            setKey(input);
            fp.ignore();
        }
        input = sha256(input);
        fp.close();
    }
    fp.open("key.ink", ios::out);
    if(!fp){
        cout<<" Error while creating the file ";     
    }else{  
        fp << input << endl;    
    }
        fp.close();
}

void User::encryptOnClose(){
    fstream fp;
    string query = "cd crypt && ccrypt -e ../records.txt -K " + key;
    system(query.c_str());

    fp.open("key.key", ios::out);
    if(!fp){
        cout<<" Error while creating the file ";     
    }else{  
        fp << key << endl;    
    }
}



void User::encryptStandard(string path){
    string query = "cd crypt && ccrypt -e " + path + " -K " + key;
    cout << "Key: " << key << " testing: " << query << endl; system("pause");
    system(query.c_str());
    system("del key.key");
}

void User::decryptStandard(string path){
    if(validate(7)){cout << "Wrong Key!" << endl; system("pause"); return;}
    string query = "cd crypt && ccrypt -d " + path + " -K " + key;
    cout << "Key: " << key << " testing: " << query << endl; system("pause");
    system(query.c_str());
}



void User::decryptOnOpen(){
    fstream fp;
    do
    {
       fp.open("key.key", ios::in);
       if(!fp){
            cout << "Key not Found!" << endl;
       }
    } while (!fp);

    if(fp.is_open()){
        fp >> key;
        fp.ignore();
    }

    fp.close();
    system("cd crypt && ccrypt -d ../records.txt.cpt -k ../key.key");
    
}

