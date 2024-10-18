//
// Created by kaylor on 10/18/24.
//
#include <thread>
#include "kaylordut/tools/terminate_signal.h"
#include "kaylordut/log/logger.h"

void thread1(){
  while (!TerminateSignal::getInstance().isTerminated()){
    KAYLORDUT_LOG_INFO("this is thread1")
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  KAYLORDUT_LOG_INFO("exit thread1");
};