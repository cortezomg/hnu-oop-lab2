#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>

#include "assignment.h"
#include "block_tracker.h"
#include "budget.h"
#include "contractor.h"
#include "customer.h"
#include "equipment.h"
#include "intern.h"
#include "manager.h"
#include "material.h"
#include "project.h"
#include "project_coordinator.h"
#include "resource.h"
#include "resource_exceptions.h"
#include "resource_pool.h"
#include "resource_registry.h"
#include "software_license.h"
#include "team_lead.h"
#include "worker.h"
#include "workstation.h"

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

// [ЛР5, п.7] Режими роботи функції Service
enum class ServiceMode { kWriteAndRead, kReadOnly };

// [ЛР5, п.7] Функція Service отримує об'єкт класу та, використовуючи його
// методи Write і Read, записує поля даних у файл та читає їх з файлу.
// Можливі виняткові ситуації генеруються через throw
void Service(Resource &resource, const std::string &file_name,
             ServiceMode mode = ServiceMode::kWriteAndRead) {
  if (file_name.empty()) {
    throw std::invalid_argument("ім'я файлу порожнє");
  }
  if (file_name.size() < 5 ||
      file_name.compare(file_name.size() - 4, 4, ".txt") != 0) {
    throw std::invalid_argument("файл '" + file_name +
                                "' повинен мати розширення .txt");
  }
  if (mode == ServiceMode::kWriteAndRead) {
    std::ofstream out(file_name);
    if (!out.is_open()) {
      throw FileOpenError("не вдалося відкрити файл '" + file_name +
                          "' для запису");
    }
    resource.Write(out);
    out.close();
    if (out.fail()) {
      throw FileOpenError("помилка запису у файл '" + file_name + "'");
    }
    std::cout << "  [Service] Об'єкт '" << resource.get_name()
              << "' записано у файл '" << file_name << "'\n";
  }
  std::ifstream in(file_name);
  if (!in.is_open()) {
    throw FileOpenError("не вдалося відкрити файл '" + file_name +
                        "' для читання");
  }
  resource.Read(in);
  std::cout << "  [Service] Дані прочитано з файлу '" << file_name << "':\n";
  resource.PrintInfo();
}

// [ЛР5, п.7] Обробка винятків функції Service через try-catch
void TryService(Resource &resource, const std::string &file_name,
                ServiceMode mode, const std::string &situation) {
  std::cout << "  -- " << situation << "\n";
  try {
    Service(resource, file_name, mode);
  } catch (const std::invalid_argument &e) {
    std::cout << "  [catch invalid_argument] " << e.what() << "\n";
  } catch (const FileOpenError &e) {
    std::cout << "  [catch FileOpenError] " << e.what() << "\n";
  } catch (const FileFormatError &e) {
    std::cout << "  [catch FileFormatError] " << e.what() << "\n";
  } catch (const std::exception &e) {
    std::cout << "  [catch exception] " << e.what() << "\n";
  }
}

// [ЛР5, п.7] Демонстрація виняткових ситуацій при роботі з файлами
void DemonstrateFileExceptions(Resource &resource) {
  const std::string kEmptyFile = "lab5_empty.txt";
  const std::string kCorruptedFile = "lab5_corrupted.txt";
  const std::string kMaterialFile = "lab5_material.txt";
  std::ofstream(kEmptyFile).close();
  std::ofstream corrupted(kCorruptedFile);
  corrupted << resource.GetCategory() << "\n" << "abc\n";
  corrupted.close();

  TryService(resource, "", ServiceMode::kWriteAndRead,
             "Ситуація 1: порожнє ім'я файлу");
  TryService(resource, "resources.dat", ServiceMode::kWriteAndRead,
             "Ситуація 2: неприпустиме розширення файлу");
  TryService(resource, "/no_such_dir/resources.txt",
             ServiceMode::kWriteAndRead,
             "Ситуація 3: неможливо відкрити файл для запису");
  TryService(resource, "lab5_missing.txt", ServiceMode::kReadOnly,
             "Ситуація 4: файл для читання не існує");
  TryService(resource, kEmptyFile, ServiceMode::kReadOnly,
             "Ситуація 5: файл порожній");
  TryService(resource, kCorruptedFile, ServiceMode::kReadOnly,
             "Ситуація 6: пошкоджені дані у файлі");
  {
    Material paint(601, "Фарба", "Sniezka", 4, 15.0, 2026, "l", 1, false);
    TryService(paint, kMaterialFile, ServiceMode::kWriteAndRead,
               "Запис об'єкта Material у файл");
  }
  TryService(resource, kMaterialFile, ServiceMode::kReadOnly,
             "Ситуація 7: тип об'єкта у файлі не відповідає типу об'єкта");

  std::remove(kEmptyFile.c_str());
  std::remove(kCorruptedFile.c_str());
  std::remove(kMaterialFile.c_str());
}

