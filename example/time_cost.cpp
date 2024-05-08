//
// Created by kaylor chen on 2024/5/8.
//
#include <vector>

#include "kaylordut/log/logger.h"
#include "thread"

void foo() {
  for (int i = 0; i < 3; i++) {
    std::cout << "i = " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main() {
  std::vector<int> vec;
  KAYLORDUT_TIME_COST_INFO("Vector insertion", {
    for (int i = 0; i < 1000000; ++i) {
      vec.push_back(i);
    }
  });

  KAYLORDUT_TIME_COST_DEBUG("Vector iteration", {
    long sum = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
      sum += vec[i];
    }
  });

  KAYLORDUT_TIME_COST_INFO("foo function", foo(););
  auto func = []() { std::this_thread::sleep_for(std::chrono::seconds(4)); };
  KAYLORDUT_TIME_COST_INFO("lambda function", func(););

  return 0;
}
