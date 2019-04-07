#include "readDB.hpp"

int main()
{
    std::string server = "localhost";
    std::string user = "root";
    std::string pass = "";
    std::string dbName = "ais";
    std::string tabName = "ship_info";
    std::string MMSI = "636012797";

    
    int length = ReadDB::get_ship_length(server.c_str(), user.c_str(), pass.c_str(), dbName.c_str(), tabName.c_str(), MMSI);

    std::cout << length << std::endl;

    return 0;
}