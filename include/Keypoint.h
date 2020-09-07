#ifndef KEYPOINT_H
#define KEYPOINT_H

#include "Keyframe.h"
#include <map>

using namespace std;

class Keyframe;

class Keypoint {
public:
  Keypoint();
  ~Keypoint();
  void add_observation(Keyframe *keyframe, size_t idx);
  void remove_observation(Keyframe *keyframe);
  int get_num_observations() const;
private:
  map<Keyframe *, size_t> observations;
};

#endif
