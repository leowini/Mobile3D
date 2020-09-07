#include "Keypoint.h"

Keypoint::Keypoint() {
  
}

Keypoint::~Keypoint() {
  for(map<Keyframe *, size_t>::const_iterator it = observations.begin(); it != observations.end(); ++it ) {
    Keyframe *key = it->first;
    size_t value = it->second;
    key->remove_keypoint(value);
    remove_observation(key);
  } 
}

void Keypoint::add_observation(Keyframe *keyframe, size_t idx) {
  observations.insert({keyframe, idx});
}

void Keypoint::remove_observation(Keyframe *keyframe) {
  observations.erase(keyframe);
}

int Keypoint::get_num_observations() const {
  return observations.size();
}
