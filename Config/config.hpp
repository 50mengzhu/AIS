#include "config.h"

int* get_day(int year)
{
    int Day[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int* day = new int[14];
    for (int i = 0; i < 13; ++ i)
    {
        day[i] = Day[i];
    }

    if (is_leap_year(year))
    {   
        day[2] = 29;    
    }
    
    return day;
}

bool is_leap_year(int year)
{
    if (year % 100 != 0)
    {
        if (year % 4 == 0)
            return true;
        else   
            return false;
    }
    else  
    {
        if (year % 400 == 0)
        {
            return true;
        }
        else 
            return false;
    }

    return false;
}