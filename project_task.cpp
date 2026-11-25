#include "project_task.h"

#include <iostream>
#include <string>

ProjectTask::ProjectTask()
    : id_(0), title_("Без назви"), assignee_("—"), priority_(1), hours_(0) {}

ProjectTask::ProjectTask(int id, const std::string &title,
                         const std::string &assignee, int priority, int hours)
    : id_(id), title_(title), assignee_(assignee), priority_(priority),
      hours_(hours) {}

bool ProjectTask::operator<(const ProjectTask &other) const {
  if (priority_ != other.priority_) {
    return priority_ < other.priority_;
  }
  return id_ > other.id_;
}

bool ProjectTask::operator==(const ProjectTask &other) const {
  return id_ == other.id_;
}

std::ostream &operator<<(std::ostream &os, const ProjectTask &task) {
  os << "#" << task.id_ << " " << task.title_ << " [" << task.assignee_
     << ", пріоритет " << task.priority_ << ", " << task.hours_ << " год]";
  return os;
}
