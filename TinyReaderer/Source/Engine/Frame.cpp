#include "Frame.h"
#include <iostream>
#include <opencv2/core/core.hpp>
using namespace cv;

Frame::~Frame()
{
	image_.release();
}

Frame::Frame(const int w, const int h)
{
	if (!image_.empty())
		return;
	wide_ = w;
	height_ = h;
	image_ = Mat::zeros(h, w, CV_8UC3);
}

void Frame::Set(Point2i& p, Scalar& color)
{
	if(image_.empty())
	{
		std::cout << "Image Empty";
		return;
	}
	image_.at<Vec3b>(height_ - 1 - p.y, p.x)[0] = color[0];
	image_.at<Vec3b>(height_ - 1 - p.y, p.x)[1] = color[1];
	image_.at<Vec3b>(height_ - 1 - p.y, p.x)[2] = color[2];
}

void Frame::Set(const Point2i p, Scalar color)
{
	if (image_.empty())
	{
		std::cout << "Image Empty";
		return;
	}
	image_.at<Vec3b>(height_ - 1 - p.y, p.x)[0] = color[0];
	image_.at<Vec3b>(height_ - 1 - p.y, p.x)[1] = color[1];
	image_.at<Vec3b>(height_ - 1 - p.y, p.x)[2] = color[2];
}

void Frame::Set(const int x, const int y, Scalar color)
{
	if (image_.empty())
	{
		std::cout << "Image Empty";
		return;
	}
	image_.at<Vec3b>(height_ - 1 - y, x)[0] = color[0];
	image_.at<Vec3b>(height_ - 1 - y, x)[1] = color[1];
	image_.at<Vec3b>(height_ - 1 - y, x)[2] = color[2];
}

cv::Scalar Frame::At(const int x, const int y)
{
	return image_.at<Scalar>(height_ - 1 - y, x);
}

cv::Scalar Frame::At(const cv::Point2i& p)
{
	return image_.at<Scalar>(height_ - 1 - p.y, p.x);
}

Mat& Frame::GetImage()
{
	return image_;
}
