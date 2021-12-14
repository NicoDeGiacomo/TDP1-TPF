#ifndef QUANTUM_CHESS_COMMON_STAGEMODE_H_
#define QUANTUM_CHESS_COMMON_STAGEMODE_H_

#include <string>

#ifdef DEVELOPMENT_MODE_
#define do_log(...) printf(__VA_ARGS__)
#define IS_DEVELOPMENT_MODE_ true
#define MODE_PATH "../"
#else
#define do_log(...)
#define IS_DEVELOPMENT_MODE_ false
#define MODE_PATH "/usr/local/share/"
#endif

class StageMode {
 public:
  static void log([[maybe_unused]] const char* s);

  static void log(const std::string& s);

  static std::string getFullPath(const std::string& s);

  static bool isDevelopmentMode();
};

#endif  // QUANTUM_CHESS_COMMON_STAGEMODE_H_
