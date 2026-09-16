// Copyright 2026 Artem Lychak
// Lab 2 - Variant 9: Project Management System (Level 3)
// Conforms to Google C++ Style Guide

#ifndef LAB2_PROJECT_H_
#define LAB2_PROJECT_H_

#include <fstream>
#include <iostream>
#include <string>

// ============================================================================
// [Requirement 1, 2] Class 1: Worker (Робітник / Член команди)
// 8 fields: 3 public, 5 private
// ============================================================================
class Worker {
 public:
  // [Requirement 2] 3 Public fields
  int worker_id;
  char name[50];
  char role[30];

  // Constructors
  Worker();
  Worker(int id, const char* name_str, const char* role_str, double rate,
         int hours, int tasks, double budget, int rating);

  // [Requirement 4] 6 Methods for Worker class
  // Method 1: Calculate total salary
  double CalculateSalary() const;

  // Method 2: Overloaded update method (version 1)
  void UpdateTasks(int new_tasks);

  // Method 3: Overloaded update method (version 2)
  void UpdateTasks(int new_tasks, double added_budget);

  // Method 4: File output
  void WriteToFile(std::ofstream& file) const;

  // Method 5: File input
  void ReadFromFile(std::ifstream& file);

  // [Requirement 12] Method allocating random dynamic memory and sorting
  void AllocateAndSortTaskHours(int count);

  // Method 6: Print full info
  void PrintInfo() const;

  // Getters for private fields (used in object interaction)
  double get_allocated_budget() const { return allocated_budget_; }
  int get_performance_rating() const { return performance_rating_; }

 private:
  // [Requirement 2] 5 Private fields
  double hourly_rate_;
  int hours_worked_;
  int completed_tasks_;
  double allocated_budget_;
  int performance_rating_;  // Rating from 1 to 10
};

// ============================================================================
// [Requirement 1, 2, 3] Class 2: Project (Проєкт)
// 8 fields: 3 public, 5 private (includes Worker lead_worker object)
// ============================================================================
class Project {
 public:
  // [Requirement 2] 3 Public fields
  int project_id;
  char title[60];
  char status[20];  // "Planned", "In Progress", "Completed"

  // Constructors
  Project();
  Project(int id, const char* title_str, const char* status_str,
          double budget, double expenses, int team_sz, int duration);

  // [Requirement 4] 6 Methods for Project class
  // Method 1: [Requirement 4] Method accepting a class object as parameter
  void AssignLeadWorker(const Worker& lead);

  // Method 2: [Requirement 4] Method returning a class object
  Worker GetLeadWorker() const;

  // Method 3: Overloaded status/expense update (version 1)
  void UpdateStatus(const char* new_status);

  // Method 4: Overloaded status/expense update (version 2)
  void UpdateStatus(const char* new_status, double added_expense);

  // Method 5: File output
  void WriteToFile(std::ofstream& file) const;

  // Method 6: File input
  void ReadFromFile(std::ifstream& file);

  // [Requirement 12] Method allocating random dynamic memory and sorting
  void AllocateAndSortExpensesHistory(int count);

  // Print full project details
  void PrintInfo() const;

 private:
  // [Requirement 2, 3] 5 Private fields (including Worker lead_worker_)
  double total_budget_;
  double current_expenses_;
  int team_size_;
  Worker lead_worker_;  // [Requirement 3] Object composition without friend
  int duration_days_;
};

#endif  // LAB2_PROJECT_H_
