#ifndef STRUCTURE_ESTIMATOR_H
#define STRUCTURE_ESTIMATOR_H

#include "Keyframe.h"
#include "Map.h"
#include <vector>

class StructureEstimator {
public:
  StructureEstimator(Map &map);
  void estimate_structure();
private:
  void filter_feature_tracks();
  void estimate_translation(Keyframe *first_frame, Keyframe *next_frame);
  void calc_inverse_depth();
  Mat cross_op(const Mat &in_vec);
  void motion_only_BA();
  void structure_only_BA();
  void loop_closure();
  void global_BA_g2o();
  Map &map;
};

#endif
