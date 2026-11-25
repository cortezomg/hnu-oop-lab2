#include "stl_demo.h"

#include <algorithm>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "block_tracker.h"
#include "expense.h"
#include "project_task.h"

namespace {

using std::placeholders::_1;

template <typename Container>
void PrintInline(const std::string &label, const Container &items) {
  std::cout << "    " << label << ": ";
  bool first = true;
  for (const auto &item : items) {
    std::cout << (first ? "" : ", ") << item;
    first = false;
  }
  std::cout << "\n";
}

template <typename Container>
void PrintLines(const std::string &label, const Container &items) {
  std::cout << "    " << label << ":\n";
  for (const auto &item : items) {
    std::cout << "      " << item << "\n";
  }
}

const char *YesNo(bool value) { return value ? "так" : "ні"; }

// [ЛР7, п.2] Категорія ітератора визначається через std::iterator_traits
template <typename Iterator>
const char *IteratorCategory() {
  using Category = typename std::iterator_traits<Iterator>::iterator_category;
  if constexpr (std::is_same_v<Category, std::random_access_iterator_tag>) {
    return "random access (довільного доступу)";
  } else if constexpr (std::is_same_v<Category,
                                      std::bidirectional_iterator_tag>) {
    return "bidirectional (двонаправлений)";
  } else if constexpr (std::is_same_v<Category, std::forward_iterator_tag>) {
    return "forward (односпрямований)";
  } else if constexpr (std::is_same_v<Category, std::input_iterator_tag>) {
    return "input (вхідний)";
  } else {
    return "output (вихідний)";
  }
}

std::vector<ProjectTask> MakeTasks() {
  return {
      ProjectTask(1, "Схема бази даних", "Олена Мороз", 4, 16),
      ProjectTask(2, "REST API проєктів", "Максим Кравець", 5, 24),
      ProjectTask(3, "Макети інтерфейсу", "Софія Бойко", 3, 12),
      ProjectTask(4, "Звіт для замовника", "Олена Мороз", 2, 6),
      ProjectTask(5, "Автотести бюджету", "Ірина Савчук", 4, 10),
      ProjectTask(6, "Налаштування CI", "Тарас Гнатюк", 3, 8),
  };
}

// ============================================================================
// [ЛР7, п.1] Контейнери послідовностей та асоціативні контейнери STL
// ============================================================================
void DemonstrateContainers() {
  std::cout << "\n>>> [ЛР7, п.1.1] vector<Expense> — витрати додаються в "
               "кінець\n";
  std::vector<Expense> expenses;
  expenses.push_back(Expense("Хмарний хостинг", "Інфраструктура", 1200.0));
  expenses.push_back(Expense("Ліцензії IDE", "Програмне забезпечення", 1450.0));
  expenses.push_back(Expense("Сервер", "Інфраструктура", 5400.0));
  expenses.push_back(Expense("Помилковий запис", "Інше", 1.0));
  PrintLines("push_back x4", expenses);
  std::cout << "    at(2): " << expenses.at(2) << "\n";
  try {
    std::cout << expenses.at(10) << "\n";
  } catch (const std::out_of_range &) {
    std::cout << "    at(10): [catch out_of_range] індекс поза межами\n";
  }
  expenses.pop_back();
  std::cout << "    pop_back() — останній запис видалено, size() = "
            << expenses.size() << "\n";

  std::cout << "\n>>> [ЛР7, п.1.2] list<ProjectTask> — беклог, вставка й "
               "видалення в будь-якому місці\n";
  std::list<ProjectTask> backlog;
  backlog.push_back(ProjectTask(10, "Сторінка звітів", "Софія Бойко", 3, 14));
  backlog.push_back(ProjectTask(11, "Експорт у PDF", "Максим Кравець", 2, 8));
  backlog.push_back(ProjectTask(12, "Сповіщення", "Тарас Гнатюк", 2, 6));
  PrintLines("push_back x3", backlog);
  auto second = std::next(backlog.begin());
  backlog.insert(second, ProjectTask(13, "Виправити вхід", "Ірина Савчук", 5,
                                     3));
  PrintLines("insert(перед 2-м елементом) — без зсуву інших елементів",
             backlog);
  backlog.remove(ProjectTask(11, "", "", 0, 0));
  PrintLines("remove(задача #11) — порівняння через operator==", backlog);

  std::cout << "\n>>> [ЛР7, п.1.3] deque<std::string> — звернення до "
               "підтримки: термінові на початок, звичайні в кінець\n";
  std::deque<std::string> support;
  support.push_back("Питання про рахунок");
  support.push_back("Доступ до звіту");
  support.push_front("ТЕРМІНОВО: сервер недоступний");
  PrintInline("push_back x2, push_front", support);
  std::cout << "    pop_front() обробляє: " << support.front() << "\n";
  support.pop_front();
  PrintInline("залишились", support);

  std::cout << "\n>>> [ЛР7, п.1.4] set<std::string> — унікальні навички "
               "команди, відсортовані\n";
  std::set<std::string> skills;
  for (const char *skill : {"C++", "SQL", "Git", "Docker", "C++"}) {
    bool added = skills.insert(skill).second;
    std::cout << "    insert(\"" << skill << "\"): "
              << (added ? "додано" : "вже є, не додано") << "\n";
  }
  PrintInline("set", skills);
  std::cout << "    find(\"Git\"): "
            << (skills.find("Git") != skills.end() ? "знайдено" : "немає")
            << "\n";
  skills.erase("Docker");
  PrintInline("erase(\"Docker\")", skills);

  std::cout << "\n>>> [ЛР7, п.1.5] multiset<int> — оцінки задач у story "
               "points (повтори дозволені)\n";
  std::multiset<int> points;
  for (int estimate : {5, 3, 8, 5, 13, 5, 2}) {
    points.insert(estimate);
  }
  PrintInline("insert x7", points);
  std::cout << "    count(5) = " << points.count(5) << "\n";
  points.erase(points.find(5));
  PrintInline("erase(find(5)) — видалено одну копію", points);

  std::cout << "\n>>> [ЛР7, п.1.6] map<int, std::string> — довідник "
               "робітників: номер -> ім'я\n";
  std::map<int, std::string> directory;
  directory[120] = "Ірина Савчук";
  directory[110] = "Максим Кравець";
  directory.insert({121, "Тарас Гнатюк"});
  directory[110] = "Максим Кравець (Team Lead)";
  for (const auto &entry : directory) {
    std::cout << "    [" << entry.first << "] " << entry.second << "\n";
  }
  auto found = directory.find(121);
  std::cout << "    find(121): "
            << (found != directory.end() ? found->second : "немає") << "\n";
  directory.erase(120);
  std::cout << "    erase(120), size() = " << directory.size() << "\n";

  std::cout << "\n>>> [ЛР7, п.1.7] multimap<std::string, ProjectTask> — "
               "виконавець -> задачі (ключі повторюються)\n";
  std::multimap<std::string, ProjectTask> by_assignee;
  for (const ProjectTask &task : MakeTasks()) {
    by_assignee.insert({task.get_assignee(), task});
  }
  std::cout << "    count(\"Олена Мороз\") = "
            << by_assignee.count("Олена Мороз") << "\n";
  auto range = by_assignee.equal_range("Олена Мороз");
  std::cout << "    equal_range(\"Олена Мороз\"):\n";
  for (auto it = range.first; it != range.second; ++it) {
    std::cout << "      " << it->second << "\n";
  }

  std::cout << "\n>>> [ЛР7, п.1.8] stack<std::string> — історія змін "
               "бюджету, скасування з кінця\n";
  std::stack<std::string> history;
  history.push("+5000 USD фінансування");
  history.push("-1200 USD хостинг");
  history.push("*1.1 індексація");
  std::cout << "    push x3, top(): " << history.top() << "\n";
  history.pop();
  std::cout << "    pop() скасовує останню зміну, top(): " << history.top()
            << "\n";

  std::cout << "\n>>> [ЛР7, п.1.9] queue<ProjectTask> — черга на code review "
               "(в порядку надходження)\n";
  std::queue<ProjectTask> review;
  std::vector<ProjectTask> tasks = MakeTasks();
  review.push(tasks[1]);
  review.push(tasks[4]);
  review.push(tasks[5]);
  while (!review.empty()) {
    std::cout << "    front(): " << review.front() << " -> pop()\n";
    review.pop();
  }

  std::cout << "\n>>> [ЛР7, п.1.10] priority_queue<ProjectTask> — задачі за "
               "пріоритетом (operator<)\n";
  std::priority_queue<ProjectTask> by_priority;
  for (const ProjectTask &task : tasks) {
    by_priority.push(task);
  }
  while (!by_priority.empty()) {
    std::cout << "    top(): " << by_priority.top() << " -> pop()\n";
    by_priority.pop();
  }
}

// ============================================================================
// [ЛР7, п.2] Ітератори
// ============================================================================
void DemonstrateIterators() {
  std::cout << "\n>>> [ЛР7, п.2.1] Вхідний ітератор istream_iterator — "
               "читання годин з потоку (один прохід)\n";
  std::istringstream timesheet("8 6 7 5 9");
  std::istream_iterator<int> input_begin(timesheet);
  std::istream_iterator<int> input_end;
  std::vector<int> logged_hours(input_begin, input_end);
  std::cout << "    Категорія: "
            << IteratorCategory<std::istream_iterator<int>>() << "\n";
  PrintInline("прочитано", logged_hours);

  std::cout << "\n>>> [ЛР7, п.2.2] Вихідні ітератори ostream_iterator і "
               "back_inserter — лише запис\n";
  std::set<std::string> roles = {"Developer", "Designer", "QA", "Manager"};
  std::cout << "    Категорія: "
            << IteratorCategory<std::ostream_iterator<std::string>>() << "\n";
  std::cout << "    copy(set -> ostream_iterator): ";
  std::copy(roles.begin(), roles.end(),
            std::ostream_iterator<std::string>(std::cout, " | "));
  std::cout << "\n";
  std::vector<std::string> role_list;
  std::copy(roles.begin(), roles.end(), std::back_inserter(role_list));
  std::cout << "    copy(set -> back_inserter(vector)), size() = "
            << role_list.size() << ", категорія: "
            << IteratorCategory<
                   std::back_insert_iterator<std::vector<std::string>>>()
            << "\n";

  std::cout << "\n>>> [ЛР7, п.2.3] Односпрямований ітератор forward_list — "
               "лише ++\n";
  std::forward_list<std::string> milestones = {"Аналіз", "Розробка", "Реліз"};
  milestones.insert_after(milestones.begin(), "Проєктування");
  std::cout << "    Категорія: "
            << IteratorCategory<std::forward_list<std::string>::iterator>()
            << "\n";
  std::cout << "    Етапи:";
  for (auto it = milestones.begin(); it != milestones.end(); ++it) {
    std::cout << " " << *it;
  }
  std::cout << "\n";

  std::cout << "\n>>> [ЛР7, п.2.4] Двонаправлений ітератор list — ++ та --\n";
  std::vector<ProjectTask> tasks = MakeTasks();
  std::list<ProjectTask> backlog(tasks.begin(), tasks.begin() + 3);
  std::cout << "    Категорія: "
            << IteratorCategory<std::list<ProjectTask>::iterator>() << "\n";
  std::cout << "    Обхід з кінця (--it):\n";
  for (auto it = backlog.end(); it != backlog.begin();) {
    --it;
    std::cout << "      " << *it << "\n";
  }

  std::cout << "\n>>> [ЛР7, п.2.5] Ітератор довільного доступу vector — "
               "арифметика ітераторів\n";
  std::cout << "    Категорія: "
            << IteratorCategory<std::vector<ProjectTask>::iterator>() << "\n";
  auto first = tasks.begin();
  auto last = tasks.end();
  std::cout << "    first[2]: " << first[2] << "\n";
  std::cout << "    *(first + 4): " << *(first + 4) << "\n";
  std::cout << "    last - first = " << (last - first) << " елементів\n";
  std::cout << "    first + 3 < last: " << YesNo(first + 3 < last) << "\n";
}

// ============================================================================
// [ЛР7, п.3] П'ять алгоритмів STL
// ============================================================================
void DemonstrateAlgorithms() {
  std::vector<ProjectTask> tasks = MakeTasks();

  std::cout << "\n>>> [ЛР7, п.3] Алгоритм 1: sort — задачі за кількістю "
               "годин\n";
  std::sort(tasks.begin(), tasks.end(),
            [](const ProjectTask &a, const ProjectTask &b) {
              return a.get_hours() < b.get_hours();
            });
  PrintLines("після sort", tasks);

  std::cout << "\n>>> [ЛР7, п.3] Алгоритм 2: find_if — перша задача з "
               "пріоритетом 5\n";
  auto urgent = std::find_if(tasks.begin(), tasks.end(),
                             [](const ProjectTask &task) {
                               return task.get_priority() == 5;
                             });
  if (urgent != tasks.end()) {
    std::cout << "    знайдено: " << *urgent << "\n";
  }

  std::cout << "\n>>> [ЛР7, п.3] Алгоритм 3: count_if — задачі з пріоритетом "
               "4 і вище\n";
  auto important = std::count_if(tasks.begin(), tasks.end(),
                                 [](const ProjectTask &task) {
                                   return task.get_priority() >= 4;
                                 });
  std::cout << "    кількість: " << important << "\n";

  std::cout << "\n>>> [ЛР7, п.3] Алгоритм 4: accumulate — загальна "
               "трудомісткість\n";
  int total_hours = std::accumulate(tasks.begin(), tasks.end(), 0,
                                    [](int sum, const ProjectTask &task) {
                                      return sum + task.get_hours();
                                    });
  std::cout << "    разом годин: " << total_hours << "\n";

  std::cout << "\n>>> [ЛР7, п.3] Алгоритм 5: transform — вартість кожної "
               "задачі за ставкою 40 USD/год\n";
  std::vector<double> costs(tasks.size());
  std::transform(tasks.begin(), tasks.end(), costs.begin(),
                 [](const ProjectTask &task) {
                   return task.get_hours() * 40.0;
                 });
  PrintInline("вартість, USD", costs);
}

// ============================================================================
// [ЛР7, п.4] Функціональні об'єкти (функтори)
// ============================================================================
void DemonstrateFunctors() {
  std::cout << "\n>>> [ЛР7, п.4] Власний функтор AssignedTo\n";
  std::vector<ProjectTask> tasks = MakeTasks();
  AssignedTo olena("Олена Мороз");
  std::cout << "    count_if(AssignedTo(\"Олена Мороз\")) = "
            << std::count_if(tasks.begin(), tasks.end(), olena) << "\n";
  std::list<ProjectTask> backlog(tasks.begin(), tasks.end());
  backlog.remove_if(olena);
  std::cout << "    list::remove_if(AssignedTo(\"Олена Мороз\")), size() = "
            << backlog.size() << "\n";

  // [ЛР7, п.4.1] Арифметичні функтори (у стандарті віднімання — minus,
  // множення — multiplies)
  std::cout << "\n>>> [ЛР7, п.4.1] Арифметичні функтори\n";
  std::vector<double> hours = {16, 24, 12, 6};
  std::vector<double> rates = {40, 45, 38, 30};
  std::vector<double> cost(hours.size());
  std::transform(hours.begin(), hours.end(), rates.begin(), cost.begin(),
                 std::multiplies<double>());
  PrintInline("multiplies: години * ставка", cost);
  double total = std::accumulate(cost.begin(), cost.end(), 0.0,
                                 std::plus<double>());
  std::cout << "    plus (accumulate): разом " << total << " USD\n";
  std::vector<double> limits = {700, 1000, 500, 200};
  std::vector<double> remaining(limits.size());
  std::transform(limits.begin(), limits.end(), cost.begin(), remaining.begin(),
                 std::minus<double>());
  PrintInline("minus: ліміт - вартість", remaining);
  std::vector<double> days(hours.size());
  std::transform(hours.begin(), hours.end(), days.begin(),
                 std::bind(std::divides<double>(), _1, 8.0));
  PrintInline("divides: години / 8 = робочі дні", days);
  std::vector<int> whole_hours = {16, 26, 12, 7};
  std::vector<int> leftover(whole_hours.size());
  std::transform(whole_hours.begin(), whole_hours.end(), leftover.begin(),
                 std::bind(std::modulus<int>(), _1, 8));
  PrintInline("modulus: години % 8 = години понад повні дні", leftover);
  std::vector<double> refunds = {150, 75.5, 300};
  std::transform(refunds.begin(), refunds.end(), refunds.begin(),
                 std::negate<double>());
  PrintInline("negate: повернення коштів як від'ємні суми", refunds);

  // [ЛР7, п.4.2] Функтори порівняння
  std::cout << "\n>>> [ЛР7, п.4.2] Функтори порівняння (оцінки задач у story "
               "points)\n";
  std::vector<int> points = {5, 3, 8, 5, 13, 2, 8};
  PrintInline("оцінки", points);
  std::cout << "    equal_to 5: "
            << std::count_if(points.begin(), points.end(),
                             std::bind(std::equal_to<int>(), _1, 5))
            << ", not_equal_to 5: "
            << std::count_if(points.begin(), points.end(),
                             std::bind(std::not_equal_to<int>(), _1, 5))
            << "\n";
  std::cout << "    greater_equal 8 (варто розбити): "
            << std::count_if(points.begin(), points.end(),
                             std::bind(std::greater_equal<int>(), _1, 8))
            << ", less_equal 3 (дрібні): "
            << std::count_if(points.begin(), points.end(),
                             std::bind(std::less_equal<int>(), _1, 3))
            << "\n";
  std::sort(points.begin(), points.end(), std::greater<int>());
  PrintInline("sort(greater) — спадання", points);
  std::sort(points.begin(), points.end(), std::less<int>());
  PrintInline("sort(less) — зростання", points);
  std::set<std::string, std::greater<std::string>> reversed = {"Аналіз",
                                                               "Реліз",
                                                               "Тести"};
  PrintInline("set<string, greater> — зворотний порядок", reversed);

  // [ЛР7, п.4.3] Логічні функтори
  std::cout << "\n>>> [ЛР7, п.4.3] Логічні функтори (стан задач #1-#4)\n";
  std::vector<bool> done = {true, false, true, true};
  std::vector<bool> reviewed = {true, false, false, true};
  std::vector<bool> blocked = {false, true, false, false};
  std::vector<bool> ready(done.size());
  std::vector<bool> pending(done.size());
  std::vector<bool> attention(done.size());
  std::transform(done.begin(), done.end(), reviewed.begin(), ready.begin(),
                 std::logical_and<bool>());
  std::transform(done.begin(), done.end(), pending.begin(),
                 std::logical_not<bool>());
  std::transform(pending.begin(), pending.end(), blocked.begin(),
                 attention.begin(), std::logical_or<bool>());
  for (std::size_t i = 0; i < done.size(); ++i) {
    std::cout << "    #" << i + 1 << ": виконано " << YesNo(done[i])
              << ", перевірено " << YesNo(reviewed[i]) << ", заблоковано "
              << YesNo(blocked[i]) << "\n";
    std::cout << "        and: готово до релізу " << YesNo(ready[i])
              << " | not: не виконано " << YesNo(pending[i])
              << " | or: потребує уваги " << YesNo(attention[i]) << "\n";
  }
}

}  // namespace

void RunLab7Demo() {
  std::cout << "==============================================================="
               "=========\n";
  std::cout << "    ЛАБОРАТОРНА РОБОТА №7 - БІБЛІОТЕКА STL (МЕНЕДЖМЕНТ ПРОЄКТУ)"
               "         \n";
  std::cout << "==============================================================="
               "=========\n\n";
  BlockTracker demo_block("RunLab7Demo");
  DemonstrateContainers();
  DemonstrateIterators();
  DemonstrateAlgorithms();
  DemonstrateFunctors();
  std::cout << "\n>>> Кінець демонстрації ЛР7\n";
}
