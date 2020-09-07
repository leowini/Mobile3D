#include "Keyframe.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

using namespace cv;

Keyframe::Keyframe(Mat frame) : img(frame) {
  cvtColor(img, img_gray, COLOR_BGR2GRAY);
  Ptr<FeatureDetector> orb = ORB::create();
  orb->detect(img, keypoints);
  // for (int i = 0; i < keypoints.size(); ++i)
    // p_keypoints.push_back(new Keypoint(keypoints.at(i)));
}

vector<KeyPoint> Keyframe::get_keypoints() const {
  return keypoints;
}

Mat Keyframe::get_img() const {
  return img;
}

Mat Keyframe::get_img_gray() const {
  return img_gray;
}

void Keyframe::set_T(Mat T) {
  this->T = T;
}

Mat Keyframe::get_T() const {
  return T;
}

void Keyframe::set_R(Mat R) {
  this->R = R;
}

Mat Keyframe::get_R() const {
  return R;
}

void Keyframe::set_pose(Mat pose) {
  this->pose = pose;
}

Mat Keyframe::get_pose() const {
  return pose;
}

void Keyframe::remove_keypoint(int index) {
  p_keypoints.erase(p_keypoints.begin() + index);
}
