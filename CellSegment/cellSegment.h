#pragma once
#include<opencv2/opencv.hpp>
#include<vector>

void imadjust(const cv::Mat &src, cv::Mat &dst, const int saturate = 1, const cv::Vec2b outRange = cv::Vec2b(0, 255));
void bwareaopen(const cv::Mat &src, cv::Mat &dst, size_t area);
void label(const cv::Mat &src, cv::Mat &dst);