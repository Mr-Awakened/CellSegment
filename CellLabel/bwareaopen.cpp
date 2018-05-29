#include"cellSegment.h"
using cv::Mat;
using cv::Mat_;
using cv::connectedComponentsWithStats;

void bwareaopen(const Mat &src, Mat &dst, size_t area) {
	Mat labels, stats, centroids;
	int ncomponents = connectedComponentsWithStats(src, labels, stats, centroids);
	dst.create(src.size(), src.type());
	Mat_<unsigned char>::iterator it = dst.begin<unsigned char>();
	Mat_<int>::const_iterator it2 = labels.begin<int>();
	for (; it2 != labels.end<int>(); ++it, ++it2) {
		int label = *it2;
		if (label != 0 && (stats.at<int>(label, cv::CC_STAT_AREA) >= area)) {
			*it = 255;
		}
		else {
			*it = 0;
		}
	}
	
}