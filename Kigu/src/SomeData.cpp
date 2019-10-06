#include "SomeData.h"

MyDataThing::MyDataThing(const std::string& string)
    : my_string(string)
{
}

void MyDataThing::output()
{
    std::cout << my_string << std::endl;
}
