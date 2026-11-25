#ifndef LAB7_PROJECT_TASK_H_
#define LAB7_PROJECT_TASK_H_

#include <iostream>
#include <string>

// [ЛР7, п.1] ProjectTask — задача проєкту, яка зберігається в контейнерах STL.
// operator< (за пріоритетом) потрібен для priority_queue та сортування,
// operator== (за номером) — для list::remove та алгоритмів пошуку
class ProjectTask {
public:
  ProjectTask();
  ProjectTask(int id, const std::string &title, const std::string &assignee,
              int priority, int hours);

  bool operator<(const ProjectTask &other) const;
  bool operator==(const ProjectTask &other) const;

  friend std::ostream &operator<<(std::ostream &os, const ProjectTask &task);

  int get_id() const { return id_; }
  const std::string &get_title() const { return title_; }
  const std::string &get_assignee() const { return assignee_; }
  int get_priority() const { return priority_; }
  int get_hours() const { return hours_; }

private:
  int id_;
  std::string title_;
  std::string assignee_;
  int priority_;
  int hours_;
};

#endif // LAB7_PROJECT_TASK_H_