// [ЛР5, п.9] Поліморфний виклик через посилання на базовий клас
void ShowResource(const Resource &resource) {
  std::cout << "  2) Через посилання: " << resource.GetCategory() << " '"
            << resource.get_name() << "', вартість $"
            << resource.CalculateCost() << "\n";
  resource.PrintInfo();
}

void RunLab5Demo() {
  std::cout << "==============================================================="
               "=========\n";
  std::cout << "     ЛАБОРАТОРНА РОБОТА №5 - ПОЛІМОРФІЗМ (МЕНЕДЖМЕНТ ПРОЄКТУ)   "
               "         \n";
  std::cout << "==============================================================="
               "=========\n\n";
  BlockTracker demo_block("RunLab5Demo");

  Worker developer(110, "Максим Кравець", "Backend Developer", 42.0, 120, 10,
                   0.0, 8);
  Worker designer(111, "Софія Бойко", "UI/UX Designer", 38.0, 100, 7, 0.0, 9);

  // ==========================================================================
  // [ЛР5, п.2] Віртуальне наслідування: конструктор Resource викликається
  // один раз, Workstation містить один спільний підоб'єкт Resource
  // ==========================================================================
  std::cout << "\n>>> [ЛР5, п.2] Віртуальне наслідування (ромб Resource -> "
               "Equipment, SoftwareLicense -> Workstation)\n";
  {
    BlockTracker block("Віртуальне наслідування");
    Workstation probe(900, "Probe Station", "HP", 1, 1500.0, "HP-0001",
                      "Windows 11", 12, 10.0, 2);
    const Resource *via_equipment = static_cast<const Equipment *>(&probe);
    const Resource *via_license =
        static_cast<const SoftwareLicense *>(&probe);
    std::cout << "  Resource через Equipment і через SoftwareLicense — "
              << (via_equipment == via_license ? "один і той самий підоб'єкт"
                                               : "різні підоб'єкти")
              << "\n";
    std::cout << "  -- Кінець блоку: деструктори у зворотному порядку\n";
  }

  // ==========================================================================
  // [ЛР5, п.5] Статичні об'єкти (5 шт.)
  // ==========================================================================
  std::cout << "\n>>> [ЛР5, п.5] Створення 5 статичних об'єктів\n";
  Equipment laptop(201, "Ноутбук Lenovo ThinkPad", "Lenovo", 3, 1200.0, 2026,
                   "LNV-77812", 24, 4, 150.0);
  SoftwareLicense ide(202, "JetBrains CLion", "JetBrains", 5, 99.0, 2026,
                      "CL-5521-AX", 12, 8.0);
  Material cable(203, "Кабель UTP Cat6", "Ukrkabel", 300, 0.8, 2026, "m", 50,
                 false);
  Workstation dev_station(204, "Dev Workstation", "Dell", 2, 2100.0,
                          "DL-9001", "Ubuntu 24.04", 24, 15.0, 3);
  Material solvent(205, "Очищувач контактів", "Kontakt Chemie", 10, 12.5,
                   2026, "l", 2, true);
  laptop.AssignTo(&developer);
  dev_station.AssignTo(&designer);

  ResourceRegistry registry;
  try {
    registry.AddStatic(&laptop);
    registry.AddStatic(&ide);
    registry.AddStatic(&cable);
    registry.AddStatic(&dev_station);
    registry.AddStatic(&solvent);

    // ========================================================================
    // [ЛР5, п.5] Динамічні об'єкти (5 шт.)
    // ========================================================================
    std::cout << "\n>>> [ЛР5, п.5] Створення 5 динамічних об'єктів\n";
    registry.AddDynamic(new Equipment(301, "Сервер Dell PowerEdge", "Dell", 1,
                                      6800.0, 2026, "PE-4410", 36, 6, 600.0));
    registry.AddDynamic(new SoftwareLicense(302, "Microsoft 365 Business",
                                            "Microsoft", 10, 0.0, 2026,
                                            "M365-TEAM", 12, 12.5));
    registry.AddDynamic(new Material(303, "Папір A4", "Navigator", 20, 6.0,
                                     2026, "pack", 5, false));
    registry.AddDynamic(new Workstation(304, "Design Workstation", "Apple", 2,
                                        3200.0, "MAC-7731", "macOS 15", 12,
                                        20.0, 2));
    registry.AddDynamic(new Equipment(305, "Проектор Epson", "Epson", 1,
                                      900.0, 2026, "EP-1180", 24, 5, 80.0));
  } catch (const std::exception &e) {
    std::cout << "  [catch] " << e.what() << "\n";
  }
  registry.PrintAll();
  std::cout << "  Resource::GetTotalCount() = " << Resource::GetTotalCount()
            << "\n";

  // ==========================================================================
  // [ЛР5, п.5] Виняткові ситуації при роботі з динамічною пам'яттю
  // ==========================================================================
  std::cout << "\n>>> [ЛР5, п.5] Виняткові ситуації при роботі з динамічною "
               "пам'яттю\n";
  std::cout << "  -- Ситуація 1: переповнення масиву динамічних об'єктів\n";
  try {
    for (int i = 1; i <= 4; ++i) {
      registry.AddDynamic(new Material(400 + i,
                                       "Запасний комплект " +
                                           std::to_string(i),
                                       "Local", 1, 5.0, 2026, "pcs", 0, false));
    }
  } catch (const std::overflow_error &e) {
    std::cout << "  [catch overflow_error] " << e.what() << "\n";
  }
  std::cout << "  -- Ситуація 2: звернення за межі масиву\n";
  try {
    registry.GetDynamic(42)->PrintInfo();
  } catch (const std::out_of_range &e) {
    std::cout << "  [catch out_of_range] " << e.what() << "\n";
  }
  std::cout << "  -- Ситуація 3: нульовий вказівник замість об'єкта\n";
  try {
    Resource *missing = nullptr;
    registry.AddDynamic(missing);
  } catch (const std::invalid_argument &e) {
    std::cout << "  [catch invalid_argument] " << e.what() << "\n";
  }
  std::cout << "  -- Ситуація 4: нестача пам'яті (std::bad_alloc)\n";
  try {
    std::size_t huge_size = std::numeric_limits<std::size_t>::max() / 4;
    char *buffer = new char[huge_size];
    std::cout << "  Виділено " << static_cast<void *>(buffer) << "\n";
    delete[] buffer;
  } catch (const std::bad_alloc &e) {
    std::cout << "  [catch bad_alloc] " << e.what() << "\n";
  }
  std::cout << "  -- Ситуація 5: некоректний (від'ємний) розмір масиву "
               "об'єктів\n";
  try {
    int batch_size = registry.dynamic_count() - 100;
    if (batch_size <= 0) {
      throw std::length_error("розмір масиву має бути додатним, отримано " +
                              std::to_string(batch_size));
    }
    Material *batch = new Material[batch_size];
    delete[] batch;
  } catch (const std::length_error &e) {
    std::cout << "  [catch length_error] " << e.what() << "\n";
  }

  // ==========================================================================
  // [ЛР5, п.4] Власні віртуальні функції похідних класів
  // ==========================================================================
  std::cout << "\n>>> [ЛР5, п.4] Власні віртуальні функції похідних класів\n";
  std::cout << "  Equipment::CalculateDepreciation(2) для '" << laptop.get_name()
            << "': $" << laptop.CalculateDepreciation(2) << "\n";
  std::cout << "  SoftwareLicense::IsExpired(13) для '" << ide.get_name()
            << "': " << (ide.IsExpired(13) ? "так" : "ні") << "\n";
  cable.Consume(120);
  solvent.Consume(20);
  std::cout << "  Workstation::CalculateSetupCost() для '"
            << dev_station.get_name() << "': $"
            << dev_station.CalculateSetupCost() << "\n";

  // ==========================================================================
  // [ЛР5, п.9] Поліморфні виклики трьох методів (GetCategory, CalculateCost,
  // PrintInfo) трьома способами
  // ==========================================================================
  std::cout << "\n>>> [ЛР5, п.9] Поліморфні виклики трьома способами\n";
  // Спосіб 1: через вказівник на базовий клас
  Resource *pointer = &laptop;
  std::cout << "  1) Через вказівник: " << pointer->GetCategory() << " '"
            << pointer->get_name() << "', вартість $"
            << pointer->CalculateCost() << "\n";
  pointer->PrintInfo();
  // Спосіб 2: через посилання на базовий клас
  ShowResource(ide);
  // Спосіб 3: через масив вказівників на базовий клас
  Resource *items[] = {&laptop, &ide, &cable, &dev_station, &solvent};
  for (Resource *item : items) {
    std::cout << "  3) Через масив вказівників: " << item->GetCategory()
              << " '" << item->get_name() << "', вартість $"
              << item->CalculateCost() << "\n";
  }

  // ==========================================================================
  // [ЛР5, п.9, п.10] Зміна форми об'єкта: один вказівник на базовий клас
  // послідовно вказує на об'єкти різних похідних класів
  // ==========================================================================
  std::cout << "\n>>> [ЛР5, п.9, п.10] Зміна форми об'єкта\n";
  Resource *shape = &laptop;
  shape->PrintInfo();
  shape = &cable;
  shape->PrintInfo();
  shape = &dev_station;
  shape->PrintInfo();

  // ==========================================================================
  // [ЛР5, п.10] Раннє (статичне) та пізнє (динамічне) зв'язування
  // ==========================================================================
  std::cout << "\n>>> [ЛР5, п.10] Раннє та пізнє зв'язування\n";
  Resource *base_pointer = &laptop;
  std::cout << "  Раннє зв'язування — виклик через об'єкт laptop.Describe():\n";
  laptop.Describe();
  std::cout << "  Раннє зв'язування — невіртуальний метод через вказівник "
               "base_pointer->Describe():\n";
  base_pointer->Describe();
  std::cout << "  Пізнє зв'язування — віртуальний метод через вказівник: "
            << base_pointer->GetCategory() << "\n";
  base_pointer = &solvent;
  std::cout << "  Після зміни форми: base_pointer->GetCategory() = "
            << base_pointer->GetCategory() << ", base_pointer->Describe():\n";
  base_pointer->Describe();

  // ==========================================================================
  // [ЛР5, п.11] Обхід механізму віртуальних функцій: явний виклик версії
  // базового класу через оператор області видимості
  // ==========================================================================
  std::cout << "\n>>> [ЛР5, п.11] Обхід механізму віртуальних функцій\n";
  Resource *station = &dev_station;
  std::cout << "  station->CalculateCost() (віртуальний виклик) = $"
            << station->CalculateCost()
            << " | dev_station.Equipment::CalculateCost() (обхід) = $"
            << dev_station.Equipment::CalculateCost() << "\n";
  std::cout << "  station->Resource::PrintInfo() — лише частина базового "
               "класу:\n";
  station->Resource::PrintInfo();

  // ==========================================================================
  // [ЛР5, п.6] Видалення об'єктів з масивів за критерієм
  // ==========================================================================
  std::cout << "\n>>> [ЛР5, п.6] Service_Static та Service_Dinamic\n";
  try {
    int removed = registry.Service_Static("Material");
    std::cout << "  Вилучено статичних об'єктів категорії Material: "
              << removed << "\n";
    removed = registry.Service_Dinamic(5000.0);
    std::cout << "  Видалено динамічних об'єктів дорожчих за $5000: "
              << removed << "\n";
  } catch (const std::exception &e) {
    std::cout << "  [catch] " << e.what() << "\n";
  }
  registry.PrintAll();

  std::cout << "\n>>> [ЛР5, п.6] Виняткові ситуації Service_Static / "
               "Service_Dinamic\n";
  std::cout << "  -- Ситуація 1: критерій не задано\n";
  try {
    registry.Service_Static("");
  } catch (const std::invalid_argument &e) {
    std::cout << "  [catch invalid_argument] " << e.what() << "\n";
  }
  std::cout << "  -- Ситуація 2: об'єктів за критерієм не знайдено\n";
  try {
    registry.Service_Static("Material");
  } catch (const std::runtime_error &e) {
    std::cout << "  [catch runtime_error] " << e.what() << "\n";
  }
  std::cout << "  -- Ситуація 3: некоректний критерій (від'ємний ліміт)\n";
  try {
    registry.Service_Dinamic(-100.0);
  } catch (const std::invalid_argument &e) {
    std::cout << "  [catch invalid_argument] " << e.what() << "\n";
  }
  std::cout << "  -- Ситуація 4: масив порожній\n";
  try {
    ResourceRegistry empty_registry;
    empty_registry.Service_Dinamic(100.0);
  } catch (const std::underflow_error &e) {
    std::cout << "  [catch underflow_error] " << e.what() << "\n";
  }

  // ==========================================================================
  // [ЛР5, п.3] Відмінність віртуального та невіртуального деструкторів при
  // видаленні об'єкта через вказівник на базовий клас
  // ==========================================================================
  std::cout << "\n>>> [ЛР5, п.3] Віртуальний та невіртуальний деструктори\n";
  {
    BlockTracker block("Віртуальний деструктор");
    Resource *resource = new Workstation(950, "Temp Station", "Lenovo", 1,
                                         1000.0, "TMP-1", "Fedora 41", 6, 5.0,
                                         1);
    std::cout << "  delete через Resource* — викликаються всі деструктори:\n";
    delete resource;
  }
  {
    BlockTracker block("Невіртуальний деструктор");
    Worker *worker = new Manager(960, "Temp Manager", "Manager", 50.0, 10, 1,
                                 0.0, 7, "PMO", 1, 5.0, 1000.0, 1);
    std::cout << "  delete через Worker* — деструктор Worker невіртуальний, "
                 "~Manager() не викликається:\n";
    delete worker;
  }

  std::cout << "\n  -- Кінець демонстрації: деструктори реєстру та "
               "статичних об'єктів\n";
}

