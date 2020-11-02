#include "Rasterization.h"

Vec4i Rasterization::BoundingBox(const Vec2i& A, const Vec2i& B, const Vec2i& C)
{
	int XMin, XMax, YMin, YMax;

	XMin = min(min(A[0], B[0]), C[0]);
	YMin = min(min(A[1], B[1]), C[1]);
	XMax = max(max(A[0], B[0]), C[0]);
	YMax = max(max(A[1], B[1]), C[1]);

	return Vec4i(XMin, YMin, XMax, YMax);
}
