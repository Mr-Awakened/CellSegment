#include"cellSegment.h"
#include"CC.h"
#include<opencv2/opencv.hpp> 
#include<iostream>
#include<vector>

using cv::Mat;
using cv::imread;
using cv::cvtColor;
using cv::imshow;
using cv::waitKey;
using cv::morphologyEx;
using cv::getStructuringElement;
using cv::Size;

using std::cout;
using cv::threshold;
using cv::connectedComponents;
using std::vector;
using cv::Point;


int main()
{
	Mat origin = imread("22.bmp");
	Mat gray;
	cvtColor(origin, gray, CV_RGB2GRAY);
	imshow("gray", gray);

	Mat element = getStructuringElement(cv::MORPH_ELLIPSE,Size(19,19));
	//cout << element;
	Mat bg;
	morphologyEx(gray, bg, cv::MORPH_OPEN,element);
	imshow("bg", bg);

	Mat subtracted = gray - bg;
	imshow("subtracted", subtracted);
	//cout << subtracted.type();

	Mat stretched;
	imadjust(subtracted, stretched);
	imshow("stretched", stretched);

	Mat bw;
	threshold(stretched, bw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	imshow("bw", bw);

	Mat element2 = getStructuringElement(cv::MORPH_ELLIPSE, Size(9, 9));
	Mat eroded;
	erode(bw, eroded, element2);
	imshow("eroded", eroded);

	//Mat connected;
	//connectedComponents(eroded, connected,8, CV_16U);
	//imshow("connected", connected);
	CC c(eroded);
	vector<vector<Point>> temp1 = c.findComponents(30);
	Mat temp2 = Mat::zeros(eroded.size(), eroded.type());
	vec2Mat(temp1, temp2);
	imshow("temp2", temp2);

	waitKey(0);

}
