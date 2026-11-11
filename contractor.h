#ifndef LAB4_CONTRACTOR_H_
#define LAB4_CONTRACTOR_H_

#include <string>

#include "worker.h"

// [ЛР4, п.1, п.2] Contractor — захищене (protected) наслідування від Worker:
// відкриті члени Worker стають захищеними і недоступні ззовні
class Contractor : protected Worker {
public:
  Contractor();
  Contractor(int id, const char *name_str, double rate, int hours,
             const std::string &company, const std::string &contract_number,
             int contract_months, double fixed_fee, double tax_rate,
             bool is_remote);
  Contractor(const Contractor &other);
  ~Contractor();

  // [ЛР4, п.6] using відновлює відкритий доступ до окремих членів Worker
  using Worker::name;
  using Worker::worker_id;

  double CalculateInvoice() const;
  void CompleteDeliverable(double task_budget);
  void ExtendContract(int months);
  void ShowInheritedAccess();
  void PrintInfo() const;

private:
  std::string company_;
  std::string contract_number_;
  int contract_start_year_;
  int contract_months_;
  double fixed_fee_;
  double tax_rate_;
  int deliverables_count_;
  bool is_remote_;
};

#endif // LAB4_CONTRACTOR_H_
