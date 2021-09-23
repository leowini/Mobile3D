#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "Feature.h"
#include <opencv2/core/mat.hpp>
#include <vector>

using namespace std;
using namespace cv;

class Keypoint;

class Keyframe {
public:
  Keyframe(Mat frame);
  vector<KeyPoint> get_keypoints() const;
  Mat get_img() const;
  Mat get_img_gray() const;
  void set_T(Mat T);
  Mat get_T() const;
  void set_R(Mat R);
  Mat get_R() const;
  void set_pose(Mat pose);
  Mat get_pose() const;
  void remove_keypoint(int index);
private:
  Mat img;
  Mat img_gray;
  vector<KeyPoint> keypoints;
  vector<Keypoint *> p_keypoints;
  Mat T;
  Mat R;
  Mat pose;
};

#endif
