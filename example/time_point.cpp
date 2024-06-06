//
// Created by kaylor chen on 2024/6/4.
//

#include "kaylordut/log/logger.h"
#include "chrono"
#include "thread"

int main(){
  // 先记录程序运行时间
  std::chrono::steady_clock::time_point a1 = std::chrono::steady_clock::now();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::chrono::steady_clock::time_point a2 = std::chrono::steady_clock::now();
  KAYLORDUT_LOG_INFO("a1 = {}", std::chrono::duration_cast<std::chrono::seconds>(a1.time_since_epoch()).count());
  KAYLORDUT_LOG_INFO("a2 = {}", a2.time_since_epoch().count());
  std::cout << "秒:"<<std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;
  std::cout << "毫秒:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()<<std::endl;
  std::cout << "微秒:" << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;
  std::cout << "纳秒:" << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;

  return 0;
}