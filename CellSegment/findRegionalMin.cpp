#include"cellSegment.h"
using cv::Mat;

void findRegionalMin(const Mat &src, Mat &dst) {
	Mat med;
	imcomplement(src, med);
	findRegionalMax(med, dst);
}