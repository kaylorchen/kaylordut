//
// Created by kaylor on 12/16/23.
//

#pragma once
#include <fmt/format.h>

#include "iostream"
#include "map"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/systemd_sink.h"
#include "spdlog/spdlog.h"

namespace common {

class Logger {
 public:
  static Logger &Instance() {
    static Logger instance("spdlog");
    return instance;
  }

  Logger(std::string &&logger_name) {
    try {
      std::vector<spdlog::sink_ptr> sinks;
      if (IsEnableStdOut()) {
        auto console_sink =
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        sinks.emplace_back(console_sink);
      }
      if (IsEnableSystemd()) {
        auto systemd_sink = std::make_shared<spdlog::sinks::systemd_sink_mt>();
        sinks.emplace_back(systemd_sink);
      }

      logger_ = std::make_shared<spdlog::logger>(logger_name, sinks.begin(),
                                                 sinks.end());
      logger_->set_level(ReadLogLevelFromEnv());
      logger_->set_pattern("%v");
    } catch (const spdlog::spdlog_ex &ex) {
    }
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
          {"critical", spdlog::level::critical}};
      try {
        auto ret = level_map.at(std::string(value));
        return ret;
      } catch (const std::out_of_range &e) {
        // 返回默认值
        std::cout << "environment variable SPDLOG_LEVEL is invalid, and set "
                     "default level\n";
        return spdlog::level::info;
      }
    } else {
      // 返回默认值
      std::cout << "environment variable SPDLOG_LEVEL is not set, and set "
                   "default level\n";
      return spdlog::level::info;
    }
  }
  /**
   * 通过环境变量使能stdout输出
   * @return 默认返回true
   */
  bool IsEnableStdOut() {
    const char *value = std::getenv("SPDLOG_STDOUT");
    if (value != nullptr) {
      std::string var = std::string(value);
      if (var == "true") {
        return true;
      } else if (var == "false") {
        return false;
      } else {
        std::cout
            << "environment variable SPDLOG_STDOUT is invalid, and set true\n";
        return true;
      }
    }
    std::cout
        << "environment variable SPDLOG_STDOUT is not set, and set true\n";
    return true;
  }

  /**
   * 通过环境变量使能systemd的输出
   * @return 默认返回false
   */
  bool IsEnableSystemd() {
    const char *value = std::getenv("SPDLOG_SYSTEMD");
    if (value != nullptr) {
      std::string var = std::string(value);
      if (var == "true") {
        return true;
      } else if (var == "false") {
        return false;
      } else {
        std::cout << "environment variable SPDLOG_SYSTEMD is invalid, and set "
                     "false\n";
        return false;
      }
    }
    std::cout
        << "environment variable SPDLOG_SYSTEMD is not set, and set false\n";
    return false;
  }

  std::shared_ptr<spdlog::logger> logger_;
};
}  // namespace common

#define SUFFIX_FORMAT fmt::format("{}() at {}:{}", __func__, __FILE__, __LINE__)
#define DEBUG_FORMAT (fmt::format(" | [DEBUG] ") + SUFFIX_FORMAT)
#define TRACE_FORMAT (fmt::format(" | [TRACE] ") + SUFFIX_FORMAT)
#define INFO_FORMAT (fmt::format(" | [INFO] ") + SUFFIX_FORMAT)
#define WARN_FORMAT (fmt::format(" | [WARN] ") + SUFFIX_FORMAT)
#define ERROR_FORMAT (fmt::format(" | [ERROR] ") + SUFFIX_FORMAT)
#define CRITICAL_FORMAT (fmt::format(" | [CRITICAL] ") + SUFFIX_FORMAT)

#define KAYLORDUT_LOG_TRACE(...)                                 \
  {                                                              \
    SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(),   \
                       spdlog::level::trace,                     \
                       fmt::format(__VA_ARGS__) + TRACE_FORMAT); \
  }
#define KAYLORDUT_LOG_TRACE_ONCE(...)  \
  do {                                 \
    static bool once = true;           \
    if (once) {                        \
      once = false;                    \
      KAYLORDUT_LOG_TRACE(__VA_ARGS__) \
    }                                  \
  } while (0)

#define KAYLORDUT_LOG_TRACE_FUNCTION(function, ...) \
  do {                                              \
    if ((*function)()) {                            \
      KAYLORDUT_LOG_TRACE(__VA_ARGS__)              \
    }                                               \
  } while (0)

#define KAYLORDUT_LOG_TRACE_EXPRESSION(expression, ...) \
  do {                                                  \
    if (expression) {                                   \
      KAYLORDUT_LOG_TRACE(__VA_ARGS__)                  \
    }                                                   \
  } while (0)

#define KAYLORDUT_LOG_DEBUG(...)                                 \
  {                                                              \
    SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(),   \
                       spdlog::level::debug,                     \
                       fmt::format(__VA_ARGS__) + DEBUG_FORMAT); \
  }
