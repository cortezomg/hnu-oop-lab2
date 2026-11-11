#include "project_coordinator.h"

#include <iostream>
#include <string>

ProjectCoordinator::ProjectCoordinator()
    : Manager(), coordinated_project_id_(0), communication_channel_("None"),
      tracking_tool_("None"), meetings_held_(0), reports_submitted_(0),
      reminders_sent_(0), resolved_conflicts_(0), coordination_rate_(0.0) {
  std::cout << "  [Constructor] Створено об'єкт ProjectCoordinator #"
            << worker_id << "\n";
}

// [ЛР4, п.5] Передача параметрів конструктору базового класу Manager, який
// своєю чергою передає їх конструктору Worker
ProjectCoordinator::ProjectCoordinator(
    int id, const char *name_str, double rate, const std::string &department,
    int coordinated_project_id, const std::string &communication_channel,
    const std::string &tracking_tool, double coordination_rate)
    : Manager(id, name_str, "Project Coordinator", rate, 0, 0, 0.0, 7,
              department, 1, 5.0, 0.0, 2),
      coordinated_project_id_(coordinated_project_id),
      communication_channel_(communication_channel),
      tracking_tool_(tracking_tool), meetings_held_(0), reports_submitted_(0),
      reminders_sent_(0), resolved_conflicts_(0),
      coordination_rate_(coordination_rate) {
  std::cout << "  [Constructor] Створено об'єкт ProjectCoordinator #"
            << worker_id << " (" << name << ")\n";
}

ProjectCoordinator::ProjectCoordinator(const ProjectCoordinator &other)
    : Manager(other), coordinated_project_id_(other.coordinated_project_id_),
      communication_channel_(other.communication_channel_),
      tracking_tool_(other.tracking_tool_),
      meetings_held_(other.meetings_held_),
      reports_submitted_(other.reports_submitted_),
      reminders_sent_(other.reminders_sent_),
      resolved_conflicts_(other.resolved_conflicts_),
      coordination_rate_(other.coordination_rate_) {
  std::cout << "  [Copy Constructor] Створено копію координатора: " << name
            << "\n";
}

ProjectCoordinator::~ProjectCoordinator() {
  std::cout << "  [Destructor] Знищено об'єкт ProjectCoordinator #"
            << worker_id << " (" << name << ")\n";
}

void ProjectCoordinator::ScheduleMeeting(const std::string &topic) {
  meetings_held_++;
  hours_worked_ += 1;
  std::cout << "  [Coordinator] Мітинг №" << meetings_held_ << " \"" << topic
            << "\" у " << communication_channel_ << "\n";
}

// [ЛР4, п.3] Об'єкт закритого похідного класу оперує методами різних класів
// ієрархії: Manager::AssignTask та Worker::UpdateTasks
void ProjectCoordinator::CoordinateTask(Worker &worker, int tasks,
                                        double task_budget) {
  Manager::AssignTask(worker, tasks, task_budget);
  Worker::UpdateTasks(1);
  reminders_sent_++;
  std::cout << "  [Coordinator] Завдання відстежується в " << tracking_tool_
            << ", нагадувань надіслано: " << reminders_sent_ << "\n";
}

void ProjectCoordinator::ResolveConflict(const std::string &description) {
  resolved_conflicts_++;
  std::cout << "  [Coordinator] Вирішено конфлікт: " << description << "\n";
}

void ProjectCoordinator::SubmitReport(const Project &project) {
  reports_submitted_++;
  std::cout << "  [Coordinator] Звіт №" << reports_submitted_
            << " по проєкту '" << project.title << "' (статус: "
            << project.status << ", витрати: $"
            << project.get_current_expenses() << ")\n";
}

// [ЛР4, п.6] Ланцюжок викликів через оператор області видимості:
// ProjectCoordinator -> Manager::CalculateSalary -> Worker::CalculateSalary
double ProjectCoordinator::CalculateSalary() const {
  return Manager::CalculateSalary() + coordination_rate_ * meetings_held_;
}

void ProjectCoordinator::PrintInfo() const {
  Manager::PrintInfo();
  std::cout << "    [Координатор] Проєкт #" << coordinated_project_id_
            << " | Канал: " << communication_channel_
            << " | Трекер: " << tracking_tool_
            << " | Мітингів: " << meetings_held_
            << " | Звітів: " << reports_submitted_
            << " | Нагадувань: " << reminders_sent_
            << " | Вирішено конфліктів: " << resolved_conflicts_
            << " | Ставка координації: $" << coordination_rate_
            << " | Зарплата: $" << CalculateSalary() << "\n";
}
