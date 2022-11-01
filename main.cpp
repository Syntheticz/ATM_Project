#include "header/functions.h"

int main(){
 fileHandling fh;
 User us;
 us.setHead();
 fh.retrieve();
 while(1){
    us.menu();
 }
}