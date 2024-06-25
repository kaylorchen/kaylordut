//
// Created by kaylor chen on 2024/6/25.
//
#include "kaylordut/time/time.h"
#include "kaylordut/log/logger.h"
#include "thread"

int main(int argc, char** argv){

  kaylordut::Time time;
  auto time1 = time.now_ctime();
  auto time2 = time.now_time_t();
  auto time3 = time.now_str();
  auto time4 = time.duration_since_epoch<std::chrono::nanoseconds>();
  auto time5 = time.duration_since_epoch<std::chrono::seconds>();
  auto time6 = time.duration_since_epoch<std::chrono::microseconds>();
  KAYLORDUT_LOG_INFO(" {} {} {} {}\n {}\n {}", time1, time2, time3, time4, time5, time6);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  auto duration = time.duration_from_last_call<std::chrono::milliseconds>();
  KAYLORDUT_LOG_INFO("duration is {}ms", duration.count());
  KAYLORDUT_LOG_INFO("filename: {}", kaylordut::Time::current_time_as_filename());
  return 0;
}
