#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

#include "assignment.h"
#include "project.h"
#include "worker.h"

// ============================================================================
// [Requirement 5] Global function taking class object BY VALUE
// Performs numeric calculation (budget utilization efficiency) and prints
// result
// ============================================================================
double CalculateProjectEfficiency(Project p) {
  double budget = p.get_total_budget();
  double expenses = p.get_current_expenses();
  double efficiency =
      (budget > 0) ? ((budget - expenses) / budget) * 100.0 : 0.0;

  std::cout << "\n  [Глобальна функція (За значенням)] Ефективність проєкту '"
            << p.title << "': " << efficiency << "%\n";
  return efficiency;
}

// ============================================================================
// [Requirement 6] OVERLOADED Global function taking class object BY POINTER
// Performs numeric calculation (budget utilization efficiency) and prints
// result
// ============================================================================
double CalculateProjectEfficiency(const Project *p) {
  if (p == nullptr)
    return 0.0;
  double budget = p->get_total_budget();
  double expenses = p->get_current_expenses();
  double efficiency =
      (budget > 0) ? ((budget - expenses) / budget) * 100.0 : 0.0;

  std::cout << "  [Глобальна функція (За вказівником)] Ефективність проєкту '"
            << p->title << "': " << efficiency << "%\n";
  return efficiency;
}

// ============================================================================
// [Requirement 7] Function returning a class object
// Creates and returns an upgraded Project object
// ============================================================================
Project UpgradeProjectBudget(const Project &source, double bonus_budget) {
  Project upgraded(source); // Use copy constructor
  upgraded.project_id += 1000;
  std::snprintf(upgraded.title, sizeof(upgraded.title), "%s (Upgraded)",
                source.title);
  std::cout << "  [Функція, що повертає об'єкт] Модифіковано та повернено "
               "новий проєкт з додатковим бюджетом\n";
  return upgraded;
}

