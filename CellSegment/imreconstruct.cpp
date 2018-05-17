#pragma warning(disable : 4996)
#include"cellSegment.h"
#include<algorithm>
using cv::Mat;
using cv::morphologyEx;
using cv::getStructuringElement;
using cv::Size;
using cv::min;
using std::equal;
using cv::countNonZero;
using cv::erode;

//void imreconstruct(const Mat& marker, const Mat& mask,Mat &dst)
//{
//	cv::min(marker, mask, dst);
//	dilate(dst, dst, Mat());
//	cv::min(dst, mask, dst);
//	Mat temp1 = Mat(marker.size(), CV_8UC1);
//	Mat temp2 = Mat(marker.size(), CV_8UC1);
//	do
//	{
//		dst.copyTo(temp1);
//		dilate(dst, dst, Mat());
//		cv::min(dst, mask, dst);
//		compare(temp1, dst, temp2, CV_CMP_NE);
//	} while (sum(temp2).val[0] != 0);
//	
//}

//void imreconstruct(const Mat& marker, const Mat& mask, Mat &dst)
//{
//	dst.create(marker.size(), marker.type());
//	Mat med = marker.clone();
//	Mat dilated;
//	bool eq;
//	//Mat element = getStructuringElement(cv::MORPH_RECT, Size(5, 5));
//	do {
//		med.copyTo(dst);
//		dilate(dst, dilated,Mat());
//		med = min(dilated, mask);
//		eq = equal(med.begin<unsigned char>(), med.end<unsigned char>(), mask.begin<unsigned char>());
//	} while (!eq);
//}

void imreconstruct(const Mat &g, const Mat &f, Mat& dest)
{
	Mat m0, m1, m;
	m1 = f;
	do {
		m0 = m1.clone();
		erode(m0, m, Mat());
		cv::max(g, m, m1);
	} while (countNonZero(m1 != m0) != 0);
	dest = m1.clone();
}


