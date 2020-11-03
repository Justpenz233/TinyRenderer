#pragma once
#include "CoreMinimal.h"

using namespace cv;

class Rasterization
{
	void Line(const int& x0, const int& y0, const int& x1, const int& y1, 
		Frame& image, const Scalar& color);
	
	void Line(const Vec2i& A, const Vec2i& B, Frame& image, const Scalar& color);
	
	bool PointInTriangle(const Vec2i& A, const Vec2i& B, const Vec2i& C, const Vec2i& P);
	
	void Triangle(const Vec2i& A, const Vec2i& B, const Vec2i& C, bool IsFill);
	
	Vec4i BoundingBox(const Vec2i& A, const Vec2i& B, const Vec2i& C);
	
	Vec4i BoundingBox(std::vector<Vec2i> pts);
};

