#include"cellSegment.h"
#include<array>
#include<algorithm>
using cv::Mat;
using std::array;
using std::for_each;
using std::distance;
using std::lower_bound;
using cv::Mat_;
using cv::Vec2b;
using std::max;
using std::min;
using cv::saturate_cast;

void imadjust(const Mat &src, Mat &dst, const int saturate, const Vec2b outRange) {
	CV_Assert(src.type()== CV_8U);
	CV_Assert(saturate >= 0);

	dst.create(src.size(), src.type());
	
	array<size_t, 256> hist{};
	for_each(src.begin<unsigned char>(), src.end<unsigned char>(), [&hist](unsigned char val) {++hist[val]; });

	for (size_t i = 1; i != hist.size(); ++i) {
		hist[i] += hist[i - 1];
	}

	size_t total = dst.rows*dst.cols;
	size_t lowBound = total*saturate / 100;
	size_t uppBound = total - lowBound;
	cv::Vec2i inRange;
	inRange[0] = static_cast<int>(distance(hist.begin(), lower_bound(hist.begin(), hist.end(), lowBound)));
	inRange[1]=  static_cast<int>(distance(hist.begin(), lower_bound(hist.begin(), hist.end(), uppBound)));
	float scale = static_cast<float>(outRange[1] - outRange[0]) / (inRange[1] - inRange[0]);
	Mat_<unsigned char>::const_iterator it = src.begin<unsigned char>();
	Mat_<unsigned char>::iterator it2 = dst.begin<unsigned char>();
	for (; it2 != dst.end<unsigned char>(); ++it,++it2) {
		int vs = max(static_cast<int>(*it) - inRange[0], 0);
		int vd = min(static_cast<int>(vs*scale + outRange[0]), static_cast<int>(outRange[1]));
		*it2 = saturate_cast<unsigned char>(vd);
	}
}