#include <opencv2/core/core.hpp>
using namespace cv;

class Frame
{
public:
	~Frame();
	Frame();
	Frame(int w, int h);
	int get_wide() const { return wide_; }
	int get_height() const { return height_; }
	void set(Point2i& p, Scalar& color);
	void set(Point2i p, Scalar color);
	void set(int x, int y, Scalar color);
	Mat& get_image();
	
private:
	int wide_;
	int height_;
	Mat image_;
};
