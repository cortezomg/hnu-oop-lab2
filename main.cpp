#include "project.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

void runFullDemonstration() {
  std::cout << "\n==============================================================="
               "=========\n";
  std::cout << "        АВТОМАТИЧНА ДЕМОНСТРАЦІЯ ВСІХ ПУНКТІВ (РІВЕНЬ 3)       "
               "         \n";
  std::cout << "==============================================================="
               "=========\n\n";

  // [Пункт 5] Створення 5 об'єктів у статичній та 5 у динамічній пам'яті
  Worker w_stat1(101, "Олександр Коваленко", "Lead Developer", 45.0, 160, 20,
                 5000.0, 9);
  Worker w_stat2(102, "Марія Мельник", "QA Automation", 30.0, 150, 15, 3000.0,
                 8);
  Worker w_stat3(103, "Дмитро Шевченко", "DevOps Engineer", 40.0, 140, 12,
                 4500.0, 9);
  Worker w_stat4(104, "Анна Бойко", "UI/UX Designer", 35.0, 130, 10, 2500.0, 7);
  Worker w_stat5(105, "Іван Ткаченко", "Backend Developer", 38.0, 155, 18,
                 4000.0, 8);

  Project *p_dyn1 = new Project(1, "E-Commerce Platform", "In Progress",
                                50000.0, 12000.0, 8, 90);
  Project *p_dyn2 =
      new Project(2, "Mobile Banking App", "Planned", 80000.0, 5000.0, 12, 120);
  Project *p_dyn3 = new Project(3, "CRM System Integration", "In Progress",
                                35000.0, 18000.0, 6, 60);
  Project *p_dyn4 =
      new Project(4, "AI Analytics Dashboard", "Planned", 60000.0, 0.0, 5, 75);
  Project *p_dyn5 = new Project(5, "Cloud Infrastructure Migration",
                                "Completed", 45000.0, 44000.0, 7, 45);

  std::cout << ">>> [Пункт 5] Створено 5 статичних робітників та 5 динамічних "
               "проєктів.\n";

  // [Пункт 6 & 7] Створення 2 масивів об'єктів та робота з ними
  Worker worker_array[5] = {w_stat1, w_stat2, w_stat3, w_stat4, w_stat5};
  Project project_array[5] = {*p_dyn1, *p_dyn2, *p_dyn3, *p_dyn4, *p_dyn5};

  std::cout << "\n>>> [Пункт 6 & 7] Робота з масивами: оновлення завдань у масиві...\n";
  for (int i = 0; i < 5; ++i) {
    worker_array[i].UpdateTasks(2, 500.0);
  }

  // [Пункт 3 & 10] Сценарій взаємодії двох об'єктів
  std::cout << "\n>>> [Пункт 3 & 10] Сценарій взаємодії двох об'єктів (призначення тимлідів)...\n";
  for (int i = 0; i < 5; ++i) {
    project_array[i].AssignLeadWorker(worker_array[i]);
  }

  std::cout << "\n--- Інформація про перший проєкт масиву після призначення тимліда ---\n";
  project_array[0].PrintInfo();

  // [Пункт 8 & 9] Демонстрація всіх методів класів Worker та Project
  std::cout << "\n>>> [Пункт 8 & 9] Демонстрація всіх методів класів...\n";
  std::cout << "   - CalculateSalary() робітника 1: $" << w_stat1.CalculateSalary() << "\n";
  w_stat1.UpdateTasks(5);
  w_stat1.UpdateTasks(3, 1200.0);
  
  Worker current_lead = project_array[0].GetLeadWorker();
  std::cout << "   - GetLeadWorker() повернув об'єкт: " << current_lead.name << "\n";
  project_array[0].UpdateStatus("Completed", 3500.0);

  // [Пункт 11] Покажчик на екземпляр класу
  std::cout << "\n>>> [Пункт 11] Використання покажчика на екземпляр класу...\n";
  Worker *ptr_worker = &w_stat3;
  std::cout << "Покажчик ptr_worker вказує на: " << ptr_worker->name << "\n";
  ptr_worker->PrintInfo();

  // [Пункт 4 & 5] Запис та читання з файлу
  std::cout << "\n>>> [Пункт 4 & 5] Запис та читання об'єктів з файлу (DATA.TXT)...\n";
  const char *filename = "DATA.TXT";
  std::ofstream out_file(filename);
  if (out_file.is_open()) {
    project_array[0].WriteToFile(out_file);
    project_array[1].WriteToFile(out_file);
    out_file.close();
    std::cout << "Записано 2 проєкти у файл " << filename << "\n";
  }

  Project read_project1, read_project2;
  std::ifstream in_file(filename);
  if (in_file.is_open()) {
    read_project1.ReadFromFile(in_file);
    read_project2.ReadFromFile(in_file);
    in_file.close();
    std::cout << "Зчитано проєкт з файлу:\n";
    read_project1.PrintInfo();
  }

  // [Пункт 12] Динамічна пам'ять та сортування
  std::cout << "\n>>> [Пункт 12] Виділення випадкового обсягу динамічної пам'яті та сортування...\n";
  w_stat1.AllocateAndSortTaskHours(8);
  project_array[0].AllocateAndSortExpensesHistory(6);

  // Очищення динамічної пам'яті
  delete p_dyn1;
  delete p_dyn2;
  delete p_dyn3;
  delete p_dyn4;
  delete p_dyn5;
}

