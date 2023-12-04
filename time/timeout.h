//
// Created by kaylor chen on 2023/11/14.
//

#pragma once
#include <chrono>
class Timeout {
 public:
  Timeout(const std::chrono::nanoseconds &timeout) : timeout_(timeout) {
    start_ = std::chrono::steady_clock::now();
  }
  bool isTimeout() {
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start_);
    if (elapsed >= timeout_) { return true; }
    return false;
  }
  void set_timeout(const std::chrono::nanoseconds &timeout) {
    timeout_ = timeout;
    start_ = std::chrono::steady_clock::now();
  }
 private:
  std::chrono::nanoseconds timeout_;
  std::chrono::steady_clock::time_point start_;
};
