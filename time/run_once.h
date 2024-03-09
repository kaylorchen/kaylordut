//
// Created by kaylor on 3/9/24.
//

#pragma once
#include "chrono"
#include "thread"

template <typename T>
void run_once_with_delay(T callback,
                         const std::chrono::nanoseconds total_duration) {
  auto start = std::chrono::high_resolution_clock::now();
  callback();
  auto end = std::chrono::high_resolution_clock::now();
  auto remain_delay =
      total_duration -
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  if (remain_delay > std::chrono::nanoseconds::zero()) {
    std::this_thread::sleep_for(remain_delay);
  }
}