#define KAYLORDUT_LOG_DEBUG_ONCE(...)  \
  do {                                 \
    static bool once = true;           \
    if (once) {                        \
      once = false;                    \
      KAYLORDUT_LOG_DEBUG(__VA_ARGS__) \
    }                                  \
  } while (0)

#define KAYLORDUT_LOG_DEBUG_FUNCTION(function, ...) \
  do {                                              \
    if ((*function)()) {                            \
      KAYLORDUT_LOG_DEBUG(__VA_ARGS__)              \
    }                                               \
  } while (0)

#define KAYLORDUT_LOG_DEBUG_EXPRESSION(expression, ...) \
  do {                                                  \
    if (expression) {                                   \
      KAYLORDUT_LOG_DEBUG(__VA_ARGS__)                  \
    }                                                   \
  } while (0)

#define KAYLORDUT_LOG_INFO(...)                                 \
  {                                                             \
    SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(),  \
                       spdlog::level::info,                     \
                       fmt::format(__VA_ARGS__) + INFO_FORMAT); \
  }
#define KAYLORDUT_LOG_INFO_ONCE(...)  \
  do {                                \
    static bool once = true;          \
    if (once) {                       \
      once = false;                   \
      KAYLORDUT_LOG_INFO(__VA_ARGS__) \
    }                                 \
  } while (0)

#define KAYLORDUT_LOG_INFO_FUNCTION(function, ...) \
  do {                                             \
    if ((*function)()) {                           \
      KAYLORDUT_LOG_INFO(__VA_ARGS__)              \
    }                                              \
  } while (0)

#define KAYLORDUT_LOG_INFO_EXPRESSION(expression, ...) \
  do {                                                 \
    if (expression) {                                  \
      KAYLORDUT_LOG_INFO(__VA_ARGS__)                  \
    }                                                  \
  } while (0)

#define KAYLORDUT_LOG_WARN(...)                                 \
  {                                                             \
    SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(),  \
                       spdlog::level::warn,                     \
                       fmt::format(__VA_ARGS__) + WARN_FORMAT); \
  }
#define KAYLORDUT_LOG_WARN_ONCE(...)  \
  do {                                \
    static bool once = true;          \
    if (once) {                       \
      once = false;                   \
      KAYLORDUT_LOG_WARN(__VA_ARGS__) \
    }                                 \
  } while (0)

#define KAYLORDUT_LOG_WARN_FUNCTION(function, ...) \
  do {                                             \
    if ((*function)()) {                           \
      KAYLORDUT_LOG_WARN(__VA_ARGS__)              \
    }                                              \
  } while (0)

#define KAYLORDUT_LOG_WARN_EXPRESSION(expression, ...) \
  do {                                                 \
    if (expression) {                                  \
      KAYLORDUT_LOG_WARN(__VA_ARGS__)                  \
    }                                                  \
  } while (0)

#define KAYLORDUT_LOG_ERROR(...)                                 \
  {                                                              \
    SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(),   \
                       spdlog::level::err,                       \
                       fmt::format(__VA_ARGS__) + ERROR_FORMAT); \
  }
#define KAYLORDUT_LOG_ERROR_ONCE(...)  \
  do {                                 \
    static bool once = true;           \
    if (once) {                        \
      once = false;                    \
      KAYLORDUT_LOG_ERROR(__VA_ARGS__) \
    }                                  \
  } while (0)

#define KAYLORDUT_LOG_ERORR_FUNCTION(function, ...) \
  do {                                              \
    if ((*function)()) {                            \
      KAYLORDUT_LOG_ERORR(__VA_ARGS__)              \
    }                                               \
  } while (0)

#define KAYLORDUT_LOG_ERORR_EXPRESSION(expression, ...) \
  do {                                                  \
    if (expression) {                                   \
      KAYLORDUT_LOG_ERORR(__VA_ARGS__)                  \
    }                                                   \
  } while (0)

#define KAYLORDUT_LOG_CRITICAL(...)                                 \
  {                                                                 \
    SPDLOG_LOGGER_CALL(common::Logger::Instance().GetLogger(),      \
                       spdlog::level::critical,                     \
                       fmt::format(__VA_ARGS__) + CRITICAL_FORMAT); \
  }
#define KAYLORDUT_LOG_CRITICAL_ONCE(...)  \
  do {                                    \
    static bool once = true;              \
    if (once) {                           \
      once = false;                       \
      KAYLORDUT_LOG_CRITICAL(__VA_ARGS__) \
    }                                     \
  } while (0)

#define KAYLORDUT_LOG_CRITICAL_FUNCTION(function, ...) \
  do {                                                 \
    if ((*function)()) {                               \
      KAYLORDUT_LOG_CRITICAL(__VA_ARGS__)              \
    }                                                  \
  } while (0)

#define KAYLORDUT_LOG_CRITICAL_EXPRESSION(expression, ...) \
  do {                                                     \
    if (expression) {                                      \
      KAYLORDUT_LOG_CRITICAL(__VA_ARGS__)                  \
    }                                                      \
  } while (0)