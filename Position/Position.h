#include <string>

class Position
{
private:
    std::string MMSI;
    double      Longitude;
    double      Latitude;
    double      SOG; // speed
    double      COG; // oriented
    int         Year;
    int         Month;
    int         Day;
    int         Hour;
    int         Minute;
    int         Second;

public:
    Position();
    Position(std::string MMSI, double longitude, double latitude, 
        double SOG, double COG, int year, int month, int day, 
        int hour, int minute, int second);
    ~Position();
    std::string get_MMSI()const;
    double get_longitude();
    double get_latitude();
    double get_SOG()const;
    double get_COG()const;
    int get_year()const;
    int get_month()const;
    int get_day()const;
    int get_hour()const;
    int get_minute()const;
    int get_second()const;
};

