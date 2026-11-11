#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

#include "assignment.h"
#include "block_tracker.h"
#include "budget.h"
#include "contractor.h"
#include "customer.h"
#include "intern.h"
#include "manager.h"
#include "project.h"
#include "project_coordinator.h"
#include "resource_pool.h"
#include "team_lead.h"
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

void RunLab3Demo() {
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

  // Спосіб 1: Простий
  Worker w_simple(101, "Олександр Коваленко", "Lead Developer", 45.0, 160, 20,
                  5000.0, 9);
  std::cout << "1. Простий спосіб (Worker w_simple(...)):\n";
  w_simple.PrintInfo();

  // Спосіб 2: Явний
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

  // Об'єкт у статичній/автоматичній пам'яті на стеку (Requirement 9)
  Project p_stat(1, "E-Commerce Platform", "In Progress", 50000.0, 12000.0, 8, 90);
  Project *p_dyn2 =
      new Project(2, "Mobile Banking App", "Planned", 80000.0, 5000.0, 12, 120);

  // Покажчик на екземпляр класу (Requirement 9) через оператор &
  Project *ptr_proj = &p_stat;
  std::cout << "Покажчик ptr_proj вказує на проєкт на стеку: "
            << ptr_proj->title << "\n";
  ptr_proj->PrintInfo();

  // ==========================================================================
  // [Requirement 13] Сценарій взаємодії за КОМПОЗИЦІЄЮ
  // ==========================================================================
  std::cout << "\n>>> [Пункт 13] Демонстрація взаємодії за КОМПОЗИЦІЄЮ "
               "(Composition)...\n";
  ptr_proj->AssignLeadWorkerComposition(w_simple);
  ptr_proj->PrintInfo();

  // ==========================================================================
  // [Requirement 12] Сценарій взаємодії за АГРЕГАЦІЄЮ
  // ==========================================================================
  std::cout << "\n>>> [Пункт 12] Демонстрація взаємодії за АГРЕГАЦІЄЮ "
               "(Aggregation)...\n";
  ptr_proj->AssignLeadWorkerAggregation(&w_explicit);
  ptr_proj->PrintInfo();

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
  TaskAssignment assignment1(501, "Розробка платежного модуля API", 40, ptr_proj,
                             &manager_obj, &w_simple);
  assignment1.PrintInfo();

  // ==========================================================================
  // [Requirement 5 & 6] Глобальні функції та їх перевантаження
  // ==========================================================================
  std::cout << "\n>>> [Пункт 5 & 6] Виклики глобальної функції та її "
               "перевантаженої версії...\n";

  // Виклик функції за значенням (Requirement 5)
  CalculateProjectEfficiency(p_stat);

  // Виклик перевантаженої функції за вказівником (Requirement 6)
  CalculateProjectEfficiency(ptr_proj);

  // ==========================================================================
  // [Requirement 7] Функція, що повертає об'єкт класу
  // ==========================================================================
  std::cout << "\n>>> [Пункт 7] Виклик функції, яка повертає об'єкт класу...\n";
  Project upgraded_p = UpgradeProjectBudget(p_stat, 15000.0);
  upgraded_p.PrintInfo();

  // ==========================================================================
  // Очищення динамічної пам'яті (delete)
  // ==========================================================================
  std::cout << "\n>>> Очищення динамічних об'єктів...\n";
  delete p_dyn2;

  std::cout
      << "\n==============================================================="
         "=========\n";
  std::cout
      << "        УСІ 18 ПУНКТІВ ЛАБОРАТОРНОЇ РОБОТИ №3 УСПІШНО ВИКОНАНО! \n";
  std::cout << "==============================================================="
               "=========\n";
}

