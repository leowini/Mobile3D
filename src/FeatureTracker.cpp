#include "FeatureTracker.h"
#include "Keyframe.h"
#include <vector>
#include <opencv2/video/tracking.hpp>

#define MSG_EXIT_THREAD                 1
#define MSG_TRACK_IMAGE                 2

using namespace std;
using namespace cv;

struct ThreadMsg {
  ThreadMsg(int i, const void* m) { id = i; msg = m; }
  int id;
  const void* msg;
};

FeatureTracker::FeatureTracker(Map &map) : map(map) {
  start_tracking();
}

void FeatureTracker::start_tracking() {
  if (!tracking_thread)
    tracking_thread = new thread(&FeatureTracker::tracking_process, this);
}

void FeatureTracker::exit_tracking_thread() {
  if (!tracking_thread)
    return;
  ThreadMsg *threadMsg = new ThreadMsg(MSG_EXIT_THREAD, 0);
  {
    lock_guard<mutex> lk(image_mutex);
    image_queue.push(threadMsg);
    cond_var.notify_one();
  }
  //might cause segfault
  tracking_thread->join();
  delete tracking_thread;
  tracking_thread = nullptr;
}

void FeatureTracker::post_image(const Mat *image, const int *rot) {
  ThreadMsg *threadMsg = new ThreadMsg(MSG_TRACK_IMAGE, image);
  unique_lock<mutex> lk(image_mutex);
  image_queue.push(threadMsg);
  cond_var.notify_one();
}

void FeatureTracker::tracking_process() {
  while (1) {
    // wait for image
    ThreadMsg *msg = nullptr;
    {
      unique_lock<mutex> lk(image_mutex);
      while (image_queue.empty())
	cond_var.wait(lk);
      if (image_queue.empty())
	continue;
      msg = image_queue.front();
      image_queue.pop();
    }
    // track image
    switch (msg->id) {
      case MSG_TRACK_IMAGE:
      {
        const Mat *image = static_cast<const Mat *>(msg->msg);
        track(*image);
        delete image;
        image = nullptr;
        delete msg;
        msg = nullptr;
        break;
      }
      case MSG_EXIT_THREAD:
      {
        delete msg;
        msg = nullptr;
        unique_lock<mutex> lk(image_mutex);
        while (!image_queue.empty()) {
          msg = image_queue.front();
          image_queue.pop();
          delete msg;
          msg = nullptr;
        }
        return;
      } 
    }
  }
}

/*
   1. Make a keyframe from the image. This makes a gray-scale copy and detects features.
   2. Divide the image into cells, and select the highest Shi-Tomasi response from each cell.
   3. Align the features from the last keyframe in the current frame.
   4. Align the patches we found in the current frame and align them back to the previous frame.
   5. If the second alignment does not return the patch to the initial position, throw out the correspondence.
*/
void FeatureTracker::track(const Mat &frame) {
  Keyframe keyframe(frame);
  if (!map.get_keyframes().empty()) {
    vector<uchar> status;
    vector<float> err;
    const Mat &prevImg = (*map.get_keyframes().end())->get_img_gray();
    const Mat &nextImg = keyframe.get_img_gray();
    const vector<KeyPoint> &prevKeypoints = (*map.get_keyframes().end())->get_keypoints();
    vector<Point2f> prevPoints;
    for (int i = 0; i < prevKeypoints.size(); ++i) {
      prevPoints.push_back(prevKeypoints.at(i).pt);
    }
    vector<Point2f> nextPoints;
    calcOpticalFlowPyrLK(prevImg, nextImg, prevPoints, nextPoints, status, err);
  }
  map.add_keyframe(&keyframe);
}
