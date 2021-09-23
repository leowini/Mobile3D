#ifndef MAP_H
#define MAP_H

#include "Keyframe.h"
#include "Feature.h"
#include <set>

class Keyframe;
class Keypoint;

using namespace std;

class Map {
public:
  Map();
  void filter_feature_tracks();
  void add_keyframe(Keyframe *keyframe);
  void add_keypoint(Keypoint *keypoint);
  void erase_keyframe(Keyframe *keyframe);
  void erase_keypoint(Keypoint *keypoint);
  set<Keyframe *> get_keyframes() const;
  set<Keypoint *> get_keypoints() const;
  int num_keyframes() const;
private:
  set<Keyframe *> keyframes;
  set<Keypoint *> keypoints;
};

#endif
