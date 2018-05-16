#pragma once
#include<vector>
#include<opencv2/opencv.hpp>
#include<algorithm>
#include<iterator>

class CC {
private:
	const cv::Mat img;
	const size_t total;
	std::vector<bool> marked;
	size_t count = 0;
	std::vector<int> id;
	std::vector<size_t> size;
	std::vector<std::vector<cv::Point>> components;


public:
	CC(const cv::Mat &src):img(src),total(img.rows*img.cols),marked(total,false),id(total,-1) {
		for (size_t y = 0; y != img.rows; ++y) {
			for (size_t x = 0; x != img.cols; ++x) {
				if (!isMarked(y,x)) {
					dfs(y, x);
					++count;
				}
			}
		}
		
		size_t nBlocks =*std::max_element(id.begin(), id.end())+1;
		size.resize(nBlocks, 0);
		components.resize(nBlocks);
		for (size_t y = 0; y != img.rows; ++y) {
			for (size_t x = 0; x != img.cols; ++x) {
				int idNum = id[y*img.cols + x];
				if (idNum < 0 ) continue;
				++size.at(idNum);
				components.at(idNum).push_back(cv::Point(y, x));
			}
		}
	}

	size_t nComponents() {
		return id.size();
	}

	size_t nComponents(size_t sz) {
		return std::count_if(components.begin(), components.end(), [=](const std::vector<cv::Point> &pv) {return pv.size() >= sz; });
	}

	std::vector<std::vector<cv::Point>> findComponents(size_t area) {
		std::vector<std::vector<cv::Point>> ret;
		std::copy_if(components.begin(), components.end(), std::back_inserter(ret), [=](const std::vector<cv::Point> &pv) {return pv.size() >= area; });
		return ret;
	}

private:
	bool isMarked(size_t y,size_t x) {
		size_t pos = y*img.cols + x;
		return marked[pos] || (img.at<unsigned char>(y, x) == 0);
	}

	void dfs(size_t y, size_t x) {
		size_t pos = y*img.cols + x;
		marked[pos] = true;
		id[pos] = count;
		for (size_t row = y - 1; row <= y + 1; ++row) {
			if (row >= img.rows) continue;
			for (size_t col = x - 1; col <= x + 1; ++col) {
				if (col >= img.cols) continue;
				if (!isMarked(y, x)) {
					dfs(row, col);
				}

			}
		}
	}



};