#ifndef LAB6_EXPENSE_H_
#define LAB6_EXPENSE_H_

#include <iostream>
#include <string>

// [ЛР6, п.6] Expense — користувацький клас (витрата проєкту), який
// використовується як параметр шаблона Catalog<T>. Він визначає операції, яких
// потребують методи шаблона: + (Total), < (FindMax), == (Contains),
// << (Print), а також конструктор за замовчуванням (масив new T[])
class Expense {
public:
  Expense();
  Expense(const std::string &description, const std::string &category,
          double amount);

  Expense operator+(const Expense &other) const;
  bool operator<(const Expense &other) const;
  bool operator==(const Expense &other) const;

  friend std::ostream &operator<<(std::ostream &os, const Expense &expense);

  const std::string &get_description() const { return description_; }
  const std::string &get_category() const { return category_; }
  double get_amount() const { return amount_; }

private:
  std::string description_;
  std::string category_;
  double amount_;
};

#endif // LAB6_EXPENSE_H_
