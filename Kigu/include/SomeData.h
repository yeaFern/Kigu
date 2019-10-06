#pragma once

#include <string>
#include <iostream>

class MyDataThing
{
private:
    std::string my_string;
public:
    MyDataThing(const std::string& string);

    void output();
};
