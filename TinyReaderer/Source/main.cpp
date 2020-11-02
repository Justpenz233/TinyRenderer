#include "Engine/CoreMinimal.h"
#include "Engine/Model.h"

using namespace cv;

// Bresenham¡¯s Line Drawing 
void line(int x0, int y0, int x1, int y1, Frame& image, const Scalar& color) {
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

void line(const Vec2i& A, const Vec2i& B, Frame& image, const Scalar& color) {
	bool flag = 0;
	int x0 = A[0];
	int x1 = B[0];
	int y0 = A[1];
	int y1 = B[1];
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		flag = 1;
		swap(x0, y0);
		swap(x1, y1);
	}
	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}
	int dy = y1 - y0;
	int dx = x1 - x0;
	float t = 2 * abs(dy);
	int y = y0;
	float del = 0;
	for (int x = x0; x <= x1; x++)
	{
		if (flag)
		{
			image.Set(y, x, color);
		}
		else
		{
			image.Set(x, y, color);
		}
		del += t;
		if (del > dx)
		{
			y += y0 < y1 ? 1 : -1;
			del -= dx * 2;
		}
	}
}

Vec4i BoundingBox(const Vec2i& A, const Vec2i& B, const Vec2i& C)
{
	int XMin, XMax, YMin, YMax;

	XMin = min(min(A[0], B[0]), C[0]);
	YMin = min(min(A[1], B[1]), C[1]);
	XMax = max(max(A[0], B[0]), C[0]);
	YMax = max(max(A[1], B[1]), C[1]);

	return Vec4i(XMin, YMin, XMax, YMax);
}

bool PointInTriangle(const Vec2i& A, const Vec2i& B, const Vec2i& C, const Vec2i& P)
{
	Vec2i v0 = C - A;
	Vec2i v1 = B - A;
	Vec2i v2 = P - A;
	int dot00 = v0.dot(v0);
	int dot01 = v0.dot(v1);
	int dot02 = v0.dot(v2);
	int dot11 = v1.dot(v1);
	int dot12 = v1.dot(v2);

	float invDenom = 1. / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
	return (u >= 0 and v >= 0 and (u + v) < 1);
}

void Triangle(const Vec2i& A, const Vec2i& B, const Vec2i& C, bool IsFill, Frame& image, const Scalar& color)
{
	if(!IsFill)
	{
		line(A, B, image, color);
		line(B, C, image, color);
		line(A, C, image, color);
	}
	else
	{
		
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