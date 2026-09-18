#ifndef LAB3_WORKER_H_
#define LAB3_WORKER_H_

#include <fstream>
#include <iostream>

// ============================================================================
// [Requirement 1, 2, 4] Class Worker
// Contains Default, Parameterized, Copy constructors, Copy Assignment operator,
// Destructor, Member initializer list with const member, Static member & method
// ============================================================================
class Worker {
public:
  // [Requirement 2] Public fields
  int worker_id;
  char name[50];
  char role[30];

  // [Requirement 4] Static field for tracking total worker instances
  static int total_workers_count;

  // [Requirement 1, 10] Constructors
  Worker();
  Worker(int id, const char *name_str, const char *role_str, double rate,
         int hours, int tasks, double budget, int rating);

  // [Requirement 1, 10] Copy Constructor
  Worker(const Worker &other);

  // Copy Assignment Operator
  Worker &operator=(const Worker &other);

  // [Requirement 3] Destructor with block entrance/exit tracking
  ~Worker();

  // [Requirement 4] Static member method
  static void PrintTotalWorkers();

  // Member methods
  double CalculateSalary() const;
  void UpdateTasks(int new_tasks);
  void UpdateTasks(int new_tasks, double added_budget);
  void WriteToFile(std::ofstream &file) const;
  void ReadFromFile(std::ifstream &file);
  void InputFromConsole();
  void AllocateAndSortTaskHours(int count);
  void PrintInfo() const;

  // Getters
  double get_allocated_budget() const { return allocated_budget_; }
  int get_performance_rating() const { return performance_rating_; }
  int get_creation_year() const { return creation_year_; }

private:
  // Private fields
  double hourly_rate_;
  int hours_worked_;
  int completed_tasks_;
  double allocated_budget_;
  int performance_rating_;

  // [Requirement 2] Constant member variable set via Member Initializer List
  const int creation_year_;
};

#endif // LAB3_WORKER_H_
