#ifndef IMU_INTEGRATOR_H
#define IMU_INTEGRATOR_H

#include <queue>
#include <condition_variable>
#include <thread>
#include <atomic>

using namespace std;

struct ThreadMsg;

class IMUIntegrator {
public:
  IMUIntegrator();
  void post_IMU(const int *imu_data);
  bool start_IMU_thread();
  void exit_IMU_thread();
  atomic<bool> ready_to_track;
  int get_rot();
private:
  void IMU_process();
  void trackIMU(int imu_data);
  mutex IMU_mutex;
  mutex rot_mutex;
  queue<ThreadMsg*> IMU_queue;
  condition_variable cond_var;
  thread *IMU_thread;
  int rot;
};

#endif
