#include"cellSegment.h"
using cv::Mat;

void findRegionalMax(const Mat &src, Mat &dst) {
	dst.create(src.size(), CV_8U);
	for (size_t y = 1; y != src.rows - 1; ++y) {
		for (size_t x = 1; x != src.cols - 1; ++x) {
			if (src.at<float>(y, x) < src.at<float>(y - 1, x - 1) ||
				src.at<float>(y, x) < src.at<float>(y - 1, x) ||
				src.at<float>(y, x) < src.at<float>(y - 1, x + 1) ||
				src.at<float>(y, x) < src.at<float>(y, x - 1) ||
				src.at<float>(y, x) < src.at<float>(y, x + 1) ||
				src.at<float>(y, x) < src.at<float>(y + 1, x - 1) ||
				src.at<float>(y, x) < src.at<float>(y + 1, x) ||
				src.at<float>(y, x) < src.at<float>(y + 1, x + 1)
				) {
				dst.at<unsigned char>(y, x) = 0;
			}
			else {
				dst.at<unsigned char>(y, x) = 255;
			}
		}
	}
}
