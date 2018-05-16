#include"cellSegment.h"
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
using cv::distanceTransform;
using cv::watershed;
using cv::normalize;



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
	Mat connected;
	bwareaopen(eroded, connected, 30);
	imshow("connected", connected);

	Mat dist;
	Mat connected2;
	cv::bitwise_not(connected, connected2);
	distanceTransform(connected2, dist, cv::DIST_L2, 3);
	//normalize(dist, dist, 0, 1, cv::NORM_MINMAX);
	dist.convertTo(dist, CV_8U);
	imshow("dist", dist);

	Mat dist2;

	cvtColor(dist, dist2, cv::COLOR_GRAY2BGR);
	Mat DL;
	connectedComponents(connected,DL);
	//DL.convertTo(DL, CV_32S);

	watershed(dist2, DL);

	Mat DL2;
	normalize(DL, DL2, 0, 255, cv::NORM_MINMAX);
	DL.convertTo(DL2, CV_8U);
	imshow("DL2", DL2);
	

	//normalize(DL, DL, 0, 255, cv::NORM_MINMAX);
	//DL.convertTo(DL, CV_8S);

	Mat bgm = Mat::zeros(DL.size(), CV_8U);
	for (size_t i = 0; i != bgm.rows; ++i) {
		for (size_t j = 0; j != bgm.cols; ++j) {
			if (DL.at<int>(i,j)== -1) {
				bgm.at<unsigned char>(i, j) = 255;
			}
		}
	}
	imshow("bgm", bgm);

	Mat combine = connected | bgm;
	imshow("combine", combine);

	waitKey(0);

}
