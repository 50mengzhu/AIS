#include <fstream>
#include <cmath>
#include <regex>
#include "ReadCSV.h"

CSVReader::CSVReader(std::string filename, std::string deli = ","):filename(filename), delimeter(deli), average_SOG(0){}

/***
 * compare two double nums
 * if num1 >= num2 return true
 * else return false
 *  ***/
bool CSVReader::compare_double(double num1, double num2)
{
    double e = 1E-6;

    if (num1 > num2 && fabs(num1 - num2) > e)
        return true;
    if (num1 < num2 && fabs(num1 - num2) > e)
        return false;
    
    return false;
}

std::vector<std::vector<std::string> > CSVReader::getData()
{
    std::ifstream file(filename);

    std::vector<std::vector<std::string> > data_list;

    std::string line = "";

    while (getline(file, line))
    {
        std::vector<std::string> vec = split(line, delimeter);

        data_list.push_back(vec);
    }
    
    file.close();

    return data_list;
}


std::map<std::string, std::vector<Position> > CSVReader::Classify_By_MMSI()
{
    return MMSI_Classify;
}

std::map<std::string, Linklist* > CSVReader::Classify_By_MMSI_List()
{
    return MMSI_Classify_List;
}


Linklist* CSVReader::readData()
{
    std::ifstream file(filename);

    Linklist* list = new Linklist();
    Node* node = new Node();
    std::string last_line;

    std::string line = "";
    Linklist* list_MMSI;

    double min_longitude = MAX_LONGITUDE;
    double max_longitude = MIN_LONGITUDE;
    double min_latitude  = MAX_LATITUDE;
    double max_latitude  = MIN_LATITUDE;

    std::set<std::string> MMSI_set;
    int count = 1;

    // std::regex reg("\"(.*)\"");

    int key = 0;

    while (getline(file, line))
    {   
        // 跳过读第一行的错误行为
        if (key == 0)
        {
            ++ key;
            continue;
        }

        std::vector<std::string> vec = split(line, delimeter);

        // MMSI, SOG, Longitude, Latitude, COG, Year, Month, Day, Hour, Minute, Second
        // 他们分别在ais_data.csv里面这个分隔符号的（以0开始计数）第3、6、8、9、10、15、16、17、18、19、20位处
        int index_array[] = {3, 6, 8, 9, 10, 15, 16, 17, 18, 19, 20};

        if (!vec.empty())
        {
            
            std::vector<std::string> param;
            double longitude, latitude, SOG;
            int year, month, day, hour, minute;

            // 这仅仅针对于我的测试数据中的每一个元素都被一对引号包围住而导致的情况
            // std::smatch match;
            // for (int i = 0; i < sizeof(index_array) / sizeof(index_array[0]); ++ i)
            // {
            //     regex_match(vec[index_array[i]], match, reg);
            //     param.push_back(match.str(1));
            // }

            for (int i = 0; i < sizeof(index_array) / sizeof(index_array[0]); ++ i)
            {
                param.push_back(vec[index_array[i]]);
            }

            SOG       = atof(param[1].c_str());
            longitude = atof(param[2].c_str());
            latitude  = atof(param[3].c_str());
            year      = atoi(param[5].c_str());
            month     = atoi(param[6].c_str());
            day       = atoi(param[7].c_str());
            hour      = atoi(param[8].c_str());
            minute    = atoi(param[9].c_str());
            
            if (longitude > USER_LONGITUDE_HIRH || longitude < USER_LONGITUDE_LOW)
                continue;

            if (latitude > USER_LATITUDE_HIGH || latitude < USER_LATITUDE_LOW)
                continue;
            
            // 对时间进行筛选
            if (USER_START_MINUTE + DURATION_TIME < 60)
            {
                if (!(hour == USER_START_HOUR && day == USER_START_DAY && month == USER_START_MONTH && year == USER_START_YEAR && minute >= USER_START_MINUTE && minute < USER_START_MINUTE + DURATION_TIME))
                {
                    continue;
                }
            }
            else
            {
                if (USER_START_HOUR + 1 < 24)
                {
                    if (!((day == USER_START_DAY) && (month == USER_START_MONTH) && (year == USER_START_YEAR)))
                        continue;
                    
                    bool condition_1 = (hour == USER_START_HOUR && minute >= USER_START_MINUTE && minute < 60);
                    bool condition_2 = (hour == USER_START_HOUR + 1 && minute >= 0 && minute < USER_START_MINUTE + DURATION_TIME - 60);
                    if (!(condition_1 || condition_2))
                        continue;
                }
                else
                {
                    if (USER_START_DAY + 1 <= get_day(USER_START_YEAR)[USER_START_MONTH])
                    {
                        if (!((month == USER_START_MONTH) && (year == USER_START_YEAR)))
                            continue;
                    
                        bool condition_1 = (day == USER_START_DAY && hour == USER_START_HOUR && minute >= USER_START_MINUTE && minute < 60);
                        bool condition_2 = (day == USER_START_DAY + 1 && hour == 0 && minute >= 0 && minute < USER_START_MINUTE + DURATION_TIME - 60);

                        if (!(condition_1 || condition_2))
                            continue;
                    }
                    else 
                    {
                        if (USER_START_MONTH + 1 <= 12)
                        {
                            if (year != USER_START_YEAR)
                                continue;
                            
                            bool condition_1 = (month == USER_START_MONTH && day == USER_START_DAY && hour == USER_START_HOUR && minute >= USER_START_MINUTE && minute < 60);
                            bool condition_2 = (month == USER_START_MONTH && day == 1 && hour == 0 && minute >= 0 && minute < USER_START_MINUTE + DURATION_TIME - 60);

                            if (!(condition_1 || condition_2))
                                continue;
                        }
                        else
                        {
                            bool condition_1 = (year == USER_START_YEAR && month == USER_START_MONTH && day == USER_START_DAY && hour == USER_START_HOUR && minute >= USER_START_MINUTE && minute < 60);
                            bool condition_2 = (year == USER_START_YEAR + 1 && month == 1 && day == 1 && hour == 0 && minute >= 0 && minute < USER_START_MINUTE + DURATION_TIME - 60);

                            if (!(condition_1 || condition_2))
                                continue;
                        }
                        
                    }
                }
            }

            // std::cout << year << "\t" << month << "\t" << day << "\t" << hour << "\t" << minute << "\t" << std::endl;
            min_longitude = compare_double(min_longitude, longitude) ? longitude : longitude;
            max_longitude = compare_double(max_longitude, longitude) ? max_longitude : longitude;
            min_latitude  = compare_double(min_latitude, latitude) ? latitude : min_latitude;
            max_latitude  = compare_double(max_latitude, latitude) ? max_latitude : latitude;

            average_SOG = ((count - 1) * average_SOG + SOG) / count;
            ++ count;

            // Position(std::string MMSI, double longitude, double latitude, 
            //             double SOG, double COG, int year, int month, int day, 
            //             int hour, int minute, int second);
            Position position(param[0], atof(param[2].c_str()), atof(param[3].c_str()), 
                            atof(param[1].c_str()), atof(param[4].c_str()), 
                            atoi(param[5].c_str()), atoi(param[6].c_str()),
                            atoi(param[7].c_str()), atoi(param[8].c_str()),
                            atoi(param[9].c_str()), atoi(param[10].c_str()));
            
            node = new Node(position);
            list -> push_back(node);

            /***
             * 不同船只的MMSI，存储在这个链表中
             * **/
            std::vector<Position> vec_MMSI;

            auto result = MMSI_set.insert(param[0]);
            if (result.second)
            {
                vec_MMSI.push_back(position);
                MMSI_Classify.insert(std::pair<std::string, std::vector<Position> >(param[0], vec_MMSI));
            }
            else 
            {
                vec_MMSI = MMSI_Classify[param[0]];
                vec_MMSI.push_back(position);
            }
        }     
    }

    max_position.push_back(max_longitude);
    max_position.push_back(max_latitude);
    min_position.push_back(min_longitude);
    min_position.push_back(min_latitude);


    file.close();

    return list;
}

double CSVReader::findMax(int type)
{
    return max_position[type];
}

double CSVReader::findMin(int type)
{
    return min_position[type];
}

double CSVReader::get_average_SOG()
{
    return average_SOG;
}


// https://thispointer.com/how-to-read-data-from-a-csv-file-in-c/
// https://www.cnblogs.com/dfcao/p/cpp-FAQ-split.html
