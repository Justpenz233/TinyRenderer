#pragma once

#include <opencv2/core/core.hpp>
class Frame
{
public:
	~Frame();
	Frame(int w, int h);
	Frame();
	int GetWide() const { return wide_; }
	int GetHeight() const { return height_; }
	void Set(cv::Point2i& p, cv::Scalar& color);
	void Set(cv::Point2i p, cv::Scalar color);
	void Set(int x, int y, cv::Scalar color);
	cv::Scalar At(int x, int y);
	cv::Scalar At(const cv::Point2i& p);

	cv::Mat& GetImage();
	
private:
	int wide_;
	int height_;
	cv::Mat image_;
};