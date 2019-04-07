#include <iostream>

#include "config.hpp"

int main(int argc,char* argv[])
{
    int year = 0;
    while (std::cin >> year)
    {
        std::cout << is_leap_year(year) << std::endl;

        int* Day = get_day(year);
        for (int i = 1; i < 13; ++ i)
        {
            std::cout << Day[i] << "\t";
        }

        std::cout << std::endl;
    }
    
    return 0;
}