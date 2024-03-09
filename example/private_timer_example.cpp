//
// Created by kaylor chen on 2023/11/24.
//
#include "kaylordut/time/private_timer.h"
#include "iomanip"

void callback(void){
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);
  struct tm* time_info = std::localtime(&now_time);
  std::cout << "Current time：";
  std::cout << std::put_time(time_info, "%Y-%m-%d %H:%M:%S") << std::endl;
}

int main(void){
  PrivateTimer private_timer;
  private_timer.start(std::chrono::milliseconds(1000), callback);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  private_timer.stop();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  return 0;
}