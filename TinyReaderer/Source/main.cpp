#include "Engine/CoreMinimal.h"

void line(int x0, int y0, int x1, int y1, Frame& image, Scalar color) {
	for (float t = 0.; t < 1.; t += .01) {
		int x = x0 + (x1 - x0) * t;
		int y = y0 + (y1 - y0) * t;
		image.set(Point2d(x,y), color);
	}
}


int main()
{
	Frame t_frame(500, 500);

	line(0, 0, 100, 100, t_frame,COLOR_RED);

	for(int i = 1;i <= 100;i ++)
	{
		for(int j = 200;j <= 400;j ++)
		{
			t_frame.set(i, j, COLOR_CYAN);
		}
	}
	
	for (int i = 200; i <= 300; i++)
	{
		for (int j = 0; j <= 200; j++)
		{
			if (j & 1)
				t_frame.set(i, j, COLOR_GREEN);
			else
				t_frame.set(i, j, COLOR_RED);
		}
	}
	cv::imshow("test", t_frame.get_image());
	cv::waitKey(0);
	return 0;
}