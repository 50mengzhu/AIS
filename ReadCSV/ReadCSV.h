#include "../Linklist/Linklist.hpp"
#include "../Util/Util.hpp"
#include "../Config/config.h"

static const double MIN_LATITUDE  = 0.0;
static const double MAX_LATITUDE  = 90.0;
static const double MIN_LONGITUDE = 0.0;
static const double MAX_LONGITUDE = 180.0;

#define LONGITUDE 0
#define LATITUDE  1

class CSVReader
{
private:
    std::string filename;
    std::string delimeter;
    std::vector<double> max_position;
    std::vector<double> min_position;
    std::map<std::string, Linklist* > MMSI_Classify_List;
    std::map<std::string, std::vector<Position> > MMSI_Classify;

    bool compare_double(double num1, double num2);
    
    double average_SOG;

public:
    CSVReader(std::string filename, std::string deli);

    std::vector<std::vector<std::string> > getData();

    Linklist* readData();

    std::map<std::string, Linklist* > Classify_By_MMSI_List();
    std::map<std::string, std::vector<Position> > Classify_By_MMSI(); 

    double findMin(int type);
    double findMax(int type);

    double get_average_SOG();
};