// [ЛР5, п.8] Зчитування параметрів з консолі з генерацією винятків
std::string PromptLine(const std::string &prompt) {
  std::cout << prompt;
  std::string line;
  if (!std::getline(std::cin >> std::ws, line)) {
    throw std::runtime_error("введення перервано");
  }
  return line;
}

int PromptInt(const std::string &prompt) {
  std::string line = PromptLine(prompt);
  try {
    return std::stoi(line);
  } catch (const std::exception &) {
    throw std::invalid_argument("'" + line + "' не є цілим числом");
  }
}

double PromptDouble(const std::string &prompt) {
  std::string line = PromptLine(prompt);
  try {
    return std::stod(line);
  } catch (const std::exception &) {
    throw std::invalid_argument("'" + line + "' не є числом");
  }
}

// [ЛР5, п.8] Меню створення та знищення об'єктів (ресурсів проєкту)
void RunLab5Menu() {
  ResourceRegistry registry;
  int next_id = 700;
  while (true) {
    std::cout << "\n===== [ЛР5, п.8] Меню ресурсів проєкту =====\n"
              << "  1 - створити Equipment\n"
              << "  2 - створити SoftwareLicense\n"
              << "  3 - створити Material\n"
              << "  4 - створити Workstation\n"
              << "  5 - переглянути всі об'єкти\n"
              << "  6 - детальна інформація про об'єкт\n"
              << "  7 - знищити об'єкт\n"
              << "  0 - вихід\n";
    std::string choice;
    try {
      choice = PromptLine("Ваш вибір: ");
    } catch (const std::runtime_error &) {
      break;
    }
    if (choice == "0") {
      break;
    }
    try {
      if (choice == "1" || choice == "2" || choice == "3" || choice == "4") {
        std::string name = PromptLine("Назва: ");
        int quantity = PromptInt("Кількість: ");
        double price = PromptDouble("Ціна за одиницю ($): ");
        if (quantity <= 0 || price < 0) {
          throw std::invalid_argument("кількість і ціна мають бути додатними");
        }
        int id = next_id++;
        if (choice == "1") {
          registry.AddDynamic(new Equipment(id, name, "Custom", quantity,
                                            price, 2026, "SN-" +
                                            std::to_string(id), 12, 3,
                                            0.05 * price * quantity));
        } else if (choice == "2") {
          registry.AddDynamic(new SoftwareLicense(id, name, "Custom",
                                                  quantity, price, 2026,
                                                  "KEY-" + std::to_string(id),
                                                  12, 0.1 * price));
        } else if (choice == "3") {
          registry.AddDynamic(new Material(id, name, "Custom", quantity,
                                           price, 2026, "pcs", 0, false));
        } else {
          registry.AddDynamic(new Workstation(id, name, "Custom", quantity,
                                              price, "WS-" +
                                              std::to_string(id),
                                              "Linux", 12, 10.0, 2));
        }
      } else if (choice == "5") {
        registry.PrintAll();
      } else if (choice == "6") {
        registry.GetDynamic(PromptInt("Індекс об'єкта: "))->PrintInfo();
      } else if (choice == "7") {
        registry.RemoveDynamic(PromptInt("Індекс об'єкта для знищення: "));
      } else {
        std::cout << "  Невідомий пункт меню\n";
      }
    } catch (const std::exception &e) {
      std::cout << "  [catch] " << e.what() << "\n";
    }
  }
  std::cout << "  Вихід з меню: реєстр знищує динамічні об'єкти, що "
               "залишились\n";
}

