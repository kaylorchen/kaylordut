#pragma once
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

class PrivateTimer {
 public:
  PrivateTimer() {
    std::cout << "PrivateTimer constructor is called\n";
  }
  ~PrivateTimer() {
    std::cout << "PrivateTimer destructor is called\n";
  }
  template<typename T>
  void start(const std::chrono::nanoseconds &interval, T callback) {
    m_isRunning = true;
    std::thread([=]() {
      while (m_isRunning) {
        auto start = std::chrono::steady_clock::now();
        callback();
        auto end = std::chrono::steady_clock::now();
        std::chrono::nanoseconds elapsed = end - start;

        if (elapsed < interval) {
          std::this_thread::sleep_for(interval - elapsed);
        } else {
          std::cerr << "Thread id is " << std::this_thread::get_id <<
                    "Elapsed: " << elapsed.count() << "ms" << std::endl;
        }
      }
    }).detach();
  }

  void stop() { m_isRunning = false; }

 private:
  bool m_isRunning = false;
};
