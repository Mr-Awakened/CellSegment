#include<vector>
#include<opencv2/opencv.hpp>
using std::vector;
using cv::Mat;
using cv::Point;

void vec2Mat(const vector<vector<Point>> &src, Mat &dst) {
	for (const vector<Point> &vec : src) {
		for (const Point& p : vec) {
			dst.at<unsigned char>(p.y, p.x) = 1;
		}
	}
}