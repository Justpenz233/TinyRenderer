#include "Flame.h"
#include <iostream>
#include <opencv2/core/core.hpp>
using namespace cv;

Flame::~Flame()
{
	image_.release();
}

Flame::Flame(int w, int h)
{
	if (!image_.empty())
		return;
	wide_ = w;
	height_ = h;
	image_ = Mat::zeros(w, h, CV_8UC3);
}

void Flame::set(Point2i& p, Scalar& color)
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

void Flame::set(Point2i p, Scalar color)
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

Mat& Flame::get_image()
{
	return image_;
}
