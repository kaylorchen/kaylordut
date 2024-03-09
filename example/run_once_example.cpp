#include "iomanip"
#include "iostream"
#include "kaylordut/time/run_once.h"

void callback(void) {
  static int count = 0;
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);
  struct tm* time_info = std::localtime(&now_time);
  std::cout << "Current time：";
  std::cout << std::put_time(time_info, "%Y-%m-%d %H:%M:%S")
            << ", count = " << count++ << std::endl;
}

int main(void) {
  callback();
  run_once_with_delay(callback, std::chrono::seconds(3));
  callback();
  run_once_with_delay(callback, std::chrono::seconds(5));
  callback();
  return 0;
}