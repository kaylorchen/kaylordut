//
// Created by kaylor on 10/16/24.
//

#pragma once

#include "csignal"
#include "kaylordut/log/logger.h"
#include "map"

class TerminateSignal {
 public:
  static TerminateSignal &getInstance() {
    static TerminateSignal instance; // Guaranteed to be destroyed, instantiated on first use.
    return instance;
  }

  // Deleted copy constructor and assignment operator to ensure a single instance
  TerminateSignal(const TerminateSignal &) = delete;

  TerminateSignal &operator=(const TerminateSignal &) = delete;

  bool isTerminated() const {
    return terminated_;
  }

  const std::string &signal_map(int signal) { return signal_map_.at(signal); }

  static void signalHandler(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
      TerminateSignal::getInstance().terminated_ = true;
      KAYLORDUT_LOG_WARN("{}, setting terminated to true", TerminateSignal::getInstance().signal_map(signal));
    }
  }

 private:
  TerminateSignal() : terminated_(false) {
    // Register signal handler
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);
  }

  bool terminated_;
  std::map<int, std::string> signal_map_{
      {SIGINT, "Interactive attention signal. (Ctrl + C)"},
      {SIGTERM, "Termination request"}
  };
};

auto &terminate_signal = TerminateSignal::getInstance();

#define GLOBAL_SIGNAL_STOP (terminate_signal.isTerminated())
