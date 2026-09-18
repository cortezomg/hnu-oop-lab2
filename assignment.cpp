#include "assignment.h"
#include <cstring>
#include <iostream>

TaskAssignment::TaskAssignment()
    : assignment_id(0), estimated_hours(0), project_ref_(nullptr),
      manager_ref_(nullptr), assignee_ref_(nullptr) {
  std::strncpy(task_title, "No Task", sizeof(task_title) - 1);
  task_title[sizeof(task_title) - 1] = '\0';
}

TaskAssignment::TaskAssignment(int id, const char *title_str, int hours,
                               const Project *p_ptr, const Worker *mgr_ptr,
                               const Worker *assignee_ptr)
    : assignment_id(id), estimated_hours(hours), project_ref_(p_ptr),
      manager_ref_(mgr_ptr), assignee_ref_(assignee_ptr) {
  std::strncpy(task_title, title_str, sizeof(task_title) - 1);
  task_title[sizeof(task_title) - 1] = '\0';
}

TaskAssignment::TaskAssignment(const TaskAssignment &other)
    : assignment_id(other.assignment_id),
      estimated_hours(other.estimated_hours), project_ref_(other.project_ref_),
      manager_ref_(other.manager_ref_), assignee_ref_(other.assignee_ref_) {
  std::strncpy(task_title, other.task_title, sizeof(task_title) - 1);
  task_title[sizeof(task_title) - 1] = '\0';
}

TaskAssignment::~TaskAssignment() {
  std::cout << "  [Destructor] Знищено об'єкт TaskAssignment #" << assignment_id
            << "\n";
}

void TaskAssignment::PrintInfo() const {
  std::cout << "==============================================================="
               "=========\n"
            << "  [Клас Асоціацій TaskAssignment #" << assignment_id
            << "] Таск: " << task_title << "\n"
            << "  Оцінка часу: " << estimated_hours << " годин\n";
  if (project_ref_ != nullptr) {
    std::cout << "  --> Проєкт: " << project_ref_->title << " (ID: #"
              << project_ref_->project_id << ")\n";
  }
  if (manager_ref_ != nullptr) {
    std::cout << "  --> Менеджер/Призначав: " << manager_ref_->name << " ("
              << manager_ref_->role << ")\n";
  }
  if (assignee_ref_ != nullptr) {
    std::cout << "  --> Виконавець: " << assignee_ref_->name << " ("
              << assignee_ref_->role << ")\n";
  }
  std::cout << "==============================================================="
               "=========\n";
}
