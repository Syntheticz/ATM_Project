#include <iostream>
#include <random>
#include <regex>
#include <fstream> 
#include <ctime>
#include <time.h>
#include <iomanip>
#include <sstream>

#include "filehandling.h"
#include "display.h"


using namespace std;

class Functions{
    protected:
        UREC *head;
        UREC *acc;
    public:
    void setHead();
};
