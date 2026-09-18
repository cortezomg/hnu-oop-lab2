#include "worker.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

// [Requirement 4] Definition of static member variable
int Worker::total_workers_count = 0;

// [Requirement 1, 2, 10] Default Constructor (uses Initializer List)
Worker::Worker()
    : worker_id(0), hourly_rate_(0.0), hours_worked_(0), completed_tasks_(0),
      allocated_budget_(0.0), performance_rating_(0), creation_year_(2026) {
  std::strncpy(name, "Undefined", sizeof(name) - 1);
  name[sizeof(name) - 1] = '\0';
  std::strncpy(role, "None", sizeof(role) - 1);
  role[sizeof(role) - 1] = '\0';
  total_workers_count++;
}

// [Requirement 1, 2, 10] Parameterized Constructor (uses Initializer List for
// const member)
Worker::Worker(int id, const char *name_str, const char *role_str, double rate,
               int hours, int tasks, double budget, int rating)
    : worker_id(id), hourly_rate_(rate), hours_worked_(hours),
      completed_tasks_(tasks), allocated_budget_(budget),
      performance_rating_(rating), creation_year_(2026) {
  std::strncpy(name, name_str, sizeof(name) - 1);
  name[sizeof(name) - 1] = '\0';
  std::strncpy(role, role_str, sizeof(role) - 1);
  role[sizeof(role) - 1] = '\0';
  total_workers_count++;
}

// [Requirement 1, 10] Copy Constructor
Worker::Worker(const Worker &other)
    : worker_id(other.worker_id), hourly_rate_(other.hourly_rate_),
      hours_worked_(other.hours_worked_),
      completed_tasks_(other.completed_tasks_),
      allocated_budget_(other.allocated_budget_),
      performance_rating_(other.performance_rating_),
      creation_year_(other.creation_year_) {
  std::strncpy(name, other.name, sizeof(name) - 1);
  name[sizeof(name) - 1] = '\0';
  std::strncpy(role, other.role, sizeof(role) - 1);
  role[sizeof(role) - 1] = '\0';
  total_workers_count++;
  std::cout << "  [Copy Constructor] Створено копію робітника: " << name
            << "\n";
}

// Copy Assignment Operator
Worker &Worker::operator=(const Worker &other) {
  if (this != &other) {
    worker_id = other.worker_id;
    std::strncpy(name, other.name, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
    std::strncpy(role, other.role, sizeof(role) - 1);
    role[sizeof(role) - 1] = '\0';
    hourly_rate_ = other.hourly_rate_;
    hours_worked_ = other.hours_worked_;
    completed_tasks_ = other.completed_tasks_;
    allocated_budget_ = other.allocated_budget_;
    performance_rating_ = other.performance_rating_;
    // creation_year_ is const, so it retains its constant value
  }
  return *this;
}

// [Requirement 3] Destructor with block tracking
Worker::~Worker() {
  total_workers_count--;
  std::cout << "  [Destructor] Знищено об'єкт Worker #" << worker_id << " ("
            << name << ")\n";
}

// [Requirement 4] Static Member Method
void Worker::PrintTotalWorkers() {
  std::cout << "  [Static Method Worker::PrintTotalWorkers] Поточна кількість "
               "робітників у пам'яті: "
            << total_workers_count << "\n";
}

double Worker::CalculateSalary() const { return hourly_rate_ * hours_worked_; }

void Worker::UpdateTasks(int new_tasks) {
  completed_tasks_ += new_tasks;
  hours_worked_ += new_tasks * 8;
}

void Worker::UpdateTasks(int new_tasks, double added_budget) {
  completed_tasks_ += new_tasks;
  hours_worked_ += new_tasks * 8;
  allocated_budget_ += added_budget;
}

void Worker::WriteToFile(std::ofstream &file) const {
  if (!file.is_open())
    return;
  file << worker_id << "\n"
       << name << "\n"
       << role << "\n"
       << hourly_rate_ << " " << hours_worked_ << " " << completed_tasks_ << " "
       << allocated_budget_ << " " << performance_rating_ << "\n";
}

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

void Worker::InputFromConsole() {
  std::cout << "\n--- Ручне введення даних про робітника ---\n";
  std::cout << "Введіть ID робітника: ";
  std::cin >> worker_id;
  std::cin.ignore();
  std::cout << "Прізвище та ім'я: ";
  std::cin.getline(name, sizeof(name));
  std::cout << "Посада: ";
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

void Worker::PrintInfo() const {
  std::cout << "  [Робітник #" << worker_id << "] " << name
            << " | Посада: " << role << " | Ставка: $" << hourly_rate_
            << "/год | Годин: " << hours_worked_
            << " | Виконано тасків: " << completed_tasks_ << " | Бюджет: $"
            << allocated_budget_ << " | Рейтинг: " << performance_rating_
            << "/10 | Рік створення: " << creation_year_ << " | Зарплата: $"
            << CalculateSalary() << "\n";
}
