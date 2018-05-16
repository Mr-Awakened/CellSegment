#include"cellSegment.h"
using cv::Mat;

void imcomplement(const Mat &src, Mat &dst) {
	dst.create(src.size(), src.type());
	
	for (size_t y = 1; y != src.rows - 1; ++y) {
		for (size_t x = 1; x != src.cols - 1; ++x) {
			dst.at<float>(y, x) = 1 - src.at<float>(y, x);
		}
	}
}