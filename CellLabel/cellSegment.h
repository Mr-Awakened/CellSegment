#pragma once
#include<opencv2/opencv.hpp>
#include<vector>

void imadjust(const cv::Mat &src, cv::Mat &dst, const int saturate = 1, const cv::Vec2b outRange = cv::Vec2b(0, 255));
void bwareaopen(const cv::Mat &src, cv::Mat &dst, size_t area);
size_t colorComponent(const cv::Mat &src, cv::Mat &dst);
size_t cellCount(const cv::Mat &src,cv::Mat &dst,cv::Size openSize, cv::Size erodeSize, cv::Size dilateSize,size_t areaThreshold);

