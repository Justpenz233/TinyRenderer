#include <iostream>
#include <limits>
#include "Engine/CoreMinimal.h"
#include "Engine/Model.h"

using namespace cv;

int FrameWidth;
int FrameHeight;
float* ZBuffer;

Scalar RandColor()
{
	int t1 = rand() % 256;
	int t2 = rand() % 256;
	int t3 = rand() % 256;
	return Scalar(t1, t2, t3);
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
Vec2i World2Screen(const Vec3f& Vert)
{
	const int x0 = (Vert[0] + 1.) * (FRAME_WIDTH - 1) / 2. + .5;
	const int y0 = (Vert[1] + 1.) * (FRAME_HEIGHT - 1) / 2. + .5;
	return Vec2i(x0, y0);
}

// Bresenham’s Line Drawing 
void Line(int x0, int y0, int x1, int y1, Frame& image, const Scalar& color) {
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
void Line(const Vec2i& A, const Vec2i& B, Frame& image, const Scalar& color) {
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
	float t = 2. * abs(dy);
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


bool PointInTriangle(const Vec2i& A, const Vec2i& B, const Vec2i& C, const Vec2i& P)
{
	Vec2i v0 = C - A;
	Vec2i v1 = B - A;
	Vec2i v2 = P - A;
	const int dot00 = v0.dot(v0);
	const int dot01 = v0.dot(v1);
	const int dot02 = v0.dot(v2);
	const int dot11 = v1.dot(v1);
	const int dot12 = v1.dot(v2);

	const double invDenom = 1. / (dot00 * dot11 - dot01 * dot01);
	const double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	const double v = (dot00 * dot12 - dot01 * dot02) * invDenom;
	return (u >= 0. and v >= 0. and (u + v) <= 1.);
}

Vec3f Barycentric(const Vec2i& A, const Vec2i& B, const Vec2i& C, const Vec2i& P)
{
	Vec3f s[2];
	for(int i = 1;i >= 0;i --)
	{
		s[i][0] = C[i] - A[i];
		s[i][1] = B[i] - A[i];
		s[i][2] = A[i] - P[i];
	}

	Vec3f u = s[0].cross(s[1]);
	
	if (std::abs(u[2]) > 0.)
		return Vec3f(1.f - (u[0] + u[1]) / u[2], u[0] / u[2], u[1] / u[2]);

	else return Vec3f(-1, 1, 1);
}

//Draw A world Triangle to Screen
void Triangle(const std::vector<Vec3f>& Tri, Frame& image, const Scalar& color, bool IsFill)
{
	if (IsFill)
	{
		const Vec2i AScreen = World2Screen(Tri[0]);
		const Vec2i BScreen = World2Screen(Tri[1]);
		const Vec2i CScreen = World2Screen(Tri[2]);
		
		Rect BBox = boundingRect(std::vector<Vec2i>{AScreen, BScreen, CScreen}); //Find Bounding Box

		for (int i = BBox.x; i < BBox.x + BBox.width; i++)
		{
			for (int j = BBox.y; j < BBox.y + BBox.height; j++)
			{
				Vec3f u = Barycentric(AScreen, BScreen, CScreen, Vec2i(i, j));
				if (u[0] < 0 || u[1] < 0 || u[2] < 0) 
					continue;

				//应用ZBuffer
				if(ZBuffer != nullptr)
				{
					float Pz = 0.;
					for(int k = 0;k < 3;k ++)
					{
						Pz += Tri[k][2] * u[k];
					}
					if(ZBuffer[i * FrameWidth + j] <= Pz)
					{
						image.Set(i, j, color);
						ZBuffer[i * FrameWidth + j] = Pz;
					}
				}
				//无ZBuffer
				else
				{
					image.Set(i, j, color);
				}
			}
		}
	}
	else
	{
		const Vec2i A = World2Screen(Tri[0]);
		const Vec2i B = World2Screen(Tri[1]);
		const Vec2i C = World2Screen(Tri[2]);
		Line(A, B, image, color);
		Line(B, C, image, color);
		Line(A, C, image, color);
	}
}

void DEBUG()
{
	Frame t_frame(FRAME_WIDTH, FRAME_HEIGHT);
	
	cv::imshow("test", t_frame.GetImage());
	cv::waitKey(0);
	exit(0);
}

int main()
{
//	DEBUG();
	FrameWidth = FRAME_WIDTH;
	FrameHeight = FRAME_HEIGHT;

	ZBuffer = new float[FrameWidth * FrameHeight]();
	for(int i = 0;i < FrameWidth * FrameHeight;i ++)
	{
		ZBuffer[i] = - std::numeric_limits<float>::max();
	}
	
	Frame t_frame(FRAME_WIDTH, FRAME_HEIGHT);
	Model t_model("head.obj");

	//一个全局平行光照 数字的大小代表光照的强度
	Vec3f GlobalLight(0, 0, -0.8);
	
	for (int i = 0; i < t_model.FaceSize(); i++) 
	{
		std::vector<int> face = t_model.Face(i);
		std::vector<Vec3f> Tri;
		for (int j = 0; j < 3; j++) 
		{
			Vec3f v0 = t_model.Vert(face[j]);
			Tri.push_back(v0);
		}

		//光照计算 叉乘求面的法向量 Normal
		//Normal 点乘 光的方向 为这个面的亮度
		Vec3f Normal = (Tri[2] - Tri[0]).cross(Tri[1] - Tri[0]);
		float n = cv::normalize(Normal).dot(GlobalLight);
		if (n > 0)
			Triangle(Tri, t_frame, Scalar(n * 255., n * 255., n * 255.), true);
	}

	
	cv::imshow("test", t_frame.GetImage());
	cv::waitKey(0);
	return 0;
}