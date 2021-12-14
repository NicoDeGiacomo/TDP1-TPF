#include "StageMode.h"

void StageMode::log([[maybe_unused]] const char* s) {
    do_log("%s\n", s);
}

void StageMode::log(const std::string& s) {
    log(s.c_str());
}

std::string StageMode::getFullPath(const std::string &s) {
    return MODE_PATH + s;
}

bool StageMode::isDevelopmentMode() {
    return IS_DEVELOPMENT_MODE_;
}
