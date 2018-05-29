#include"cellSegment.h"
using cv::Mat;
using cv::Size;
using cv::getStructuringElement;
using cv::morphologyEx;

size_t cellCount(const Mat &src, Mat &dst, Size openSize, Size erodeSize, Size dilateSize, size_t areaThreshold) {
	Mat openElement= getStructuringElement(cv::MORPH_ELLIPSE, openSize);
	Mat bg; 
	morphologyEx(src, bg, cv::MORPH_OPEN, openElement);

	Mat subtracted = src - bg;

	Mat stretched;
	imadjust(subtracted, stretched);

	Mat bw;
	threshold(stretched, bw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	Mat erodeElement= getStructuringElement(cv::MORPH_ELLIPSE, erodeSize);
	Mat eroded;
	morphologyEx(bw, eroded, cv::MORPH_ERODE, erodeElement);

	Mat connected;
	bwareaopen(eroded, connected, areaThreshold);

	Mat dilateElement = getStructuringElement(cv::MORPH_ELLIPSE, dilateSize);
	Mat dilated;
	morphologyEx(connected,dilated, cv::MORPH_DILATE, dilateElement);
	
	size_t nCells=colorComponent(dilated, dst);
	return nCells;
}
