#ifndef LAB4_BUDGET_H_
#define LAB4_BUDGET_H_

#include <string>

// [ЛР4, п.4] Budget — перший додатковий базовий клас для множинного
// наслідування (бюджет, що відстежує витрати)
class Budget {
public:
  Budget();
  // [ЛР4, п.5] Конструктор базового класу з 7 параметрами
  Budget(int budget_id, const std::string &budget_name,
         const std::string &currency, double total_amount, double spent_amount,
         double reserved_amount, int fiscal_year);
  Budget(const Budget &other);
  ~Budget();

  bool Spend(double amount);
  bool Reserve(double amount);
  double GetAvailable() const;
  double GetUsagePercent() const;
  void PrintInfo() const;

  double get_total_amount() const { return total_amount_; }
  double get_spent_amount() const { return spent_amount_; }

private:
  int budget_id_;
  std::string budget_name_;
  std::string currency_;
  double total_amount_;
  double spent_amount_;
  double reserved_amount_;
  int fiscal_year_;
  int transactions_count_;
};

#endif // LAB4_BUDGET_H_
