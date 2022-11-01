
#include "dataStructure.h"
class fileHandling : protected User{
    private:
    string path;
    
    public:
    void save();
    void retrieve();
    void retrieveAcc();
    void saveToAcc();
};

void fileHandling::save(){
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

void fileHandling::saveToAcc(){
    fstream fp;
    UREC pointer = acc;
    fp.open(path, ios::out);
    if(!fp){
        cout<<" Error while creating the file ";     
    }else{  
        while(!(fp.eof())){
            fp << pointer.inf.name << "\n" << pointer.inf.accountNumber << " " << pointer.inf.pincode << " " << pointer.inf.birthDay << " " << pointer.inf.savings << endl;    
        }
    }
        fp.close();
}


void fileHandling::retrieveAcc(){
    fstream fp;

    fp.open(path, ios::in);
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
}

void fileHandling::retrieve(){
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
                    add(rec, getHead());
                }else{
                    break;
                }
               

            }
            fp.close();

        }
    }
}