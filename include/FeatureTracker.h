#ifndef FEATURE_TRACKER_H
#define FEATURE_TRACKER_H

#include "Keyframe.h"
#include "Map.h"
#include <thread>
#include <condition_variable>
#include <queue>

using namespace std;
using namespace cv;

struct ThreadMsg;

class FeatureTracker {
public:
  FeatureTracker(Map &map);
  void post_image(const Mat *image, const int *rot);
  void start_tracking();
  void exit_tracking_thread();
private:
  void track(const Mat &image);
  void tracking_process();
  thread *tracking_thread;
  mutex image_mutex;
  queue<ThreadMsg*> image_queue;
  condition_variable cond_var;
  Map &map;
};

#endif
