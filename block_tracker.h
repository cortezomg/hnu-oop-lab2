#ifndef LAB4_BLOCK_TRACKER_H_
#define LAB4_BLOCK_TRACKER_H_

#include <string>

// [ЛР4, п.8] Клас для відстеження входження у блок програми (конструктор) та
// виходу з нього (деструктор) для блоку, у якому визначено його об'єкт
class BlockTracker {
public:
  explicit BlockTracker(const std::string &block_name);
  BlockTracker(const BlockTracker &) = delete;
  BlockTracker &operator=(const BlockTracker &) = delete;
  ~BlockTracker();

private:
  std::string block_name_;
  int depth_;

  static int current_depth_;
};

#endif // LAB4_BLOCK_TRACKER_H_
