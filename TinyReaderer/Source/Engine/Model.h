#pragma once
#include <opencv2/imgproc.hpp>
class Model
{
private:
	std::vector<cv::Vec3f> verts_;
	std::vector<std::vector<int> > faces_;
public:
	Model(const char* filename);
	~Model();
	int VertSize();
	int FaceSize();
	cv::Vec3f Vert(int i);
	std::vector<int> Face(int idx);
	std::vector<cv::Vec3f> FaceVert(int idx);
};

