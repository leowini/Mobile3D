#ifndef RECONSTRUCTOR_H
#define RECONSTRUCTOR_H

#include "Motion.h"
#include "Depth.h"
#include "MeshReconstructor.h"
#include "TextureMapper.h"
#include "Map.h"

using namespace cv;

class Reconstructor {
public:
  Reconstructor();
  void reconstruct();
  void track_image(const Mat &img);
  void track_IMU();
  void cancel_reconstruction();
private:
  Motion *motionEstimator;
  Depth *depthReconstructor;
  MeshReconstructor *meshReconstructor;
  TextureMapper *textureMapper;
  Map map;
  std::string sparse_pointcloud;
  int tsdf_volume;
  int mesh;
};

#endif
