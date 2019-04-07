#include "../ReadCSV/ReadCSV.hpp"
#include <ctime>


int main(int argv, char* argc[])
{
    // std::string filename = argc[1];
	std::string filename("../Data/position.csv");
    CSVReader reader(filename);

    clock_t start, finish;
    double total_time;

    start = clock();
    Linklist* list = reader.readData();
    finish = clock();

    list -> traverse();

    total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    // std::cout << data_list.size() << std::endl;
    std::cout << list -> size() << std::endl;
    std::cout << "cost about " << total_time << "s!\n" << std::endl;

    auto MMSI = reader.Classify_By_MMSI();


    std::cout << "----------" << std::endl;
    int count = 0;
    for (auto iter = MMSI.begin(); iter != MMSI.end(); ++ iter)
    {
        std::cout << iter -> first << std::endl;
        ++ count;
    }
        
    std::cout << "*********" << std::endl;
    std::cout << " count : " << count << std::endl;

    std::cout << reader.findMax(LONGITUDE) << std::endl;
    std::cout << reader.findMin(LONGITUDE) << std::endl;
    std::cout << reader.findMax(LATITUDE) << std::endl;
    std::cout << reader.findMin(LATITUDE) << std::endl;

    return 0;
}

// int main()
// {
//     std::string str = "姓名,性别,年龄,学分";

//     std::vector<std::string> vstr = split(str, ",");

//     for (std::string str_ : vstr)
//     {
//         std::cout << str_ << ", ";
//     }

//     std::cout << std::endl;

//     return 0;
// }


// vstr split(string str, string deli)
// {
//     vstr result;
//     if (str.size() == 0)
//     {
//         return result;
//     }

//     int i = 0, j = i;
    

//     while (i < str.size())
//     {
//         while (i < str.size() && str[i] != deli[0])
//             ++ i;
        
//         // 判断是否含有分隔符
//         if (str.substr(i, deli.size()) == deli)
//         {
//             result.push_back(str.substr(j, i - j));
//             i += deli.size();
//             j = i;
//             continue;
//         }
        
//         ++ i;
//     }

//     result.push_back(str.substr(j, i - j));

//     return result;
// }
