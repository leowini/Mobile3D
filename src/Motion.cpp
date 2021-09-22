#include "Motion.h"
#include <thread>
#include <iostream>

using namespace std;

Motion::Motion(Map &map) : map(map) {
  // Start motion tracking threads
  feature_tracker = new FeatureTracker(map);
  IMU_integrator = new IMUIntegrator();
}

void Motion::track_image(const Mat &image) {
  if (IMU_integrator->ready_to_track) {
    int *rot = new int(IMU_integrator->get_rot());
    Mat *img = new Mat(image);
    feature_tracker->post_image(img, rot);
    IMU_integrator->ready_to_track = false;
  }
}

void Motion::track_IMU(const double roll, const double pitch, const double yaw) {
  int *imu_data_point = new int(0);
  IMU_integrator->post_IMU(imu_data_point);
}

void Motion::stop_recording() {
  feature_tracker->exit_tracking_thread();
  //IMU_integrator->exit_IMU_thread();
  delete feature_tracker;
  delete IMU_integrator;
  feature_tracker = nullptr;
  IMU_integrator = nullptr;
  structure_estimator = new StructureEstimator(map);
}