void RunLab4Demo() {
  std::cout << "==============================================================="
               "=========\n";
  std::cout << "     ЛАБОРАТОРНА РОБОТА №4 - НАСЛІДУВАННЯ (МЕНЕДЖМЕНТ ПРОЄКТУ)  "
               "         \n";
  std::cout << "==============================================================="
               "=========\n\n";

  // [ЛР4, п.8] Об'єкт BlockTracker відстежує вхід у блок функції та вихід з
  // нього (деструктор спрацьовує останнім при виході з блоку)
  BlockTracker demo_block("RunLab4Demo");

  // ==========================================================================
  // [ЛР4, п.7] Порядок виклику конструкторів і деструкторів при простому
  // наслідуванні: спочатку базовий клас, потім похідний; деструктори — навпаки
  // ==========================================================================
  std::cout << "\n>>> [Пункт 7] Порядок конструкторів і деструкторів: просте "
               "наслідування\n";
  {
    BlockTracker block("Просте наслідування");
    std::cout << "  -- Manager : public Worker\n";
    Manager manager(1, "Manager A", "Project Manager", 50.0, 100, 10, 1000.0,
                    9, "PMO", 2, 10.0, 5000.0, 5);
    std::cout << "  -- Contractor : protected Worker\n";
    Contractor contractor(2, "Contractor B", 40.0, 60, "Outsource Inc",
                          "CN-001", 3, 500.0, 18.0, false);
    std::cout << "  -- Intern : private Worker\n";
    Intern intern(3, "Intern C", 8.0, "KPI", "Software Engineering", 2, 8,
                  200.0, 1);
    std::cout << "  -- ProjectCoordinator : private Manager (: public Worker)\n";
    ProjectCoordinator coordinator(4, "Coordinator D", 35.0, "PMO", 1,
                                   "Teams", "Trello", 20.0);
    std::cout << "  -- Кінець блоку: деструктори у зворотному порядку\n";
  }

  // ==========================================================================
  // [ЛР4, п.7] Порядок виклику конструкторів і деструкторів при множинному
  // наслідуванні: базові класи — у порядку оголошення в списку наслідування
  // ==========================================================================
  std::cout << "\n>>> [Пункт 7] Порядок конструкторів і деструкторів: "
               "множинне наслідування\n";
  {
    BlockTracker block("Множинне наслідування");
    std::cout
        << "  -- TeamLead : public Manager, public Budget, public ResourcePool\n";
    TeamLead team_lead(5, "TeamLead E", 45.0, "Development", "Alpha",
                       "Backend", 3000.0, 3, 3, 10);
    std::cout << "  -- Кінець блоку: деструктори у зворотному порядку\n";
  }

  {
    BlockTracker block("Сценарій функціонування системи");

    // ========================================================================
    // [ЛР4, п.2, п.5] Створення об'єктів похідних класів конструкторами з
    // передачею параметрів конструктору базового класу Worker
    // ========================================================================
    std::cout << "\n>>> [Пункт 2, 5] Створення учасників проєкту "
                 "конструкторами похідних класів\n";
    Manager manager(201, "Ірина Ткаченко", "Project Manager", 65.0, 160, 25,
                    12000.0, 10, "Development", 3, 15.0, 30000.0, 8);
    Contractor contractor(301, "Андрій Савченко", 50.0, 80, "CloudOps LLC",
                          "CN-2026-017", 6, 2000.0, 20.0, true);
    Intern intern(401, "Олена Литвин", 10.0, "КНУ", "Комп'ютерні науки", 3,
                  12, 300.0, 201);
    Worker developer(110, "Максим Кравець", "Backend Developer", 42.0, 120,
                     10, 0.0, 8);
    Worker designer(111, "Софія Бойко", "UI/UX Designer", 38.0, 100, 7, 0.0,
                    9);

    // ========================================================================
    // [ЛР4, п.2] Керування доступом до трьох даних (worker_id, name, role) та
    // трьох методів (CalculateSalary, UpdateTasks, PrintInfo) базового класу
    // ========================================================================
    std::cout << "\n>>> [Пункт 2] public-наслідування (Manager): члени Worker "
                 "доступні ззовні\n";
    std::cout << "  manager.worker_id=" << manager.worker_id
              << ", manager.name=" << manager.name
              << ", manager.role=" << manager.role << "\n";
    manager.UpdateTasks(2);
    std::cout << "  manager.Worker::CalculateSalary()=$"
              << manager.Worker::CalculateSalary() << "\n";
    manager.Worker::PrintInfo();
    manager.ShowInheritedAccess();

    std::cout << "\n>>> [Пункт 2] protected-наслідування (Contractor): члени "
                 "Worker доступні лише всередині класу\n";
    // contractor.role;               // помилка: role захищений у Contractor
    // contractor.CalculateSalary();  // помилка: метод захищений
    // contractor.UpdateTasks(1);     // помилка: метод захищений
    contractor.ShowInheritedAccess();

    std::cout << "\n>>> [Пункт 2] private-наслідування (Intern): члени Worker "
                 "закриті, доступні лише всередині класу\n";
    // intern.worker_id;           // помилка: поле закрите в Intern
    // intern.CalculateSalary();   // помилка: метод закритий
    // intern.PrintTotalWorkers(); // помилка: метод закритий
    intern.ShowInheritedAccess();

    // ========================================================================
    // [ЛР4, п.6] Доступ до членів базового класу через оператор області
    // видимості (Worker::) та оператор using
    // ========================================================================
    std::cout << "\n>>> [Пункт 6] Оператор області видимості та using\n";
    std::cout << "  manager.CalculateSalary() (з бонусом) = $"
              << manager.CalculateSalary()
              << " | manager.Worker::CalculateSalary() = $"
              << manager.Worker::CalculateSalary() << "\n";
    std::cout << "  using Worker::name / worker_id у Contractor: "
              << contractor.name << " #" << contractor.worker_id << "\n";

    // ========================================================================
    // [ЛР4, п.9] Сценарій: замовник замовляє проєкт у менеджера
    // ========================================================================
    std::cout << "\n>>> [Пункт 9] Замовник замовляє проєкт у менеджера\n";
    Customer customer(1, "FinTech Solutions", "Ольга Іваненко",
                      "olga@fintech.ua", "+380671234567", "Україна");
    Project project(20, "Online Banking Portal", "Planned", 50000.0, 0.0, 6,
                    120);
    customer.OrderProject(project, manager);
    TaskAssignment task(601, "Інтеграція платіжного шлюзу", 40, &project,
                        &manager, &developer);
    task.PrintInfo();

    // ========================================================================
    // [ЛР4, п.4, п.9] Об'єкт класу з множинним наслідуванням: тімлід формує
    // команду, розподіляє завдання, бюджет та ресурси
    // ========================================================================
    std::cout << "\n>>> [Пункт 4, 9] TeamLead розподіляє роботу, бюджет і "
                 "ресурси в команді\n";
    TeamLead team_lead(203, "Тарас Мороз", 55.0, "Development",
                       "Payments Team", "Платіжний модуль", 6000.0, 6, 6, 20);
    team_lead.AddMember(&developer);
    team_lead.AddMember(&designer);
    team_lead.DistributeWork(3, 1500.0);
    team_lead.ProvideResources(developer, 2, 2, 5);
    team_lead.ProvideResources(designer, 1, 2, 3);
    team_lead.HoldStandup();
    // [ЛР4, п.6] Виклик однойменних методів різних базових класів ззовні
    std::cout << "  team_lead.Budget::PrintInfo():\n";
    team_lead.Budget::PrintInfo();
    std::cout << "  team_lead.ResourcePool::PrintInfo():\n";
    team_lead.ResourcePool::PrintInfo();
    team_lead.PrintInfo();

    // ========================================================================
    // [ЛР4, п.3, п.9] Об'єкт класу з закритим наслідуванням оперує методами
    // різних класів ієрархії (Worker, Manager, ProjectCoordinator)
    // ========================================================================
    std::cout << "\n>>> [Пункт 3, 9] ProjectCoordinator координує завдання\n";
    ProjectCoordinator coordinator(202, "Віктор Гнатюк", 40.0, "PMO", 20,
                                   "Slack", "Jira", 25.0);
    coordinator.ScheduleMeeting("Планування спринту");
    coordinator.CoordinateTask(developer, 2, 800.0);
    // [ЛР4, п.6] AssignTask відкритий через using Manager::AssignTask
    coordinator.AssignTask(designer, 1, 400.0);
    // coordinator.ApproveExpense(project, 100.0);  // помилка: метод закритий
    // coordinator.Worker::PrintInfo();             // помилка: база закрита
    coordinator.ResolveConflict("перетин дедлайнів дизайну та бекенду");
    coordinator.PrintInfo();

    // ========================================================================
    // [ЛР4, п.9] Підрядник і стажер виконують роботу, менеджер керує
    // бюджетом проєкту, замовник переглядає результат та оплачує
    // ========================================================================
    std::cout << "\n>>> [Пункт 9] Виконання робіт та керування бюджетом\n";
    contractor.CompleteDeliverable(1000.0);
    contractor.ExtendContract(3);
    intern.CompleteTrainingTask();
    intern.ExtendInternship(4);
    manager.ApproveExpense(project, team_lead.get_spent_amount());
    manager.ApproveExpense(project, contractor.CalculateInvoice());
    manager.ApproveExpense(project, intern.CalculateStipend());
    manager.ApproveExpense(project, 40000.0);
    coordinator.SubmitReport(project);
    customer.ReviewProject(project);
    customer.PayInvoice(project.get_current_expenses());

    std::cout << "\n>>> Підсумковий стан об'єктів\n";
    customer.PrintInfo();
    project.PrintInfo();
    manager.PrintInfo();
    contractor.PrintInfo();
    intern.PrintInfo();
    developer.PrintInfo();
    designer.PrintInfo();
    Worker::PrintTotalWorkers();
    std::cout << "\n  -- Кінець сценарію: деструктори всіх об'єктів\n";
  }
  Worker::PrintTotalWorkers();
}

int main() {
  std::setlocale(LC_ALL, "");
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  int choice = 4;
  std::cout << "Оберіть демонстрацію (3 - ЛР3, 4 - ЛР4): ";
  if (!(std::cin >> choice)) {
    choice = 4;
  }
  std::cout << "\n";

  if (choice == 3) {
    RunLab3Demo();
  } else {
    RunLab4Demo();
  }
  return 0;
}
