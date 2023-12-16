//
// Created by kaylor on 12/16/23.
//

#pragma once
#include <fmt/format.h>
#include "map"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "iostream"

namespace common {

class Logger {
 public:
  static Logger &Instance() {
    static Logger instance("spdlog");
    return instance;
  }

  Logger(std::string &&logger_name) {
    try {
      auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
      logger_ = std::make_shared<spdlog::logger>(logger_name, console_sink);
      logger_->set_level(ReadLogLevelFromEnv());
      logger_->set_pattern("%v");
    }
    catch (const spdlog::spdlog_ex &ex) {}
  }
  ~Logger() {}
  const std::shared_ptr<spdlog::logger> GetLogger() const { return logger_; }
 private:
  spdlog::level::level_enum ReadLogLevelFromEnv() {
    const char *value = std::getenv("SPDLOG_LEVEL");
    if (value != nullptr) {
      std::map<std::string, spdlog::level::level_enum> level_map = {
          {"trace", spdlog::level::trace},
          {"debug", spdlog::level::debug},
          {"info", spdlog::level::info},
          {"warning", spdlog::level::warn},
          {"error", spdlog::level::err},
          {"critical", spdlog::level::critical}
      };
      try {
        auto ret = level_map.at(std::string(value));
        return ret;
      } catch (const std::out_of_range &e) {
        // 返回默认值
        std::cout << "environment variable SPDLOG_LEVEL is invalid, and set default level\n";
        return spdlog::level::info;
      }
    } else {
      // 返回默认值
      std::cout << "environment variable SPDLOG_LEVEL is not set, and set default level\n";
      return spdlog::level::info;
    }
  }
  std::shared_ptr<spdlog::logger> logger_;
};
}  // namespace common

#define SUFFIX_FORMAT fmt::format("{}() at {}:{}",__func__ ,__FILE__, __LINE__)
#define DEBUG_FORMAT (fmt::format("| [DEBUG] ") + SUFFIX_FORMAT)
#define TRACE_FORMAT (fmt::format("| [TRACE] ") + SUFFIX_FORMAT)
#define INFO_FORMAT (fmt::format("| [INFO] ") + SUFFIX_FORMAT)
#define WARN_FORMAT (fmt::format("| [WARN] ") + SUFFIX_FORMAT)
#define ERROR_FORMAT (fmt::format("| [ERROR] ") + SUFFIX_FORMAT)
#define CRITICAL_FORMAT (fmt::format("| [CRITICAL] ") + SUFFIX_FORMAT)

#define KAYLORDUT_LOG_TRACE(...) \
    { SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(), spdlog::level::trace, fmt::format(__VA_ARGS__) + TRACE_FORMAT); }

#define KAYLORDUT_LOG_DEBUG(...) \
    { SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(), spdlog::level::debug, fmt::format(__VA_ARGS__) + DEBUG_FORMAT); }

#define KAYLORDUT_LOG_INFO(...) \
    { SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(), spdlog::level::info, fmt::format(__VA_ARGS__) + INFO_FORMAT); }

#define KAYLORDUT_LOG_WARN(...) \
    { SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(), spdlog::level::warn, fmt::format(__VA_ARGS__) + WARN_FORMAT); }

#define KAYLORDUT_LOG_ERROR(...) \
    { SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(), spdlog::level::err, fmt::format(__VA_ARGS__) + ERROR_FORMAT); }

#define KAYLORDUT_LOG_CRITICAL(...) \
    { SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(), spdlog::level::critical, fmt::format(__VA_ARGS__) + CRITICAL_FORMAT); }
