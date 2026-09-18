#include "project.h"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

// [Requirement 4] Definition of static member variable
int Project::total_projects_count = 0;

// [Requirement 1, 2, 10] Default Constructor
Project::Project()
    : project_id(0), total_budget_(0.0), current_expenses_(0.0), team_size_(0),
      lead_worker_agg_ptr_(nullptr), duration_days_(0), creation_year_(2026) {
  std::strncpy(title, "Untitled Project", sizeof(title) - 1);
  title[sizeof(title) - 1] = '\0';
  std::strncpy(status, "Planned", sizeof(status) - 1);
  status[sizeof(status) - 1] = '\0';
  total_projects_count++;
}

// [Requirement 1, 2, 10] Parameterized Constructor (uses Initializer List for
// const member)
Project::Project(int id, const char *title_str, const char *status_str,
                 double budget, double expenses, int team_sz, int duration)
    : project_id(id), total_budget_(budget), current_expenses_(expenses),
      team_size_(team_sz), lead_worker_agg_ptr_(nullptr),
      duration_days_(duration), creation_year_(2026) {
  std::strncpy(title, title_str, sizeof(title) - 1);
  title[sizeof(title) - 1] = '\0';
  std::strncpy(status, status_str, sizeof(status) - 1);
  status[sizeof(status) - 1] = '\0';
  total_projects_count++;
}

// [Requirement 1, 10] Copy Constructor
Project::Project(const Project &other)
    : project_id(other.project_id), total_budget_(other.total_budget_),
      current_expenses_(other.current_expenses_), team_size_(other.team_size_),
      lead_worker_comp_(other.lead_worker_comp_),
      lead_worker_agg_ptr_(other.lead_worker_agg_ptr_),
      duration_days_(other.duration_days_),
      creation_year_(other.creation_year_) {
  std::strncpy(title, other.title, sizeof(title) - 1);
  title[sizeof(title) - 1] = '\0';
  std::strncpy(status, other.status, sizeof(status) - 1);
  status[sizeof(status) - 1] = '\0';
  total_projects_count++;
  std::cout << "  [Copy Constructor] Створено копію проєкту: " << title << "\n";
}

// Copy Assignment Operator
Project &Project::operator=(const Project &other) {
  if (this != &other) {
    project_id = other.project_id;
    std::strncpy(title, other.title, sizeof(title) - 1);
    title[sizeof(title) - 1] = '\0';
    std::strncpy(status, other.status, sizeof(status) - 1);
    status[sizeof(status) - 1] = '\0';
    total_budget_ = other.total_budget_;
    current_expenses_ = other.current_expenses_;
    team_size_ = other.team_size_;
    lead_worker_comp_ = other.lead_worker_comp_;
    lead_worker_agg_ptr_ = other.lead_worker_agg_ptr_;
    duration_days_ = other.duration_days_;
    // creation_year_ is const, so it retains its constant value
  }
  return *this;
}

// [Requirement 3] Destructor with block tracking
Project::~Project() {
  total_projects_count--;
  std::cout << "  [Destructor] Знищено об'єкт Project #" << project_id << " ("
            << title << ")\n";
}

// [Requirement 4] Static Member Method
void Project::PrintTotalProjects() {
  std::cout << "  [Static Method Project::PrintTotalProjects] Поточна "
               "кількість проєктів у пам'яті: "
            << total_projects_count << "\n";
}

// [Requirement 13] Composition Assignment (embedded value)
void Project::AssignLeadWorkerComposition(const Worker &lead) {
  lead_worker_comp_ = lead;
  std::cout << "[Composition] Тимлідом (Композиція) проєкту '" << title
            << "' призначено: " << lead.name << " (" << lead.role << ")\n";
}

// [Requirement 12] Aggregation Assignment (pointer to independent external
// object)
void Project::AssignLeadWorkerAggregation(Worker *lead_ptr) {
  lead_worker_agg_ptr_ = lead_ptr;
  if (lead_ptr != nullptr) {
    std::cout << "[Aggregation] Тимлідом (Агрегація) проєкту '" << title
              << "' призначено: " << lead_ptr->name << " (" << lead_ptr->role
              << ")\n";
  }
}

Worker Project::GetLeadWorkerComposition() const { return lead_worker_comp_; }

void Project::UpdateStatus(const char *new_status) {
  std::strncpy(status, new_status, sizeof(status) - 1);
  status[sizeof(status) - 1] = '\0';
}

void Project::UpdateStatus(const char *new_status, double added_expense) {
  std::strncpy(status, new_status, sizeof(status) - 1);
  status[sizeof(status) - 1] = '\0';
  current_expenses_ += added_expense;
}

void Project::WriteToFile(std::ofstream &file) const {
  if (!file.is_open())
    return;
  file << project_id << "\n"
       << title << "\n"
       << status << "\n"
       << total_budget_ << " " << current_expenses_ << " " << team_size_ << " "
       << duration_days_ << "\n";
  lead_worker_comp_.WriteToFile(file);
}

void Project::ReadFromFile(std::ifstream &file) {
  if (!file.is_open())
    return;
  file >> project_id;
  file.ignore();
  file.getline(title, sizeof(title));
  file.getline(status, sizeof(status));
  file >> total_budget_ >> current_expenses_ >> team_size_ >> duration_days_;
  lead_worker_comp_.ReadFromFile(file);
}

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
  lead_worker_comp_.InputFromConsole();
}

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

void Project::PrintInfo() const {
  std::cout << "==============================================================="
               "=========\n"
            << "  [Проєкт #" << project_id << "] " << title << "\n"
            << "  Статус: " << status << " | Тривалість: " << duration_days_
            << " днів | Рік створення: " << creation_year_ << "\n"
            << "  Загальний бюджет: $" << total_budget_
            << " | Поточні витрати: $" << current_expenses_ << " | Баланс: $"
            << (total_budget_ - current_expenses_) << "\n"
            << "  Команда: " << team_size_ << " робітників\n"
            << "  [Композиція] Тимлід вкладений у проєкт:\n";
  lead_worker_comp_.PrintInfo();
  if (lead_worker_agg_ptr_ != nullptr) {
    std::cout << "  [Агрегація] Тимлід через вказівник на зовнішній об'єкт:\n";
    lead_worker_agg_ptr_->PrintInfo();
  }
  std::cout << "==============================================================="
               "=========\n";
}
