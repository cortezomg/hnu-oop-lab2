#ifndef LAB4_PROJECT_COORDINATOR_H_
#define LAB4_PROJECT_COORDINATOR_H_

#include <string>

#include "manager.h"
#include "project.h"
#include "worker.h"

// [ЛР4, п.3] ProjectCoordinator — додатковий похідний клас із закритим
// (private) наслідуванням від Manager: координатор розподіляє завдання, але не
// має відкритого доступу до керування бюджетом. Його методи використовують
// методи різних класів ієрархії (Worker -> Manager -> ProjectCoordinator)
class ProjectCoordinator : private Manager {
public:
  ProjectCoordinator();
  ProjectCoordinator(int id, const char *name_str, double rate,
                     const std::string &department, int coordinated_project_id,
                     const std::string &communication_channel,
                     const std::string &tracking_tool,
                     double coordination_rate);
  ProjectCoordinator(const ProjectCoordinator &other);
  ~ProjectCoordinator();

  // [ЛР4, п.6] using відкриває лише потрібні члени базових класів
  using Manager::AssignTask;
  using Worker::name;

  void ScheduleMeeting(const std::string &topic);
  void CoordinateTask(Worker &worker, int tasks, double task_budget);
  void ResolveConflict(const std::string &description);
  void SubmitReport(const Project &project);
  double CalculateSalary() const;
  void PrintInfo() const;

private:
  int coordinated_project_id_;
  std::string communication_channel_;
  std::string tracking_tool_;
  int meetings_held_;
  int reports_submitted_;
  int reminders_sent_;
  int resolved_conflicts_;
  double coordination_rate_;
};

#endif // LAB4_PROJECT_COORDINATOR_H_
