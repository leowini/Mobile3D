#include "StructureEstimator.h"
#include "Optimizer.h"
#include <opencv2/core.hpp>
#include <iostream>

using namespace cv;
using namespace std;

StructureEstimator::StructureEstimator(Map &map) : map(map) {
  estimate_structure();
}

void StructureEstimator::estimate_structure() {
  map.filter_feature_tracks();
  if (map.num_keyframes() < 2)
    return;
  Keyframe *first_frame = nullptr;//*(map.get_keyframes().begin());
  Keyframe *second_frame = nullptr;//*(map.get_keyframes().begin()+1);
  // pick a reference point
  // this point's inverse depth will be held constant
  Mat T;
  for (int i = 0; i < 20; ++i) {
    estimate_translation(first_frame, second_frame);
    calc_inverse_depth();
  }
  for (int i = 2; i < map.num_keyframes(); ++i) {
    Keyframe *next_frame = nullptr;//*(map.get_keyframes().begin());
    estimate_translation(first_frame, next_frame);
    calc_inverse_depth();
  }
}

void StructureEstimator::estimate_translation(Keyframe *first_frame, Keyframe *next_frame) {
  const Mat &R = next_frame->get_R();
  // inverse depth values for five points
  Mat alpha;
  Mat xj, xj1;
  Mat b = -1 * cross_op(xj) * R * xj1;
  Mat A = alpha * cross_op(xj);
  Mat T;
  // T = least squares (A, b)
  next_frame->set_T(T);
}

void StructureEstimator::calc_inverse_depth() {
  int num_frames = 5;
  Mat top_sum, bottom_sum;
  vector<Mat> xji;
  Mat xj1;
  Mat R;
  Mat T;
  for (int i = 1; i < num_frames; ++i) {
    top_sum += (cross_op(xji.at(i)) * T).t() * cross_op(xji.at(i)) * R * xj1;
    bottom_sum += 1;
  }
  Mat alpha_j;
  divide(top_sum, bottom_sum, alpha_j);
  alpha_j *= -1;
}

Mat StructureEstimator::cross_op(const Mat &in_vec) {
  Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
  return C;
}

void StructureEstimator::motion_only_BA() {

}

void StructureEstimator::structure_only_BA() {

}

void StructureEstimator::loop_closure() {
  global_BA_g2o();
}

void StructureEstimator::global_BA_g2o() {

}
