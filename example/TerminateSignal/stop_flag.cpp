//
// Created by kaylor on 10/16/24.
//
#include <thread>
#include "kaylordut/tools/terminate_signal.h"

void thread1();

int main(int argc, char** argv){
  auto t = std::thread([]{thread1();});
  while(!TerminateSignal::getInstance().isTerminated()){
    KAYLORDUT_LOG_INFO("RUNNING");
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  t.join();
  KAYLORDUT_LOG_INFO("exit main thread");
  return 0;
}