#include "Frame.h"
#include <iostream>
#include <opencv2/core/core.hpp>
using namespace cv;

Frame::~Frame()
{
	image_.release();
}

Frame::Frame(int w, int h)
{
	if (!image_.empty())
		return;
	wide_ = w;
	height_ = h;
	image_ = Mat::zeros(w, h, CV_8UC3);
}

void Frame::set(Point2i& p, Scalar& color)
{
	if(image_.empty())
	{
		std::cout << "Image Empty";
		return;
	}
	image_.at<Vec3b>(p.x, p.y)[0] = color[0];
	image_.at<Vec3b>(p.x, p.y)[1] = color[1];
	image_.at<Vec3b>(p.x, p.y)[2] = color[2];
}

void Frame::set(Point2i p, Scalar color)
{
	if (image_.empty())
	{
		std::cout << "Image Empty";
		return;
	}
	image_.at<Vec3b>(p.x, p.y)[0] = color[0];
	image_.at<Vec3b>(p.x, p.y)[1] = color[1];
	image_.at<Vec3b>(p.x, p.y)[2] = color[2];
}

void Frame::set(int x, int y, Scalar color)
{
	if (image_.empty())
	{
		std::cout << "Image Empty";
		return;
	}
	image_.at<Vec3b>(x, y)[0] = color[0];
	image_.at<Vec3b>(x, y)[1] = color[1];
	image_.at<Vec3b>(x, y)[2] = color[2];
}

Mat& Frame::get_image()
{
	return image_;
}
