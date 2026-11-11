#include "team_lead.h"

#include <iostream>
#include <string>

TeamLead::TeamLead()
    : Manager(), Budget(), ResourcePool(), team_name_("Undefined"),
      project_part_("None"), members_{}, member_count_(0), sprint_number_(1),
      standups_held_(0), team_velocity_(0.0), team_rating_(0.0) {
  std::cout << "  [Constructor] Створено об'єкт TeamLead #" << worker_id
            << "\n";
}

// [ЛР4, п.4, п.5] Конструктори базових класів викликаються в порядку їх
// оголошення у списку наслідування: Manager (з Worker), Budget, ResourcePool
TeamLead::TeamLead(int id, const char *name_str, double rate,
                   const std::string &department, const std::string &team_name,
                   const std::string &project_part, double team_budget,
                   int equipment_units, int software_licenses,
                   int material_units)
    : Manager(id, name_str, "Team Lead", rate, 0, 0, 0.0, 8, department, 2,
              10.0, team_budget, 3),
      Budget(id, team_name + " budget", "USD", team_budget, 0.0, 0.0, 2026),
      ResourcePool(id, team_name + " resources", "Main office",
                   equipment_units, software_licenses, material_units),
      team_name_(team_name), project_part_(project_part), members_{},
      member_count_(0), sprint_number_(1), standups_held_(0),
      team_velocity_(0.0), team_rating_(0.0) {
  std::cout << "  [Constructor] Створено об'єкт TeamLead #" << worker_id
            << " (" << name << ")\n";
}

TeamLead::TeamLead(const TeamLead &other)
    : Manager(other), Budget(other), ResourcePool(other),
      team_name_(other.team_name_), project_part_(other.project_part_),
      members_{}, member_count_(other.member_count_),
      sprint_number_(other.sprint_number_),
      standups_held_(other.standups_held_),
      team_velocity_(other.team_velocity_), team_rating_(other.team_rating_) {
  for (int i = 0; i < member_count_; ++i) {
    members_[i] = other.members_[i];
  }
  std::cout << "  [Copy Constructor] Створено копію тімліда: " << name << "\n";
}

TeamLead::~TeamLead() {
  std::cout << "  [Destructor] Знищено об'єкт TeamLead #" << worker_id << " ("
            << name << ")\n";
}

bool TeamLead::AddMember(Worker *member) {
  if (member == nullptr || member_count_ >= kMaxTeamSize) {
    return false;
  }
  members_[member_count_++] = member;
  std::cout << "  [TeamLead] До команди '" << team_name_
            << "' додано: " << member->name << "\n";
  return true;
}

// [ЛР4, п.4, п.6] Об'єкт класу з множинним наслідуванням використовує методи
// різних базових класів: Budget::Spend та Manager::AssignTask
void TeamLead::DistributeWork(int tasks_per_member, double budget_per_member) {
  std::cout << "  [TeamLead] Розподіл частини '" << project_part_
            << "' між членами команди '" << team_name_ << "':\n";
  for (int i = 0; i < member_count_; ++i) {
    if (Budget::Spend(budget_per_member)) {
      Manager::AssignTask(*members_[i], tasks_per_member, budget_per_member);
    }
  }
  team_velocity_ += tasks_per_member * member_count_;
}

void TeamLead::ProvideResources(const Worker &member, int equipment,
                                int licenses, int materials) {
  bool ok = ResourcePool::AllocateEquipment(equipment) &&
            ResourcePool::AllocateLicenses(licenses) &&
            ResourcePool::AllocateMaterials(materials);
  if (ok) {
    std::cout << "  [TeamLead] Ресурси для " << member.name << ": "
              << equipment << " од. обладнання, " << licenses
              << " ліц. ПЗ, " << materials << " од. матеріалів\n";
  }
}

void TeamLead::HoldStandup() {
  standups_held_++;
  team_rating_ = (member_count_ > 0) ? team_velocity_ / member_count_ : 0.0;
  std::cout << "  [TeamLead] Стендап №" << standups_held_ << " команди '"
            << team_name_ << "' (спринт " << sprint_number_ << ")\n";
}

// [ЛР4, п.6] Усунення неоднозначності однойменних методів базових класів
// через оператор області видимості
void TeamLead::PrintInfo() const {
  Manager::PrintInfo();
  Budget::PrintInfo();
  ResourcePool::PrintInfo();
  std::cout << "    [Команда] " << team_name_ << " | Частина проєкту: "
            << project_part_ << " | Учасників: " << member_count_ << "/"
            << kMaxTeamSize << " | Спринт: " << sprint_number_
            << " | Стендапів: " << standups_held_
            << " | Швидкість: " << team_velocity_
            << " | Рейтинг: " << team_rating_ << "\n";
  for (int i = 0; i < member_count_; ++i) {
    std::cout << "      - " << members_[i]->name << " (" << members_[i]->role
              << ")\n";
  }
}
