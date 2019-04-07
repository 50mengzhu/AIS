#include "../ReadCSV/ReadCSV.hpp"
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <cmath>
#include <set>

#define EARTH_RADIUS 6378.1370

class Process
{
public:
    static void polyfit(std::vector<std::vector<std::string> >, int n, cv::Mat& A);

    static void polyfit(Linklist* , int n, cv::Mat& A);

    static double avg_cong_density(Linklist* list, double& denominator);

    static double real_cong_density(double denominator);

private:
    static double cal_distance(double longitude_1, double latitude_1, double longitude_2, double latitude_2);
};