// [ЛР5, п.7] Ім'я файлу задається параметром командного рядка
int main(int argc, char *argv[]) {
  std::setlocale(LC_ALL, "");
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  std::string choice;
  std::cout << "Оберіть демонстрацію (3 - ЛР3, 4 - ЛР4, 5 - ЛР5): ";
  std::getline(std::cin, choice);
  std::cout << "\n";

  if (choice == "3") {
    RunLab3Demo();
  } else if (choice == "4") {
    RunLab4Demo();
  } else {
    RunLab5Demo();

    // [ЛР5, п.7] Робота програми з файлом через виклик Service у main()
    std::cout << "\n>>> [ЛР5, п.7] Запис і читання об'єкта через функцію "
                 "Service\n";
    Workstation file_station(800, "QA Workstation", "Asus", 4, 1700.0,
                             "AS-5520", "Windows 11", 24, 12.0, 2);
    try {
      if (argc < 2) {
        throw std::invalid_argument(
            "ім'я файлу не задано в командному рядку (приклад: "
            "./oop_project resources.txt)");
      }
      Service(file_station, argv[1]);
    } catch (const std::invalid_argument &e) {
      std::cout << "  [catch invalid_argument] " << e.what() << "\n";
    } catch (const FileOpenError &e) {
      std::cout << "  [catch FileOpenError] " << e.what() << "\n";
    } catch (const FileFormatError &e) {
      std::cout << "  [catch FileFormatError] " << e.what() << "\n";
    }

    std::cout << "\n>>> [ЛР5, п.7] Виняткові ситуації при роботі з файлами\n";
    DemonstrateFileExceptions(file_station);

    RunLab5Menu();
  }
  return 0;
}
