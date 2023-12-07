//
// Created by kaylor on 12/7/23.
//
#include "iostream"
#include "kaylordut/time/time_duration.h"
#include "thread"
int main(void) {
  int count = 10;
  TimeDuration time_duration;
  while (count--) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        time_duration.DurationSinceLastTime());
    std::cout << "count is " << count << ", duration is " << duration.count()
              << std::endl;
  }
  return 0;
}
