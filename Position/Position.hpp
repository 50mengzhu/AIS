#include "Position.h"

double Position::get_longitude()
{
    return Longitude;
}

double Position::get_latitude()
{
    return Latitude;
}

std::string Position::get_MMSI()const
{
    return MMSI;
}