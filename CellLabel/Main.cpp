#include"cellSegment.h"
#include<chrono>
#include<iostream>
using cv::Mat;
using cv::imread;
using cv::cvtColor;
using cv::imshow;
using cv::waitKey;
using cv::Size;
using cv::addWeighted;

using std::cout;
using std::endl;

using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;

int main()
{
	Mat origin = imread("22.bmp");
	Mat gray;
	cvtColor(origin, gray, CV_RGB2GRAY);
	imshow("gray", gray);
	//cv::imwrite("gray.bmp", gray);


	Mat colored;

	time_point start = std::chrono::high_resolution_clock::now();
	size_t ncomps = cellCount(gray, colored, Size(19, 19), Size(9, 9), Size(5, 5), 25);
	time_point finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	cout << "ºÄÊ±" << elapsed.count() << "Ãë"<<endl;

	imshow("colored", colored);
	//cv::imwrite("colored.bmp", colored);


	Mat dst;
	Mat gray2;
	cvtColor(gray, gray2, cv::COLOR_GRAY2BGR);

	addWeighted(gray2, 0.4, colored, 0.6,0, dst);
	imshow("dst", dst);
	//cv::imwrite("dst.bmp", dst);
	cout <<ncomps <<"¸öÏ¸°û"<< endl;

	waitKey(0);

}
