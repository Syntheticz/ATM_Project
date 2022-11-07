#include <iostream>
#include <random>
#include <regex>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "sha256.h"
#include "header/display.h"

int main(){
   User us;
   us.setHead();
   us.retrieve();
   while(1){
      us.menu();
   }


}