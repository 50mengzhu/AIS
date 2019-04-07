#include "process.h"
#include "../ShipInfo/readDB.hpp"
#pragma comment(lib, "opencv_world341d.lib")
#pragma comment(lib, "opencv_world341.lib")

// 加上用户输入的经度和纬度，时间段
// 定义拥堵的条件量化计算，看参考文献
// 实验分析，对比试验（不同区域和不同的时间段）
// 预测
void Process::polyfit(Linklist* list, int n, cv::Mat& A)
{
    cv::Mat X = cv::Mat::zeros(n + 1, n + 1, CV_64FC1);

    Linklist* list_x = list;
    Linklist* list_y = list;
    Node* head = list -> get_head();

    std::cout << __LINE__ << "\t" << __FUNCTION__ << std::endl;

    for (int i = 0; i < n + 1; ++ i)
    {
        for (int j = 0; j < n + 1; ++ j)
        {
            while (list_x -> get_head() != nullptr)
            {
                double x = list_x -> get_head() -> get_position().get_longitude();
                X.at<double>(i, j) = X.at<double>(i, j) + std::pow(x, i + j);
                list_x -> set_head(list_x -> get_head() -> get_next());
            }
            list_x -> set_head(head);
        }
    }

    list_y -> set_head(head);
    cv::Mat Y = cv::Mat::zeros(n + 1, 1, CV_64FC1);
    for (int i = 0; i < n + 1; ++ i)
    {
        while (list_y -> get_head() != nullptr)
        {
            Position position = list_y -> get_head() -> get_position();
            double y = position.get_latitude();
            double x = position.get_longitude();
            Y.at<double>(i, 0) = Y.at<double>(i, 0) + std::pow(x, i) * y;
            list_y -> set_head(list_y -> get_head() -> get_next());
        }
        list_y -> set_head(head);
    }

    list -> set_head(head);
    A = cv::Mat::zeros(n + 1, 1, CV_64FC1);

    cv::solve(X, Y, A, cv::DECOMP_LU);

    return;
}



double Process::cal_distance(double longitude_1, double latitude_1, double longitude_2, double latitude_2)
{
    double factor_1 = sin(latitude_1) * sin(latitude_2);
    double factor_2 = cos(latitude_1) * cos(latitude_2) * cos(longitude_1 - longitude_2);

    double distance = EARTH_RADIUS * acos(factor_1 + factor_2); 

    return distance;
}

double Process::avg_cong_density(Linklist* list, double& denominator)
{
    Linklist* temp_list = list;

    double molecule = 0.0;
    denominator = 0.0;
    std::set<std::string> MMSI_set;

    while (temp_list -> get_head() != nullptr)
    {
        std::string MMSI = temp_list -> get_head() -> get_position().get_MMSI();
        if (MMSI_set.count(MMSI) > 0)
        {
            temp_list -> set_head(temp_list -> get_head() -> get_next());
            continue;
        }
        MMSI_set.insert(MMSI);
        int length = ReadDB::get_ship_length(MMSI);

        double coe = ReadDB::std_ship_coe(length);

        molecule += (coe / length);
        denominator += coe;
    }

    return (1 / FIELD_LONG_AXIS_COE) * molecule / denominator;
}

double Process::real_cong_density(double denominator)
{
    double distance = cal_distance(USER_LONGITUDE_LOW, USER_LATITUDE_LOW, USER_LONGITUDE_HIRH, USER_LATITUDE_HIGH);

    return denominator / distance;
}