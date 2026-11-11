#include "intern.h"

#include <iostream>
#include <string>

Intern::Intern()
    : Worker(), university_("None"), specialty_("None"), course_year_(1),
      internship_weeks_(0), stipend_(0.0), mentor_id_(0),
      learned_skills_count_(0), is_paid_(false) {
  std::cout << "  [Constructor] Створено об'єкт Intern #" << worker_id << "\n";
}

Intern::Intern(int id, const char *name_str, double rate,
               const std::string &university, const std::string &specialty,
               int course_year, int internship_weeks, double stipend,
               int mentor_id)
    : Worker(id, name_str, "Intern", rate, 0, 0, 0.0, 5),
      university_(university), specialty_(specialty),
      course_year_(course_year), internship_weeks_(internship_weeks),
      stipend_(stipend), mentor_id_(mentor_id), learned_skills_count_(0),
      is_paid_(stipend > 0.0) {
  std::cout << "  [Constructor] Створено об'єкт Intern #" << worker_id << " ("
            << name << ")\n";
}

Intern::Intern(const Intern &other)
    : Worker(other), university_(other.university_),
      specialty_(other.specialty_), course_year_(other.course_year_),
      internship_weeks_(other.internship_weeks_), stipend_(other.stipend_),
      mentor_id_(other.mentor_id_),
      learned_skills_count_(other.learned_skills_count_),
      is_paid_(other.is_paid_) {
  std::cout << "  [Copy Constructor] Створено копію стажера: " << name << "\n";
}

Intern::~Intern() {
  std::cout << "  [Destructor] Знищено об'єкт Intern #" << worker_id << " ("
            << name << ")\n";
}

void Intern::CompleteTrainingTask() {
  UpdateTasks(1);
  learned_skills_count_++;
  std::cout << "  [Intern] " << name
            << ": виконано навчальне завдання (навичок: "
            << learned_skills_count_ << ")\n";
}

double Intern::CalculateStipend() const {
  return stipend_ + Worker::CalculateSalary();
}

void Intern::ExtendInternship(int weeks) {
  internship_weeks_ += weeks;
  std::cout << "  [Intern] Стажування " << name << " продовжено до "
            << internship_weeks_ << " тиж.\n";
}

// [ЛР4, п.2] Доступ до членів Worker зсередини класу при private-наслідуванні
void Intern::ShowInheritedAccess() {
  std::cout << "  [Intern, private] Дані: worker_id=" << worker_id
            << ", name=" << name << ", role=" << role
            << " | захищені: hourly_rate_=" << hourly_rate_
            << ", hours_worked_=" << hours_worked_
            << ", completed_tasks_=" << completed_tasks_ << "\n";
  UpdateTasks(0);
  std::cout << "  [Intern, private] Методи: CalculateSalary()=$"
            << CalculateSalary() << ", Worker::PrintInfo():\n";
  Worker::PrintInfo();
}

void Intern::PrintInfo() const {
  Worker::PrintInfo();
  std::cout << "    [Стажер] ЗВО: " << university_
            << " | Спеціальність: " << specialty_ << " | Курс: " << course_year_
            << " | Тижнів стажування: " << internship_weeks_
            << " | Стипендія: $" << stipend_ << " | Ментор #" << mentor_id_
            << " | Навичок: " << learned_skills_count_
            << " | Оплачуване: " << (is_paid_ ? "так" : "ні")
            << " | До виплати: $" << CalculateStipend() << "\n";
}
