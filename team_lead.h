#ifndef LAB4_TEAM_LEAD_H_
#define LAB4_TEAM_LEAD_H_

#include <string>

#include "budget.h"
#include "manager.h"
#include "resource_pool.h"
#include "worker.h"

// [ЛР4, п.4] TeamLead — третій додатковий клас, множинне наслідування від
// Manager (наявна ієрархія), Budget та ResourcePool: керівник команди
// розподіляє завдання, бюджет і ресурси між робітниками команди
class TeamLead : public Manager, public Budget, public ResourcePool {
public:
  static constexpr int kMaxTeamSize = 5;

  TeamLead();
  // [ЛР4, п.5] Конструктор використовує всі свої параметри, передаючи їх
  // конструкторам трьох базових класів
  TeamLead(int id, const char *name_str, double rate,
           const std::string &department, const std::string &team_name,
           const std::string &project_part, double team_budget,
           int equipment_units, int software_licenses, int material_units);
  TeamLead(const TeamLead &other);
  ~TeamLead();

  bool AddMember(Worker *member);
  void DistributeWork(int tasks_per_member, double budget_per_member);
  void ProvideResources(const Worker &member, int equipment, int licenses,
                        int materials);
  void HoldStandup();
  void PrintInfo() const;

private:
  std::string team_name_;
  std::string project_part_;
  Worker *members_[kMaxTeamSize];
  int member_count_;
  int sprint_number_;
  int standups_held_;
  double team_velocity_;
  double team_rating_;
};

#endif // LAB4_TEAM_LEAD_H_
