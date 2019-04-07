#include "process.hpp"


int main()
{
    int N = 3;
    std::string filename("../Data/position_part_3.csv");
    CSVReader reader(filename);

    clock_t start, finish;
    double total_time;

    start = clock();
    Linklist* list = reader.readData();
    finish = clock();
    
    total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << list -> size() << std::endl;
    std::cout << "cost about " << total_time << "s!\n" << std::endl;

    cv::Mat A;
    Process::polyfit(list, N, A);

    cv::namedWindow("image");

    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);
    image.setTo(cv::Scalar(100, 0, 0));

    std::vector<cv::Point> points_fitted;

    double MAX_LON = reader.findMax(LONGITUDE) + 1;
    for (double x = reader.findMin(LONGITUDE) - 1; x < MAX_LON; x += 0.01)
    {
        double y = 0.0;

        int n = 0;
        while (n <= N)
        {
            y += A.at<double>(n, 0) * std::pow(x, n);
            ++ n;
        }

        points_fitted.push_back(cv::Point(x, y));
    }

	cv::polylines(image, points_fitted, false, cv::Scalar(0, 255, 255), 1, 8, 0);

	cv::imshow("image", image);

	cv::waitKey(10000);

	cv::destroyWindow("image");
}