
#include <iostream>
#include "clsDate.h"

using namespace std;

int main()
{
    clsDate Date1;
    Date1.Print();

    clsDate Date2("7/10/2023");
    Date2.Print();

    clsDate Date3(1, 1, 2027);
    Date3.Print();

    clsDate Date4(250, 2022);
    Date4.Print();

    Date4.IncreaseDateByOneWeek();
    Date4.Print();

}
