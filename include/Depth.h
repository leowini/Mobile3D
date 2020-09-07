#ifndef DEPTH_H
#define DEPTH_H

#include "DepthMapEstimator.h"
#include "DepthFusion.h"
#include "Keyframe.h"
#include "Map.h"
#include <vector>

using namespace std;

class Depth {
public:
  Depth(Map &map, std::string sparse_pointcloud);
  void reconstructDepth();
private:
  DepthMapEstimator *depthMapEstimator;
  DepthFusion *depthFusion;
};

#endif
