// Copyright 2026 Artem Lychak
// Lab 2 - Variant 9: Project Management System (Level 3)
// Conforms to Google C++ Style Guide

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include "project.h"

int main() {
  std::setlocale(LC_ALL, "");
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  std::cout << "========================================================================\n";
  std::cout << "        ЛАБОРАТОРНА РОБОТА №2 - ВАРІАНТ 9 (МЕНЕДЖМЕНТ ПРОЄКТУ)          \n";
  std::cout << "========================================================================\n\n";

  // ==========================================================================
  // [Пункт 5] Побудова 5 об'єктів у статичній пам'яті та 5 у динамічній пам'яті
  // ==========================================================================
  std::cout << ">>> [Пункт 5] Створення 5 об'єктів у статичній та 5 у динамічній пам'яті...\n";

  // 5 об'єктів у статичній пам'яті (статична пам'ять / стек)
  Worker w_stat1(101, "Олександр Коваленко", "Lead Developer", 45.0, 160, 20, 5000.0, 9);
  Worker w_stat2(102, "Марія Мельник", "QA Automation", 30.0, 150, 15, 3000.0, 8);
  Worker w_stat3(103, "Дмитро Шевченко", "DevOps Engineer", 40.0, 140, 12, 4500.0, 9);
  Worker w_stat4(104, "Анна Бойко", "UI/UX Designer", 35.0, 130, 10, 2500.0, 7);
  Worker w_stat5(105, "Іван Ткаченко", "Backend Developer", 38.0, 155, 18, 4000.0, 8);

  // 5 об'єктів у динамічній пам'яті (куча / heap через operator new)
  Project* p_dyn1 = new Project(1, "E-Commerce Platform", "In Progress", 50000.0, 12000.0, 8, 90);
  Project* p_dyn2 = new Project(2, "Mobile Banking App", "Planned", 80000.0, 5000.0, 12, 120);
  Project* p_dyn3 = new Project(3, "CRM System Integration", "In Progress", 35000.0, 18000.0, 6, 60);
  Project* p_dyn4 = new Project(4, "AI Analytics Dashboard", "Planned", 60000.0, 0.0, 5, 75);
  Project* p_dyn5 = new Project(5, "Cloud Infrastructure Migration", "Completed", 45000.0, 44000.0, 7, 45);

  std::cout << "Успішно створено 5 статичних робітників та 5 динамічних проєктів.\n\n";

  // ==========================================================================
  // [Пункт 6 & 7] Створення 2 масивів об'єктів та демонстрація роботи з ними
  // ==========================================================================
  std::cout << ">>> [Пункт 6 & 7] Створення 2 масивів об'єктів та робота з ними...\n";

  // Масив 1: Масив об'єктів Worker (5 елементів)
  Worker worker_array[5] = {w_stat1, w_stat2, w_stat3, w_stat4, w_stat5};

  // Масив 2: Масив об'єктів Project (5 елементів)
  Project project_array[5] = {*p_dyn1, *p_dyn2, *p_dyn3, *p_dyn4, *p_dyn5};

  std::cout << "\n--- Вміст Масиву 1 (Робітники) ---\n";
  for (int i = 0; i < 5; ++i) {
    worker_array[i].PrintInfo();
  }

  std::cout << "\n--- Робота з об'єктами в Масиві 1: Оновлення виконаних завдань ---\n";
  for (int i = 0; i < 5; ++i) {
    worker_array[i].UpdateTasks(2, 500.0);  // Викликаємо перевантажений метод
  }
  std::cout << "Після оновлення масиву робітників:\n";
  for (int i = 0; i < 5; ++i) {
    worker_array[i].PrintInfo();
  }

  // ==========================================================================
  // [Пункт 3 & 10] Сценарій взаємодії двох об'єктів
  // (Призначення робітників тимлідами для проєктів)
  // ==========================================================================
  std::cout << "\n>>> [Пункт 3 & 10] Демонстрація сценарію взаємодії двох об'єктів...\n";

  // Призначаємо робітників з worker_array як тимлідів для проєктів у project_array
  for (int i = 0; i < 5; ++i) {
    project_array[i].AssignLeadWorker(worker_array[i]);
  }

  std::cout << "\n--- Інформація про проєкти після призначення тимлідів ---\n";
  for (int i = 0; i < 5; ++i) {
    project_array[i].PrintInfo();
  }

  // ==========================================================================
  // [Пункт 8 & 9] Демонстрація роботи УСІХ методів класів
  // ==========================================================================
  std::cout << "\n>>> [Пункт 8 & 9] Демонстрація всіх методів класів Worker та Project...\n";

  std::cout << "\n1. Демонстрація методів Worker:\n";
  std::cout << "   - CalculateSalary(): $" << w_stat1.CalculateSalary() << "\n";
  
  std::cout << "   - Перевантажений UpdateTasks(5):\n";
  w_stat1.UpdateTasks(5);
  w_stat1.PrintInfo();

  std::cout << "   - Перевантажений UpdateTasks(3, 1200.0):\n";
  w_stat1.UpdateTasks(3, 1200.0);
  w_stat1.PrintInfo();

  std::cout << "\n2. Демонстрація методів Project:\n";
  std::cout << "   - GetLeadWorker() (повертає об'єкт): ";
  Worker current_lead = project_array[0].GetLeadWorker();
  std::cout << current_lead.name << " (" << current_lead.role << ")\n";

  std::cout << "   - Перевантажений UpdateStatus(\"Testing\"):\n";
  project_array[0].UpdateStatus("Testing");

  std::cout << "   - Перевантажений UpdateStatus(\"Completed\", 3500.0):\n";
  project_array[0].UpdateStatus("Completed", 3500.0);
  project_array[0].PrintInfo();

  // ==========================================================================
  // [Пункт 11] Демонстрація використання покажчика на екземпляр класу
  // ==========================================================================
  std::cout << "\n>>> [Пункт 11] Демонстрація використання покажчика на екземпляр класу...\n";

  Worker* ptr_worker = &w_stat3;
  std::cout << "Покажчик ptr_worker вказує на робітника: " << ptr_worker->name << "\n";
  std::cout << "Виклики методів через вказівник оператором ->:\n";
  ptr_worker->PrintInfo();

  Project* ptr_project = p_dyn2;
  std::cout << "Покажчик ptr_project вказує на динамічний проєкт: " << ptr_project->title << "\n";
  ptr_project->AssignLeadWorker(*ptr_worker);
  ptr_project->PrintInfo();

  // ==========================================================================
  // [Пункт 4 & 5] Методи запису у файл та читання з файлу
  // ==========================================================================
  std::cout << "\n>>> [Пункт 4 & 5] Запис та читання об'єктів з файлу (DATA.TXT)...\n";

  const char* filename = "DATA.TXT";

  // Запис у файл
  std::ofstream out_file(filename);
  if (out_file.is_open()) {
    std::cout << "Запис 2 проєктів у файл " << filename << "...\n";
    project_array[0].WriteToFile(out_file);
    project_array[1].WriteToFile(out_file);
    out_file.close();
    std::cout << "Запис успішно завершено.\n";
  }

  // Читання з файлу у нові об'єкти
  Project read_project1;
  Project read_project2;

  std::ifstream in_file(filename);
  if (in_file.is_open()) {
    std::cout << "Зчитування проєктів з файлу " << filename << "...\n";
    read_project1.ReadFromFile(in_file);
    read_project2.ReadFromFile(in_file);
    in_file.close();
    std::cout << "Зчитано наступні дані:\n";
    read_project1.PrintInfo();
    read_project2.PrintInfo();
  }

  // ==========================================================================
  // [Пункт 12] Виділення випадкової динамічної пам'яті та сортування
  // ==========================================================================
  std::cout << "\n>>> [Пункт 12] Виділення випадкового обсягу динамічної пам'яті та сортування...\n";

  std::cout << "\n1. Для об'єкта Worker (сорування годин заповненого масиву):\n";
  w_stat1.AllocateAndSortTaskHours(8);

  std::cout << "\n2. Для об'єкта Project (сорування історії витрат проєкту):\n";
  project_array[0].AllocateAndSortExpensesHistory(6);

  // ==========================================================================
  // Очищення динамічної пам'яті (delete для об'єктів new)
  // ==========================================================================
  delete p_dyn1;
  delete p_dyn2;
  delete p_dyn3;
  delete p_dyn4;
  delete p_dyn5;

  std::cout << "\n========================================================================\n";
  std::cout << "        УСІ ПУНКТИ ЛАБОРАТОРНОЇ РОБОТИ №2 УСПІШНО ВИКОНАНО!            \n";
  std::cout << "========================================================================\n";

  return 0;
}