int main() {
  std::setlocale(LC_ALL, "");
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  std::cout << "==============================================================="
               "=========\n";
  std::cout << "        ЛАБОРАТОРНА РОБОТА №3 - ВАРІАНТ 9 (МЕНЕДЖМЕНТ ПРОЄКТУ) "
               "         \n";
  std::cout << "==============================================================="
               "=========\n\n";

  // ==========================================================================
  // [Requirement 4] Статичні поля та методи класу
  // ==========================================================================
  std::cout << ">>> [Пункт 4] Виклик статичних методів класу до створення "
               "об'єктів:\n";
  Worker::PrintTotalWorkers();
  Project::PrintTotalProjects();

  // ==========================================================================
  // [Requirement 8] Три способи створення об'єктів за допомогою конструкторів
  // ==========================================================================
  std::cout
      << "\n>>> [Пункт 8 & 10] Демонстрація 3 способів створення об'єктів...\n";

  // Спосіб 1: Простий (Simple creation)
  Worker w_simple(101, "Олександр Коваленко", "Lead Developer", 45.0, 160, 20,
                  5000.0, 9);
  std::cout << "1. Простий спосіб (Worker w_simple(...)):\n";
  w_simple.PrintInfo();

  // Спосіб 2: Явний (Explicit creation via assignment)
  Worker w_explicit =
      Worker(102, "Марія Мельник", "QA Automation", 30.0, 150, 15, 3000.0, 8);
  std::cout << "2. Явний спосіб (Worker w_explicit = Worker(...)):\n";
  w_explicit.PrintInfo();

  // Спосіб 3: Скорочений (Shortened initializer list style C++11)
  Worker w_short{
      103, "Дмитро Шевченко", "DevOps Engineer", 40.0, 140, 12, 4500.0, 9};
  std::cout << "3. Скорочений спосіб (Worker w_short{...}):\n";
  w_short.PrintInfo();

  // ==========================================================================
  // [Requirement 1, 10] Демонстрація Конструктора Копіювання (Copy Constructor)
  // ==========================================================================
  std::cout << "\n>>> [Пункт 1 & 10] Демонстрація Конструктора Копіювання...\n";
  Worker w_copy(w_simple); // Викликається Worker(const Worker&)
  w_copy.PrintInfo();

  // ==========================================================================
  // [Requirement 4] Перевірка роботи статичного лічильника об'єктів
  // ==========================================================================
  std::cout << "\n>>> [Пункт 4] Перевірка статичних лічильників у пам'яті:\n";
  Worker::PrintTotalWorkers();

  // ==========================================================================
  // [Requirement 3] Демонстрація Деструкторів при входженні/виході з блоку {}
  // ==========================================================================
  std::cout << "\n>>> [Пункт 3] Демонстрація виклику Деструктора у локальному "
               "блоці {}...\n";
  std::cout << "  --> Вхід у локальний блок {}\n";
  {
    Worker local_worker(999, "Тимчасовий Співробітник", "Intern", 15.0, 40, 2,
                        500.0, 5);
    local_worker.PrintInfo();
    Worker::PrintTotalWorkers();
    std::cout << "  <-- Вихід з локального блоку {}\n";
  } // Тут викликається деструктор ~Worker() для local_worker
  std::cout << "  Після виходу з блоку:\n";
  Worker::PrintTotalWorkers();

  // ==========================================================================
  // [Requirement 9] Розміщення в статичній та динамічній пам'яті + покажчики
  // ==========================================================================
  std::cout << "\n>>> [Пункт 9] Створення об'єктів у статичній та динамічній "
               "пам'яті...\n";

  // Динамічний об'єкт у кучі (Heap)
  Project *p_dyn1 = new Project(1, "E-Commerce Platform", "In Progress",
                                50000.0, 12000.0, 8, 90);
  Project *p_dyn2 =
      new Project(2, "Mobile Banking App", "Planned", 80000.0, 5000.0, 12, 120);

  // Покажчик на екземпляр класу (Requirement 9)
  Project *ptr_proj = p_dyn1;
  std::cout << "Покажчик ptr_proj вказує на динамічний проєкт: "
            << ptr_proj->title << "\n";
  ptr_proj->PrintInfo();

  // ==========================================================================
  // [Requirement 13] Сценарій взаємодії за КОМПОЗИЦІЄЮ
  // ==========================================================================
  std::cout << "\n>>> [Пункт 13] Демонстрація взаємодії за КОМПОЗИЦІЄЮ "
               "(Composition)...\n";
  p_dyn1->AssignLeadWorkerComposition(w_simple);
  p_dyn1->PrintInfo();

  // ==========================================================================
  // [Requirement 12] Сценарій взаємодії за АГРЕГАЦІЄЮ
  // ==========================================================================
  std::cout << "\n>>> [Пункт 12] Демонстрація взаємодії за АГРЕГАЦІЄЮ "
               "(Aggregation)...\n";
  p_dyn1->AssignLeadWorkerAggregation(&w_explicit);
  p_dyn1->PrintInfo();

  // ==========================================================================
  // [Requirement 11] Клас Асоціацій (Взаємодія 3-х об'єктів)
  // ==========================================================================
  std::cout << "\n>>> [Пункт 11] Демонстрація взаємодії 3-х об'єктів через "
               "Клас Асоціацій...\n";

  // Створюємо 3-й об'єкт (Менеджер)
  Worker manager_obj(200, "Сергій Бондаренко", "Project Manager", 60.0, 160, 30,
                     10000.0, 10);

  // Клас асоціацій пов'язує 3 об'єкти: Project, Manager (Worker 1), Assignee
  // (Worker 2)
  TaskAssignment assignment1(501, "Розробка платежного модуля API", 40, p_dyn1,
                             &manager_obj, &w_simple);
  assignment1.PrintInfo();

  // ==========================================================================
  // [Requirement 5 & 6] Глобальні функції та їх перевантаження
  // ==========================================================================
  std::cout << "\n>>> [Пункт 5 & 6] Виклики глобальної функції та її "
               "перевантаженої версії...\n";

  // Виклик функції за значенням (Requirement 5)
  CalculateProjectEfficiency(*p_dyn1);

  // Виклик перевантаженої функції за вказівником (Requirement 6)
  CalculateProjectEfficiency(p_dyn1);

  // ==========================================================================
  // [Requirement 7] Функція, що повертає об'єкт класу
  // ==========================================================================
  std::cout << "\n>>> [Пункт 7] Виклик функції, яка повертає об'єкт класу...\n";
  Project upgraded_p = UpgradeProjectBudget(*p_dyn1, 15000.0);
  upgraded_p.PrintInfo();

  // ==========================================================================
  // Очищення динамічної пам'яті (delete)
  // ==========================================================================
  std::cout << "\n>>> Очищення динамічних об'єктів...\n";
  delete p_dyn1;
  delete p_dyn2;

  std::cout
      << "\n==============================================================="
         "=========\n";
  std::cout
      << "        УСІ 18 ПУНКТІВ ЛАБОРАТОРНОЇ РОБОТИ №3 УСПІШНО ВИКОНАНО! \n";
  std::cout << "==============================================================="
               "=========\n";

  return 0;
}
