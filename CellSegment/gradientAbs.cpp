#include"cellSegment.h"
using cv::Mat;
using cv::Sobel;
using cv::convertScaleAbs;
using cv::addWeighted;
using cv::sqrt;

void gradientAbs(const Mat &src, Mat &dst) {
	Mat gradx, grady;
	Sobel(src, gradx, CV_32F, 1, 0, 3, 1, 0, cv::BORDER_REPLICATE);
	Sobel(src, grady, CV_32F, 0, 1, 3, 1, 0, cv::BORDER_REPLICATE);

	//convertScaleAbs(gradx, gradx);
	//convertScaleAbs(grady, grady);

	sqrt(gradx.mul(gradx) + grady.mul(grady),dst);
}