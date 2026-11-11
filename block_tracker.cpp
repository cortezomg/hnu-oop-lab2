#include "block_tracker.h"

#include <iostream>
#include <string>

int BlockTracker::current_depth_ = 0;

BlockTracker::BlockTracker(const std::string &block_name)
    : block_name_(block_name), depth_(++current_depth_) {
  std::cout << std::string(depth_ * 2, ' ') << ">>> Вхід у блок \""
            << block_name_ << "\" (рівень " << depth_ << ")\n";
}

// [ЛР4, п.8] Деструктор фіксує вихід з блоку
BlockTracker::~BlockTracker() {
  std::cout << std::string(depth_ * 2, ' ') << "<<< Вихід з блоку \""
            << block_name_ << "\" (рівень " << depth_ << ")\n";
  --current_depth_;
}
