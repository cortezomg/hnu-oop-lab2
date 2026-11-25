#include "budget.h"

#include <iostream>
#include <stdexcept>
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

// [ЛР6, п.2] Бінарний + : об'єднання бюджетів однієї валюти в новий об'єкт
Budget Budget::operator+(const Budget &other) const {
  if (currency_ != other.currency_) {
    throw std::invalid_argument("Budget +: не можна об'єднати бюджети в "
                                "різних валютах (" +
                                currency_ + " і " + other.currency_ + ")");
  }
  Budget result(*this);
  result.budget_name_ = budget_name_ + " + " + other.budget_name_;
  result.total_amount_ += other.total_amount_;
  result.spent_amount_ += other.spent_amount_;
  result.reserved_amount_ += other.reserved_amount_;
  result.transactions_count_ += other.transactions_count_;
  return result;
}

// [ЛР6, п.2] Бінарні + та - з числом реалізовано через += та -=;
// вихідний об'єкт не змінюється
Budget Budget::operator+(double amount) const {
  Budget result(*this);
  result += amount;
  return result;
}

Budget Budget::operator-(double amount) const {
  Budget result(*this);
  result -= amount;
  return result;
}

// [ЛР6, п.3] Оператор * : новий бюджет, проіндексований на коефіцієнт
Budget Budget::operator*(double factor) const {
  Budget result(*this);
  result *= factor;
  return result;
}

// [ЛР6, п.3] Оператор присвоєння: перевірка самоприсвоєння, повернення *this
// для ланцюжка a = b = c
Budget &Budget::operator=(const Budget &other) {
  if (this != &other) {
    budget_id_ = other.budget_id_;
    budget_name_ = other.budget_name_;
    currency_ = other.currency_;
    total_amount_ = other.total_amount_;
    spent_amount_ = other.spent_amount_;
    reserved_amount_ = other.reserved_amount_;
    fiscal_year_ = other.fiscal_year_;
    transactions_count_ = other.transactions_count_;
    std::cout << "  [operator=] Бюджету присвоєно значення '" << budget_name_
              << "'\n";
  } else {
    std::cout << "  [operator=] Самоприсвоєння '" << budget_name_
              << "' — копіювання пропущено\n";
  }
  return *this;
}

// [ЛР6, п.3] Складені оператори змінюють сам об'єкт і повертають посилання
Budget &Budget::operator+=(double amount) {
  if (amount < 0) {
    throw std::invalid_argument("Budget +=: сума не може бути від'ємною");
  }
  total_amount_ += amount;
  transactions_count_++;
  return *this;
}

Budget &Budget::operator-=(double amount) {
  if (amount < 0) {
    throw std::invalid_argument("Budget -=: сума не може бути від'ємною");
  }
  if (total_amount_ - amount < spent_amount_ + reserved_amount_) {
    throw std::invalid_argument("Budget -=: не можна скоротити '" +
                                budget_name_ +
                                "' нижче витрачених і зарезервованих коштів");
  }
  total_amount_ -= amount;
  transactions_count_++;
  return *this;
}

Budget &Budget::operator*=(double factor) {
  if (factor <= 0) {
    throw std::invalid_argument("Budget *=: коефіцієнт має бути додатним");
  }
  if (total_amount_ * factor < spent_amount_ + reserved_amount_) {
    throw std::invalid_argument("Budget *=: не можна скоротити '" +
                                budget_name_ +
                                "' нижче витрачених і зарезервованих коштів");
  }
  total_amount_ *= factor;
  transactions_count_++;
  return *this;
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
