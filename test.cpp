#include "Process/process.hpp"

int main()
{
    std::string filename("Data/position.csv");
    CSVReader reader(filename);

    Linklist* list = reader.readData();

    double average_speed = reader.get_average_SOG();

    double denominator = 0.0;

    double avg_cong_density = Process::avg_cong_density(list, denominator);
    double real_cong_density = Process::real_cong_density(denominator);

    std::cout << "avg_cong_density : " << avg_cong_density << std::endl;
    std::cout << "real_cong_density : " << real_cong_density << std::endl;

    std::cout << "average_speed : " << average_speed << std::endl;

    return 0;
}