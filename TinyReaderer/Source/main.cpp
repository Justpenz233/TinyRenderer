#include "Engine/CoreMinimal.h"
using namespace cv;

// Bresenham¡¯s Line Drawing 
void line(int x0, int y0, int x1, int y1, Frame& image, Scalar color) {
	bool flag = 0;
	if(abs(x0 - x1) < abs(y0 - y1))
	{
		flag = 1;
		swap(x0, y0);
		swap(x1, y1);
	}
	if(x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}
	int dy = y1 - y0;
	int dx = x1 - x0;
	float t = 2 * abs(dy);
	int y = y0;
	float del = 0;
	for(int x = x0; x <= x1;x ++)
	{
		if(flag)
		{
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}
		del += t;
		if(del > dx)
		{
			y += y0 < y1 ? 1 : -1;
			del -= dx * 2;
		}
	}
}


int main()
{
	Frame t_frame(500, 500);

	line(0, 0, 499, 30, t_frame,COLOR_RED);
	cv::imshow("test", t_frame.get_image());
	cv::waitKey(0);
	return 0;
}