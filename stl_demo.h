#ifndef LAB7_STL_DEMO_H_
#define LAB7_STL_DEMO_H_

#include <string>

#include "project_task.h"

// [ЛР7, п.4] Власний функціональний об'єкт: приховує в об'єкті умову «задача
// належить виконавцю», щоб її могли використовувати інші компоненти —
// алгоритми (count_if, find_if) і методи контейнерів (list::remove_if)
class AssignedTo {
public:
  explicit AssignedTo(const std::string &assignee) : assignee_(assignee) {}
  bool operator()(const ProjectTask &task) const {
    return task.get_assignee() == assignee_;
  }

private:
  std::string assignee_;
};

// [ЛР7] Демонстрація бібліотеки STL: контейнери, ітератори, алгоритми та
// функціональні об'єкти
void RunLab7Demo();

#endif // LAB7_STL_DEMO_H_
