#ifndef FEATURE_H
#define FEATURE_H

#include "Keyframe.h"
#include <map>

using namespace std;

class Keyframe;

class Feature {
public:
  Feature();
  ~Feature();
  void add_observation(Keyframe *keyframe, size_t idx);
  void remove_observation(Keyframe *keyframe);
  int get_num_observations() const;
private:
  map<Keyframe *, size_t> observations;
};

#endif
