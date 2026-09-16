#include "project.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

// Implementation of Class Worker

Worker::Worker()
    : worker_id(0), hourly_rate_(0.0), hours_worked_(0), completed_tasks_(0),
      allocated_budget_(0.0), performance_rating_(0) {
  std::strncpy(name, "Undefined", sizeof(name) - 1);
  name[sizeof(name) - 1] = '\0';
  std::strncpy(role, "None", sizeof(role) - 1);
  role[sizeof(role) - 1] = '\0';
}

Worker::Worker(int id, const char *name_str, const char *role_str, double rate,
               int hours, int tasks, double budget, int rating)
    : worker_id(id), hourly_rate_(rate), hours_worked_(hours),
      completed_tasks_(tasks), allocated_budget_(budget),
      performance_rating_(rating) {
  std::strncpy(name, name_str, sizeof(name) - 1);
  name[sizeof(name) - 1] = '\0';
  std::strncpy(role, role_str, sizeof(role) - 1);
  role[sizeof(role) - 1] = '\0';
}

// [Requirement 4] Method 1: Calculate total salary
double Worker::CalculateSalary() const { return hourly_rate_ * hours_worked_; }

// [Requirement 4] Method 2: Overloaded method version 1
void Worker::UpdateTasks(int new_tasks) {
  completed_tasks_ += new_tasks;
  hours_worked_ += new_tasks * 8; // Assume 8 hours per task
}

// [Requirement 4] Method 3: Overloaded method version 2
void Worker::UpdateTasks(int new_tasks, double added_budget) {
  completed_tasks_ += new_tasks;
  hours_worked_ += new_tasks * 8;
  allocated_budget_ += added_budget;
}

// [Requirement 5] Method 4: Write Worker data to text file stream
void Worker::WriteToFile(std::ofstream &file) const {
  if (!file.is_open())
    return;
  file << worker_id << "\n"
       << name << "\n"
       << role << "\n"
       << hourly_rate_ << " " << hours_worked_ << " " << completed_tasks_ << " "
       << allocated_budget_ << " " << performance_rating_ << "\n";
}

// [Requirement 5] Method 5: Read Worker data from text file stream
void Worker::ReadFromFile(std::ifstream &file) {
  if (!file.is_open())
    return;
  file >> worker_id;
  file.ignore();
  file.getline(name, sizeof(name));
  file.getline(role, sizeof(role));
  file >> hourly_rate_ >> hours_worked_ >> completed_tasks_ >>
      allocated_budget_ >> performance_rating_;
}

// Manual console input method for Worker
void Worker::InputFromConsole() {
  std::cout << "\n--- Ручне введення даних про робітника ---\n";
  std::cout << "Введіть ID робітника: ";
  std::cin >> worker_id;
  std::cin.ignore();
  std::cout << "Прізвище та ім'я: ";
  std::cin.getline(name, sizeof(name));
  std::cout << "Посада (наприклад, Lead Developer): ";
  std::cin.getline(role, sizeof(role));
  std::cout << "Годинна ставка ($): ";
  std::cin >> hourly_rate_;
  std::cout << "Відпрацьовано годин: ";
  std::cin >> hours_worked_;
  std::cout << "Виконано тасків: ";
  std::cin >> completed_tasks_;
  std::cout << "Виділений бюджет ($): ";
  std::cin >> allocated_budget_;
  std::cout << "Рейтинг продуктивності (1-10): ";
  std::cin >> performance_rating_;
}

// [Requirement 12] Method allocating random dynamic memory and sorting array
void Worker::AllocateAndSortTaskHours(int count) {
  if (count <= 0)
    return;

  int *task_hours = new int[count];

  for (int i = 0; i < count; ++i) {
    task_hours[i] = (rand() % 40) + 1;
  }

  std::cout << "[Worker::AllocateAndSortTaskHours] Згенеровано масив годин ("
            << count << " елементів):\n  Перед сортуванням: ";
  for (int i = 0; i < count; ++i) {
    std::cout << task_hours[i] << " ";
  }

  for (int i = 0; i < count - 1; ++i) {
    for (int j = 0; j < count - i - 1; ++j) {
      if (task_hours[j] > task_hours[j + 1]) {
        int temp = task_hours[j];
        task_hours[j] = task_hours[j + 1];
        task_hours[j + 1] = temp;
      }
    }
  }

  std::cout << "\n  Після сортування: ";
  for (int i = 0; i < count; ++i) {
    std::cout << task_hours[i] << " ";
  }
  std::cout << "\n";

  delete[] task_hours;
}

// Method 6: Print complete Worker info
void Worker::PrintInfo() const {
  std::cout << "  [Робітник #" << worker_id << "] " << name
            << " | Посада: " << role << " | Ставка: $" << hourly_rate_
            << "/год | Годин: " << hours_worked_
            << " | Виконано тасків: " << completed_tasks_ << " | Бюджет: $"
            << allocated_budget_ << " | Рейтинг: " << performance_rating_
            << "/10"
            << " | Зарплата: $" << CalculateSalary() << "\n";
}

// Implementation of Class Project

Project::Project()
    : project_id(0), total_budget_(0.0), current_expenses_(0.0), team_size_(0),
      duration_days_(0) {
  std::strncpy(title, "Untitled Project", sizeof(title) - 1);
  title[sizeof(title) - 1] = '\0';
  std::strncpy(status, "Planned", sizeof(status) - 1);
  status[sizeof(status) - 1] = '\0';
}

