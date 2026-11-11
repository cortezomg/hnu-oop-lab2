#include "manager.h"

#include <iostream>
#include <string>

Manager::Manager()
    : Worker(), department_("None"), management_level_(1),
      managed_projects_count_(0), assigned_tasks_count_(0),
      bonus_percent_(0.0), budget_authority_(0.0), approved_expenses_(0.0),
      years_of_experience_(0) {
  std::cout << "  [Constructor] Створено об'єкт Manager #" << worker_id
            << "\n";
}

// [ЛР4, п.5] Передача параметрів конструктору базового класу Worker
Manager::Manager(int id, const char *name_str, const char *role_str,
                 double rate, int hours, int tasks, double budget, int rating,
                 const std::string &department, int management_level,
                 double bonus_percent, double budget_authority,
                 int years_of_experience)
    : Worker(id, name_str, role_str, rate, hours, tasks, budget, rating),
      department_(department), management_level_(management_level),
      managed_projects_count_(0), assigned_tasks_count_(0),
      bonus_percent_(bonus_percent), budget_authority_(budget_authority),
      approved_expenses_(0.0), years_of_experience_(years_of_experience) {
  std::cout << "  [Constructor] Створено об'єкт Manager #" << worker_id << " ("
            << name << ")\n";
}

Manager::Manager(const Manager &other)
    : Worker(other), department_(other.department_),
      management_level_(other.management_level_),
      managed_projects_count_(other.managed_projects_count_),
      assigned_tasks_count_(other.assigned_tasks_count_),
      bonus_percent_(other.bonus_percent_),
      budget_authority_(other.budget_authority_),
      approved_expenses_(other.approved_expenses_),
      years_of_experience_(other.years_of_experience_) {
  std::cout << "  [Copy Constructor] Створено копію менеджера: " << name
            << "\n";
}

Manager::~Manager() {
  std::cout << "  [Destructor] Знищено об'єкт Manager #" << worker_id << " ("
            << name << ")\n";
}

// [ЛР4, п.6] Доступ до прихованого методу базового класу через Worker::
double Manager::CalculateSalary() const {
  double base_salary = Worker::CalculateSalary();
  return base_salary + base_salary * bonus_percent_ / 100.0;
}

void Manager::AcceptProject(Project &project) {
  project.UpdateStatus("In Progress");
  managed_projects_count_++;
  std::cout << "  [Manager] Проєкт '" << project.title
            << "' прийнято в роботу (менеджер: " << name << ")\n";
}

void Manager::AssignTask(Worker &worker, int tasks, double task_budget) {
  worker.UpdateTasks(tasks, task_budget);
  assigned_tasks_count_ += tasks;
  std::cout << "  [Manager] " << name << " -> " << worker.name
            << ": призначено завдань: " << tasks << ", бюджет на завдання: $"
            << task_budget << "\n";
}

bool Manager::ApproveExpense(Project &project, double amount) {
  if (approved_expenses_ + amount > budget_authority_) {
    std::cout << "  [Manager] Витрату $" << amount
              << " відхилено: перевищено ліміт повноважень $"
              << budget_authority_ << "\n";
    return false;
  }
  std::string current_status = project.status;
  project.UpdateStatus(current_status.c_str(), amount);
  approved_expenses_ += amount;
  std::cout << "  [Manager] Затверджено витрату $" << amount
            << " для проєкту '" << project.title << "'\n";
  return true;
}

// [ЛР4, п.2] Доступ до членів Worker зсередини класу при public-наслідуванні
void Manager::ShowInheritedAccess() {
  std::cout << "  [Manager, public] Дані: worker_id=" << worker_id
            << ", name=" << name << ", role=" << role
            << " | захищені: hourly_rate_=" << hourly_rate_
            << ", hours_worked_=" << hours_worked_
            << ", completed_tasks_=" << completed_tasks_ << "\n";
  UpdateTasks(0);
  std::cout << "  [Manager, public] Методи: Worker::CalculateSalary()=$"
            << Worker::CalculateSalary() << ", Worker::PrintInfo():\n";
  Worker::PrintInfo();
}

// [ЛР4, п.6] Виклик методу базового класу через оператор Worker::
void Manager::PrintInfo() const {
  Worker::PrintInfo();
  std::cout << "    [Менеджер] Відділ: " << department_
            << " | Рівень: " << management_level_
            << " | Проєктів: " << managed_projects_count_
            << " | Призначено завдань: " << assigned_tasks_count_
            << " | Бонус: " << bonus_percent_ << "% | Ліміт бюджету: $"
            << budget_authority_ << " | Затверджено: $" << approved_expenses_
            << " | Досвід: " << years_of_experience_
            << " р. | Зарплата з бонусом: $" << CalculateSalary() << "\n";
}
