#include <mysql.h>
#include <iostream>

#include "../Config/DBconfig.h"

class ReadDB
{
public:
    static int get_ship_length(std::string MMSI);
    static double std_ship_coe(int length);
};


