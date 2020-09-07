#include "IMUIntegrator.h"
#include <iostream>

#define MSG_EXIT_THREAD     1
#define MSG_IMU_TRACK       2

using namespace std;

struct ThreadMsg {
  ThreadMsg(int i, const void* m) { id = i; msg = m; }
  int id;
  const void* msg;
};

IMUIntegrator::IMUIntegrator() {
  bool success = start_IMU_thread();
}

bool IMUIntegrator::start_IMU_thread() {
  if (!IMU_thread)
    IMU_thread = new thread(&IMUIntegrator::IMU_process, this);
  return true;
}

void IMUIntegrator::exit_IMU_thread() {
  if (!IMU_thread)
    return;
  ThreadMsg* threadMsg = new ThreadMsg(MSG_EXIT_THREAD, 0);
  {
    lock_guard<mutex> lock(IMU_mutex);
    IMU_queue.push(threadMsg);
    cond_var.notify_one();
  }
  IMU_thread->join();
  delete IMU_thread;
  IMU_thread = nullptr;
}

void IMUIntegrator::post_IMU(const int *imu_data) {
  ThreadMsg *threadMsg = new ThreadMsg(MSG_IMU_TRACK, imu_data);
  unique_lock<mutex> lk(IMU_mutex);
  IMU_queue.push(threadMsg);
  cond_var.notify_one();
}

void IMUIntegrator::trackIMU(int imu_data) {
  cout << imu_data << endl;	
  // rotation calculations
  // ...
  // ...
  // set rotation
  {
    lock_guard<mutex> lk(rot_mutex);
    rot = 3;
  }
  if (get_rot() >= 3)
    ready_to_track = true;
}

void IMUIntegrator::IMU_process() {
  while (1) {
    // wait for IMU data
    ThreadMsg *msg = nullptr;
    {
      unique_lock<mutex> lk(IMU_mutex);
      while (IMU_queue.empty())
        cond_var.wait(lk);
      if (IMU_queue.empty())
	continue;
      msg = IMU_queue.front();
      IMU_queue.pop();
    } 
    switch (msg->id) {
      case MSG_IMU_TRACK:
      {
	// track IMU data
	const int* imu_data = static_cast<const int*>(msg->msg);
	trackIMU(*imu_data);
	delete imu_data;
	delete msg;
        break;
      }
      case MSG_EXIT_THREAD:
      {
	delete msg;
	unique_lock<mutex> lk(IMU_mutex);
	while (!IMU_queue.empty()) {
          msg = IMU_queue.front();
	  IMU_queue.pop();
	  delete msg;
	}
        return;
      }
      default:
      {
	break;
      }
    }
  }
}

int IMUIntegrator::get_rot() {
  lock_guard<mutex> lk(rot_mutex);
  return rot;
}
