#include "contractor.h"

#include <iostream>
#include <string>

Contractor::Contractor()
    : Worker(), company_("None"), contract_number_("N/A"),
      contract_start_year_(2026), contract_months_(0), fixed_fee_(0.0),
      tax_rate_(0.0), deliverables_count_(0), is_remote_(false) {
  std::cout << "  [Constructor] Створено об'єкт Contractor #" << worker_id
            << "\n";
}

Contractor::Contractor(int id, const char *name_str, double rate, int hours,
                       const std::string &company,
                       const std::string &contract_number, int contract_months,
                       double fixed_fee, double tax_rate, bool is_remote)
    : Worker(id, name_str, "Contractor", rate, hours, 0, 0.0, 5),
      company_(company), contract_number_(contract_number),
      contract_start_year_(2026), contract_months_(contract_months),
      fixed_fee_(fixed_fee), tax_rate_(tax_rate), deliverables_count_(0),
      is_remote_(is_remote) {
  std::cout << "  [Constructor] Створено об'єкт Contractor #" << worker_id
            << " (" << name << ")\n";
}

Contractor::Contractor(const Contractor &other)
    : Worker(other), company_(other.company_),
      contract_number_(other.contract_number_),
      contract_start_year_(other.contract_start_year_),
      contract_months_(other.contract_months_), fixed_fee_(other.fixed_fee_),
      tax_rate_(other.tax_rate_),
      deliverables_count_(other.deliverables_count_),
      is_remote_(other.is_remote_) {
  std::cout << "  [Copy Constructor] Створено копію підрядника: " << name
            << "\n";
}

Contractor::~Contractor() {
  std::cout << "  [Destructor] Знищено об'єкт Contractor #" << worker_id
            << " (" << name << ")\n";
}

double Contractor::CalculateInvoice() const {
  return (Worker::CalculateSalary() + fixed_fee_) * (1.0 + tax_rate_ / 100.0);
}

void Contractor::CompleteDeliverable(double task_budget) {
  UpdateTasks(1, task_budget);
  deliverables_count_++;
  std::cout << "  [Contractor] " << name << ": здано результат №"
            << deliverables_count_ << " за договором " << contract_number_
            << "\n";
}

void Contractor::ExtendContract(int months) {
  contract_months_ += months;
  std::cout << "  [Contractor] Договір " << contract_number_
            << " продовжено до " << contract_months_ << " міс.\n";
}

// [ЛР4, п.2] Доступ до членів Worker зсередини класу при protected-наслідуванні
void Contractor::ShowInheritedAccess() {
  std::cout << "  [Contractor, protected] Дані: worker_id=" << worker_id
            << ", name=" << name << ", role=" << role
            << " | захищені: hourly_rate_=" << hourly_rate_
            << ", hours_worked_=" << hours_worked_
            << ", completed_tasks_=" << completed_tasks_ << "\n";
  UpdateTasks(0);
  std::cout << "  [Contractor, protected] Методи: CalculateSalary()=$"
            << CalculateSalary() << ", Worker::PrintInfo():\n";
  Worker::PrintInfo();
}

void Contractor::PrintInfo() const {
  Worker::PrintInfo();
  std::cout << "    [Підрядник] Компанія: " << company_
            << " | Договір: " << contract_number_ << " ("
            << contract_start_year_ << ", " << contract_months_
            << " міс.) | Фікс. оплата: $" << fixed_fee_
            << " | Податок: " << tax_rate_
            << "% | Здано результатів: " << deliverables_count_
            << " | Віддалено: " << (is_remote_ ? "так" : "ні")
            << " | Рахунок: $" << CalculateInvoice() << "\n";
}
