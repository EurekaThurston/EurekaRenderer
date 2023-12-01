#pragma once
#include <string>
#include <iostream>

inline void DividingLine()
{
    std::string line(20, '-');
    std::cout << line << std::endl;
}

inline void DividingStar()
{
    std::string line(80, '*');
    std::cout << line << std::endl;
}
