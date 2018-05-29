#include"cellSegment.h"
#include<vector>
#include<random>
using cv::Mat;
using cv::connectedComponents;
using cv::Vec3b;
using cv::Mat_;
using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;

size_t colorComponent(const Mat &src, Mat &dst) {	
	Mat labels;
	size_t nComponents = static_cast<size_t>(connectedComponents(src, labels));

	vector<Vec3b> colors;
	colors.reserve(nComponents);
	colors.push_back(Vec3b(0, 0, 0));
	
	uniform_int_distribution<unsigned> u(0, 255);
	default_random_engine e;
	for (size_t i = 1; i != nComponents; ++i) {
		colors.push_back(Vec3b(u(e),u(e),u(e)));
	}

	dst.create(src.size(), CV_8UC3);
	Mat_<Vec3b>::iterator it = dst.begin<Vec3b>();
	Mat_<int>::const_iterator it2 = labels.begin<int>();
	for (; it2 != labels.end<int>(); ++it, ++it2) {
		int label = *it2;
		*it = colors[label];
	}

	return nComponents;
}