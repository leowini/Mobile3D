#include <iostream>
#include "Reconstructor.h"

using namespace std;
using namespace cv;

int main() {
  Reconstructor *reconstructor = new Reconstructor();
  reconstructor->track_IMU();
  reconstructor->track_IMU();
  reconstructor->reconstruct();
  delete reconstructor;
  reconstructor = nullptr;
  cout << "success" << endl;
  return 0;
}

Reconstructor::Reconstructor() {
  motionEstimator = new Motion(map);
}

void Reconstructor::track_image(const Mat &img) {
  motionEstimator->track_image(img);
}

void Reconstructor::track_IMU() {
  motionEstimator->track_IMU(0);
}

void Reconstructor::reconstruct() {
  motionEstimator->stop_recording();
  delete motionEstimator;
  motionEstimator = nullptr;
  depthReconstructor = new Depth(map, sparse_pointcloud);
  depthReconstructor->reconstructDepth();
  delete depthReconstructor;
  depthReconstructor = nullptr;
  meshReconstructor = new MeshReconstructor(tsdf_volume);
  meshReconstructor->reconstructMesh();
  delete meshReconstructor;
  meshReconstructor = nullptr;
  textureMapper = new TextureMapper(mesh, map);
  delete textureMapper;
  textureMapper = nullptr;
}

void Reconstructor::cancel_reconstruction() {
  
}
