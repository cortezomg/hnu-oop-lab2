#include "budget.h"

#include <iostream>
#include <string>

Budget::Budget()
    : budget_id_(0), budget_name_("Undefined"), currency_("USD"),
      total_amount_(0.0), spent_amount_(0.0), reserved_amount_(0.0),
      fiscal_year_(2026), transactions_count_(0) {
  std::cout << "  [Constructor] Створено об'єкт Budget #" << budget_id_
            << "\n";
}

Budget::Budget(int budget_id, const std::string &budget_name,
               const std::string &currency, double total_amount,
               double spent_amount, double reserved_amount, int fiscal_year)
    : budget_id_(budget_id), budget_name_(budget_name), currency_(currency),
      total_amount_(total_amount), spent_amount_(spent_amount),
      reserved_amount_(reserved_amount), fiscal_year_(fiscal_year),
      transactions_count_(0) {
  std::cout << "  [Constructor] Створено об'єкт Budget #" << budget_id_
            << " (" << budget_name_ << ")\n";
}

Budget::Budget(const Budget &other)
    : budget_id_(other.budget_id_), budget_name_(other.budget_name_),
      currency_(other.currency_), total_amount_(other.total_amount_),
      spent_amount_(other.spent_amount_),
      reserved_amount_(other.reserved_amount_),
      fiscal_year_(other.fiscal_year_),
      transactions_count_(other.transactions_count_) {
  std::cout << "  [Copy Constructor] Створено копію бюджету: " << budget_name_
            << "\n";
}

Budget::~Budget() {
  std::cout << "  [Destructor] Знищено об'єкт Budget #" << budget_id_ << " ("
            << budget_name_ << ")\n";
}

bool Budget::Spend(double amount) {
  if (amount > GetAvailable()) {
    std::cout << "  [Budget] Недостатньо коштів у '" << budget_name_
              << "': потрібно " << amount << " " << currency_ << ", доступно "
              << GetAvailable() << " " << currency_ << "\n";
    return false;
  }
  spent_amount_ += amount;
  transactions_count_++;
  return true;
}

bool Budget::Reserve(double amount) {
  if (amount > GetAvailable()) {
    return false;
  }
  reserved_amount_ += amount;
  transactions_count_++;
  return true;
}

double Budget::GetAvailable() const {
  return total_amount_ - spent_amount_ - reserved_amount_;
}

double Budget::GetUsagePercent() const {
  return (total_amount_ > 0) ? spent_amount_ / total_amount_ * 100.0 : 0.0;
}

void Budget::PrintInfo() const {
  std::cout << "    [Бюджет #" << budget_id_ << "] " << budget_name_ << " ("
            << fiscal_year_ << ") | Всього: " << total_amount_ << " "
            << currency_ << " | Витрачено: " << spent_amount_
            << " | Зарезервовано: " << reserved_amount_
            << " | Доступно: " << GetAvailable()
            << " | Використано: " << GetUsagePercent()
            << "% | Транзакцій: " << transactions_count_ << "\n";
}
