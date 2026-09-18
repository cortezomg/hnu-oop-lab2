#ifndef LAB3_ASSIGNMENT_H_
#define LAB3_ASSIGNMENT_H_
#include "project.h"
#include "worker.h"
#include <iostream>
#include <string>

// ============================================================================
// [Requirement 11] Association Class: TaskAssignment (Клас асоціацій)
// Demonstrates scenario of interaction between 3 objects:
// 1. Project (Проєкт)
// 2. Worker (Менеджер / Задач віддавець)
// 3. Worker (Виконавець)
// ============================================================================
class TaskAssignment {
public:
  int assignment_id;
  char task_title[100];
  int estimated_hours;

  // [Requirement 1, 10] Constructors
  TaskAssignment();
  TaskAssignment(int id, const char *title_str, int hours, const Project *p_ptr,
                 const Worker *mgr_ptr, const Worker *assignee_ptr);

  // Copy Constructor
  TaskAssignment(const TaskAssignment &other);

  // Destructor
  ~TaskAssignment();

  // Print association details connecting all 3 objects
  void PrintInfo() const;

private:
  // [Requirement 11] Pointers connecting 3 objects via Association Class
  const Project *project_ref_;
  const Worker *manager_ref_;
  const Worker *assignee_ref_;
};

#endif // LAB3_ASSIGNMENT_H_
