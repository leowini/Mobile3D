#ifndef MOTION_H
#define MOTION_H

#include "IMUIntegrator.h"
#include "FeatureTracker.h"
#include "StructureEstimator.h"

using namespace std;
using namespace cv;

class Motion {
public:
  Motion(Map &map);
  void stop_recording();
  void track_image(const Mat &img);
  void track_IMU(int imu_data);
private:
  FeatureTracker *feature_tracker;
  IMUIntegrator *IMU_integrator;
  StructureEstimator *structure_estimator;
  Map &map;
};

#endif
