//
// Created by kaylor chen on 2024/6/25.
//

#pragma once

#include <iomanip>
#include "chrono"
#include "string"
#include "ctime"
#include "sstream"

namespace kaylordut{
class Time{
 public:
  std::time_t now_time_t() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    return time;
  }
   char* now_ctime() const {
    auto now = now_time_t();
    return ctime(&now);
  }
  std::string now_str() const {
    return std::string(now_ctime());
  }
  template<class T>
  uint64_t duration_since_epoch() const{
    return std::chrono::duration_cast<T>(std::chrono::system_clock::now().time_since_epoch()).count();
  }
  Time(){
    tp_ = std::chrono::system_clock::now();
  }
  template<class T>
  T duration_from_last_call() {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<T>(now - tp_);
    tp_ = now;
    return duration;
  }
  static std::string current_time_as_filename(){
    std::ostringstream ss;
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); // 获取当前时间
    std::tm bt = *std::localtime(&t);
    ss << std::put_time(&bt, "%Y-%m-%d_%H-%M-%S"); // 格式化时间为年-月-日_时-分-秒
    return ss.str(); // 转换为字符串
  }
 private:
  std::chrono::system_clock::time_point tp_;
};
}