void runManualInputMode() {
  std::cout << "\n==============================================================="
               "=========\n";
  std::cout << "        РУЧНЕ ВВЕДЕННЯ ДАНИХ ТА ТЕСТУВАННЯ КОРИСТУВАЧЕМ        "
               "         \n";
  std::cout << "==============================================================="
               "=========\n";

  Project user_project;
  user_project.InputFromConsole();

  std::cout << "\n\nВведено наступний об'єкт проєкту з вкладеним робітником:\n";
  user_project.PrintInfo();

  std::cout << "\n--- Тестування методів на введеному об'єкті ---\n";
  std::cout << "1. Викликаємо оновлення статусу та додавання витрат (+$2500):\n";
  user_project.UpdateStatus("In Progress", 2500.0);
  user_project.PrintInfo();

  std::cout << "\n2. Викликаємо метод виділення динамічної пам'яті та сортування історії витрат:\n";
  user_project.AllocateAndSortExpensesHistory(5);

  std::cout << "\n3. Запис введеного об'єкта у файл USER_DATA.TXT та зчитування назад:\n";
  const char* user_file = "USER_DATA.TXT";
  std::ofstream out(user_file);
  if (out.is_open()) {
    user_project.WriteToFile(out);
    out.close();
    std::cout << "Успішно записано у файл " << user_file << "\n";
  }

  Project read_user_project;
  std::ifstream in(user_file);
  if (in.is_open()) {
    read_user_project.ReadFromFile(in);
    in.close();
    std::cout << "Зчитано з файлу " << user_file << ":\n";
    read_user_project.PrintInfo();
  }
}

int main() {
  std::setlocale(LC_ALL, "");
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  int choice = -1;
  while (choice != 0) {
    std::cout << "\n==============================================================="
                 "=========\n";
    std::cout << "        ЛАБОРАТОРНА РОБОТА №2 - ВАРІАНТ 9 (МЕНЕДЖМЕНТ ПРОЄКТУ) "
                 "         \n";
    std::cout << "==============================================================="
                 "=========\n";
    std::cout << "1. Запустити автоматичну демонстрацію всіх 16 пунктів\n";
    std::cout << "2. Ввести дані проєкту та робітника вручну з клавіатури\n";
    std::cout << "0. Вийти з програми\n";
    std::cout << "==============================================================="
                 "=========\n";
    std::cout << "Оберіть варіант (1, 2 або 0): ";

    if (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Некоректне введення. Спробуйте ще раз.\n";
      continue;
    }

    switch (choice) {
      case 1:
        runFullDemonstration();
        break;
      case 2:
        runManualInputMode();
        break;
      case 0:
        std::cout << "Завершення роботи програми.\n";
        break;
      default:
        std::cout << "Невідомий пункт меню.\n";
        break;
    }
  }

  return 0;
}
