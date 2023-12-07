//
// Created by kaylor on 12/7/23.
//

#pragma once
#include "chrono"
class TimeDuration {
 public:
  TimeDuration() { time_point_ = std::chrono::steady_clock::now(); }
  std::chrono::nanoseconds DurationSinceLastTime() {
    auto now = std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(now - time_point_);
    time_point_ = now;
    return duration;
  }

 private:
  std::chrono::steady_clock::time_point time_point_;
};