#ifndef LAB3_PROJECT_H_
#define LAB3_PROJECT_H_

#include "worker.h"
#include <fstream>
#include <iostream>
#include <string>

// ============================================================================
// [Requirement 1, 2, 3, 4, 12, 13] Class Project
// Demonstrates Composition (lead_worker_comp_) vs Aggregation
// (lead_worker_agg_ptr_)
// ============================================================================
class Project {
public:
  // [Requirement 2] Public fields
  int project_id;
  char title[60];
  char status[20];

  // [Requirement 4] Static member variable
  static int total_projects_count;

  // [Requirement 1, 10] Constructors
  Project();
  Project(int id, const char *title_str, const char *status_str, double budget,
          double expenses, int team_sz, int duration);

  // [Requirement 1, 10] Copy Constructor
  Project(const Project &other);

  // Copy Assignment Operator
  Project &operator=(const Project &other);

  // [Requirement 3] Destructor with block tracking
  ~Project();

  // [Requirement 4] Static member method
  static void PrintTotalProjects();

  // [Requirement 13] Composition scenario (object embedded by value)
  void AssignLeadWorkerComposition(const Worker &lead);

  // [Requirement 12] Aggregation scenario (pointer to independent object)
  void AssignLeadWorkerAggregation(Worker *lead_ptr);

  // Method returning class object
  Worker GetLeadWorkerComposition() const;

  // Overloaded status update methods
  void UpdateStatus(const char *new_status);
  void UpdateStatus(const char *new_status, double added_expense);

  // File I/O
  void WriteToFile(std::ofstream &file) const;
  void ReadFromFile(std::ifstream &file);

  void InputFromConsole();
  void AllocateAndSortExpensesHistory(int count);
  void PrintInfo() const;

  // Getters
  double get_total_budget() const { return total_budget_; }
  double get_current_expenses() const { return current_expenses_; }

private:
  // Private fields
  double total_budget_;
  double current_expenses_;
  int team_size_;

  // [Requirement 13] Composition (lifetime tied to Project)
  Worker lead_worker_comp_;

  // [Requirement 12] Aggregation (pointer to independent external Worker)
  Worker *lead_worker_agg_ptr_;

  int duration_days_;

  // [Requirement 2] Constant member variable set via Member Initializer List
  const int creation_year_;
};

#endif // LAB3_PROJECT_H_
