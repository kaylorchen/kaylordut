//
// Created by kaylor on 10/16/24.
//
#include <thread>
#include "kaylordut/tools/terminate_signal.h"

int main(int argc, char** argv){
  while(!GLOBAL_SIGNAL_STOP){
    KAYLORDUT_LOG_INFO("RUNNING");
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}