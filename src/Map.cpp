#include "Map.h"

Map::Map() {

}

void Map::add_keyframe(Keyframe *keyframe) {
  keyframes.insert(keyframe);
}

void Map::add_keypoint(Keypoint *keypoint) {
  keypoints.insert(keypoint);
}

void Map::erase_keyframe(Keyframe *keyframe) {
  keyframes.erase(keyframe);
}

void Map::erase_keypoint(Keypoint *keypoint) {
  keypoints.erase(keypoint);
}

set<Keyframe *> Map::get_keyframes() const {
  return keyframes;
}

set<Keypoint *> Map::get_keypoints() const {
  return keypoints;
}

int Map::num_keyframes() const {
  return keyframes.size();
}

void Map::filter_feature_tracks() {

}
