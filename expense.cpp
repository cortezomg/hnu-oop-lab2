#include "expense.h"

#include <iostream>
#include <string>

Expense::Expense()
    : description_("Без опису"), category_("Інше"), amount_(0.0) {}

Expense::Expense(const std::string &description, const std::string &category,
                 double amount)
    : description_(description), category_(category), amount_(amount) {}

Expense Expense::operator+(const Expense &other) const {
  const std::string category =
      (category_ == other.category_) ? category_ : "Різне";
  return Expense("Разом", category, amount_ + other.amount_);
}

bool Expense::operator<(const Expense &other) const {
  return amount_ < other.amount_;
}

bool Expense::operator==(const Expense &other) const {
  return description_ == other.description_ &&
         category_ == other.category_ && amount_ == other.amount_;
}

std::ostream &operator<<(std::ostream &os, const Expense &expense) {
  os << expense.description_ << " [" << expense.category_ << "] "
     << expense.amount_ << " USD";
  return os;
}
