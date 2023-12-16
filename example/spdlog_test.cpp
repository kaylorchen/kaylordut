//
// Created by kaylor on 12/16/23.
//
#include "kaylordut/log/logger.h"
#include "iostream"

int main(int argc, char **argv){
  int a = 0;
  KAYLORDUT_LOG_TRACE("a = {}", a++);
  KAYLORDUT_LOG_DEBUG("a = {}", a++);
  KAYLORDUT_LOG_INFO("a = {}", a++);
  KAYLORDUT_LOG_WARN("a = {}", a++);
  KAYLORDUT_LOG_ERROR("a = {}", a++);
  KAYLORDUT_LOG_CRITICAL("a = {}", a++);
  return 0;
}