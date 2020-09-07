#include "Depth.h"
#include "DepthMapEstimator.h"
#include "DepthFusion.h"

Depth::Depth(Map &map, std::string sparse_pointcloud) {
  depthMapEstimator = new DepthMapEstimator();
  depthFusion = new DepthFusion();
}

void Depth::reconstructDepth() {

}
