#ifndef LAB4_MANAGER_H_
#define LAB4_MANAGER_H_

#include <string>

#include "project.h"
#include "worker.h"

// [ЛР4, п.1, п.2] Manager — відкрите (public) наслідування від Worker:
// відкриті члени Worker залишаються відкритими, захищені — захищеними
class Manager : public Worker {
public:
  Manager();
  // [ЛР4, п.5] Перші 8 параметрів передаються конструктору базового класу
  // Worker у списку ініціалізації, решта — власним полям Manager
  Manager(int id, const char *name_str, const char *role_str, double rate,
          int hours, int tasks, double budget, int rating,
          const std::string &department, int management_level,
          double bonus_percent, double budget_authority,
          int years_of_experience);
  Manager(const Manager &other);
  ~Manager();

  double CalculateSalary() const;
  void AcceptProject(Project &project);
  void AssignTask(Worker &worker, int tasks, double task_budget);
  bool ApproveExpense(Project &project, double amount);
  void ShowInheritedAccess();
  void PrintInfo() const;

  const std::string &get_department() const { return department_; }
  double get_budget_authority() const { return budget_authority_; }
  double get_approved_expenses() const { return approved_expenses_; }

private:
  std::string department_;
  int management_level_;
  int managed_projects_count_;
  int assigned_tasks_count_;
  double bonus_percent_;
  double budget_authority_;
  double approved_expenses_;
  int years_of_experience_;
};

#endif // LAB4_MANAGER_H_
