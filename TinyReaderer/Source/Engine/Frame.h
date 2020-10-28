#include <opencv2/core/core.hpp>


class Frame
{
public:
	~Frame();
	Frame();
	Frame(int w, int h);
	int get_wide() const { return wide_; }
	int get_height() const { return height_; }
	void set(cv::Point2i& p, cv::Scalar& color);
	void set(cv::Point2i p, cv::Scalar color);
	void set(int x, int y, cv::Scalar color);
	cv::Mat& get_image();
	
private:
	int wide_;
	int height_;
	cv::Mat image_;
};
