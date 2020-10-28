#include <opencv2/core/core.hpp>
using namespace cv;

class Flame
{
public:
	~Flame();
	Flame();
	Flame(int w, int h);
	int get_wide() const { return wide_; }
	int get_height() const { return height_; }
	void set(Point2i& p, Scalar& color);
	void set(Point2i p, Scalar color);
	Mat& get_image();
	
private:
	int wide_;
	int height_;
	Mat image_;
};
