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
			image.Set(y, x, color);
		}
		else
		{
			image.Set(x, y, color);
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
	Frame t_frame(FRAME_WIDTH, FRAME_HEIGHT);
	Model t_model("head.obj");

	for (int i = 0; i < t_model.FaceSize(); i++) {
		std::vector<int> face = t_model.Face(i);
		for (int j = 0; j < 3; j++) {
			Vec3f v0 = t_model.Vert(face[j]);
			Vec3f v1 = t_model.Vert(face[(j + 1) % 3]);
			int x0 = (v0[0] + 1.) * (FRAME_WIDTH - 1) / 2.;
			int y0 = (v0[1] + 1.) * (FRAME_HEIGHT - 1) / 2.;
			int x1 = (v1[0] + 1.) * (FRAME_WIDTH - 1) / 2.;
			int y1 = (v1[1] + 1.) * (FRAME_HEIGHT - 1) / 2.;
	
			line(x0, y0, x1, y1, t_frame, COLOR_WHITE);
		}
	}

	
	cv::imshow("test", t_frame.GetImage());
	cv::waitKey(0);
	return 0;
}