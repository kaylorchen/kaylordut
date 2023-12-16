//
// Created by kaylor on 12/16/23.
//
#include "iostream"
#include "kaylordut/log/logger.h"
#include "thread"

int main(int argc, char **argv) {
  int a = 0;
  KAYLORDUT_LOG_TRACE("a = {}", a++);
  KAYLORDUT_LOG_DEBUG("a = {}", a++);
  KAYLORDUT_LOG_INFO("a = {}", a++);
  KAYLORDUT_LOG_WARN("a = {}", a++);
  auto foo = [&a]() { KAYLORDUT_LOG_INFO("a = {}", a++); };
  foo();
  KAYLORDUT_LOG_ERROR("a = {}", a++);
  KAYLORDUT_LOG_CRITICAL("a = {}", a++);
  std::thread(foo).join();
  int count = 5;
  do {
    KAYLORDUT_LOG_INFO_ONCE("once");
    KAYLORDUT_LOG_DEBUG("normal")
    KAYLORDUT_LOG_INFO_ONCE("test");
    KAYLORDUT_LOG_INFO("count is {}", count);
  } while (--count);
  KAYLORDUT_LOG_INFO("count is {}", count);
  KAYLORDUT_LOG_CRITICAL_EXPRESSION(count == 0, "count is {}", count);
  KAYLORDUT_LOG_CRITICAL_FUNCTION([]() { return true; },
                                  "return value is true");
  KAYLORDUT_LOG_CRITICAL_FUNCTION([]() { return false; },
                                  "return value is false");
  return 0;
}