#include "Model.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace cv;

Model::Model(const char* filename) : verts_(), faces_() {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i = 0; i < 3; i++) iss >> v.val[i];
            verts_.push_back(v);
        }
        else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--; // in wavefront obj all indices start at 1, not zero
                f.push_back(idx);
            }
            faces_.push_back(f);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::VertSize() {
    return (int)verts_.size();
}

int Model::FaceSize() {
    return (int)faces_.size();
}

std::vector<int> Model::Face(int idx) {
    return faces_[idx];
}

std::vector<cv::Vec3f> Model::FaceVert(int idx)
{
    return std::vector<Vec3f>{verts_[faces_[idx][0]], verts_[faces_[idx][1]], verts_[faces_[idx][2]]};
}

Vec3f Model::Vert(int i) {
    return verts_[i];
}
