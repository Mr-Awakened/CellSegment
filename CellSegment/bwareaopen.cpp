#include"cellSegment.h"
using cv::Mat;
using cv::connectedComponentsWithStats;

void bwareaopen(const Mat &src, Mat &dst, size_t area) {
	Mat labels, stats, centroids;
	int ncomponents = connectedComponentsWithStats(src, labels, stats, centroids);
	dst.create(src.size(), src.type());
	for (size_t y = 0; y != dst.rows; ++y) {
		for (size_t x = 0; x != dst.cols; ++x) {
			int label = labels.at<int>(y, x);
			if (label!=0 && (stats.at<int>(label, cv::CC_STAT_AREA) >= area)) {
				dst.at<unsigned char>(y, x) = 255;
			}
			else {
				dst.at<unsigned char>(y, x) = 0;
			}
		}
	}
}