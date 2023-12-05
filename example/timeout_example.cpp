#include "iostream"
#include "kaylordut/time/timeout.h"
#include "thread"
int main(void){
  std::cout << "Timeout example\n";
  Timeout timeout(std::chrono::seconds(10));
  while(!timeout.isTimeout()){
    auto now  = std::chrono::system_clock::now();
    auto now_ = std::chrono::system_clock::to_time_t(now);
    std::cout << "now is " << ctime(&now_);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  return 0;
}