Project::Project(int id, const char *title_str, const char *status_str,
                 double budget, double expenses, int team_sz, int duration)
    : project_id(id), total_budget_(budget), current_expenses_(expenses),
      team_size_(team_sz), duration_days_(duration) {
  std::strncpy(title, title_str, sizeof(title) - 1);
  title[sizeof(title) - 1] = '\0';
  std::strncpy(status, status_str, sizeof(status) - 1);
  status[sizeof(status) - 1] = '\0';
}

// [Requirement 4] Method 1: Method accepting a class object as parameter
void Project::AssignLeadWorker(const Worker &lead) {
  lead_worker_ = lead;
  std::cout << "[Project::AssignLeadWorker] Тимлідом проєкту '" << title
            << "' призначено: " << lead.name << " (" << lead.role << ")\n";
}

// [Requirement 4] Method 2: Method returning a class object
Worker Project::GetLeadWorker() const { return lead_worker_; }

// [Requirement 4] Method 3: Overloaded method version 1
void Project::UpdateStatus(const char *new_status) {
  std::strncpy(status, new_status, sizeof(status) - 1);
  status[sizeof(status) - 1] = '\0';
}

// [Requirement 4] Method 4: Overloaded method version 2
void Project::UpdateStatus(const char *new_status, double added_expense) {
  std::strncpy(status, new_status, sizeof(status) - 1);
  status[sizeof(status) - 1] = '\0';
  current_expenses_ += added_expense;
}

// [Requirement 5] Method 5: Write Project data to text file stream
void Project::WriteToFile(std::ofstream &file) const {
  if (!file.is_open())
    return;
  file << project_id << "\n"
       << title << "\n"
       << status << "\n"
       << total_budget_ << " " << current_expenses_ << " " << team_size_ << " "
       << duration_days_ << "\n";
  lead_worker_.WriteToFile(file);
}

// [Requirement 5] Method 6: Read Project data from text file stream
void Project::ReadFromFile(std::ifstream &file) {
  if (!file.is_open())
    return;
  file >> project_id;
  file.ignore();
  file.getline(title, sizeof(title));
  file.getline(status, sizeof(status));
  file >> total_budget_ >> current_expenses_ >> team_size_ >> duration_days_;
  lead_worker_.ReadFromFile(file);
}

// Manual console input method for Project
void Project::InputFromConsole() {
  std::cout << "\n--- Ручне введення даних про проєкт ---\n";
  std::cout << "Введіть ID проєкту: ";
  std::cin >> project_id;
  std::cin.ignore();
  std::cout << "Назва проєкту: ";
  std::cin.getline(title, sizeof(title));
  std::cout << "Статус (\"Planned\", \"In Progress\", \"Completed\"): ";
  std::cin.getline(status, sizeof(status));
  std::cout << "Загальний бюджет ($): ";
  std::cin >> total_budget_;
  std::cout << "Поточні витрати ($): ";
  std::cin >> current_expenses_;
  std::cout << "Кількість робітників у команді: ";
  std::cin >> team_size_;
  std::cout << "Тривалість проєкту (днів): ";
  std::cin >> duration_days_;

  std::cout << "\n--- Введення даних для тимліда цього проєкту ---\n";
  lead_worker_.InputFromConsole();
}

// [Requirement 12] Method allocating random dynamic memory and sorting array
void Project::AllocateAndSortExpensesHistory(int count) {
  if (count <= 0)
    return;

  int *expenses_history = new int[count];

  for (int i = 0; i < count; ++i) {
    expenses_history[i] = (rand() % 4900) + 100;
  }

  std::cout << "[Project::AllocateAndSortExpensesHistory] Згенеровано історію "
               "витрат ("
            << count << " елементів):\n  Перед сортуванням: ";
  for (int i = 0; i < count; ++i) {
    std::cout << "$" << expenses_history[i] << " ";
  }

  for (int i = 0; i < count - 1; ++i) {
    for (int j = 0; j < count - i - 1; ++j) {
      if (expenses_history[j] > expenses_history[j + 1]) {
        int temp = expenses_history[j];
        expenses_history[j] = expenses_history[j + 1];
        expenses_history[j + 1] = temp;
      }
    }
  }

  std::cout << "\n  Після сортування: ";
  for (int i = 0; i < count; ++i) {
    std::cout << "$" << expenses_history[i] << " ";
  }
  std::cout << "\n";

  delete[] expenses_history;
}

// Print complete Project info
void Project::PrintInfo() const {
  std::cout << "==============================================================="
               "=========\n"
            << "  [Проєкт #" << project_id << "] " << title << "\n"
            << "  Статус: " << status << " | Тривалість: " << duration_days_
            << " днів\n"
            << "  Загальний бюджет: $" << total_budget_
            << " | Поточні витрати: $" << current_expenses_ << " | Баланс: $"
            << (total_budget_ - current_expenses_) << "\n"
            << "  Команда: " << team_size_ << " робітників\n"
            << "  Тимлід проєкту:\n";
  lead_worker_.PrintInfo();
  std::cout << "==============================================================="
               "=========\n";
}
