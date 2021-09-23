#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "Keyframe.h"
#include "Feature.h"
#include <vector>

using namespace std;

class Optimizer {
public:
  static void GlobalBundleAdjustment(const vector<Keyframe> &keyframes, const vector<Keypoint> &keypoints, int iterations = 5, const unsigned long loopKF = 0);
};

#endif
