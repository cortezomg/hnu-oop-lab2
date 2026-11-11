#ifndef LAB4_CUSTOMER_H_
#define LAB4_CUSTOMER_H_

#include <string>

#include "manager.h"
#include "project.h"

// [ЛР4, п.1, п.9] Customer — замовник, який замовляє проєкт у менеджера
class Customer {
public:
  Customer();
  Customer(int customer_id, const std::string &company_name,
           const std::string &contact_person, const std::string &email,
           const std::string &phone, const std::string &country);
  Customer(const Customer &other);
  ~Customer();

  void OrderProject(Project &project, Manager &manager);
  void PayInvoice(double amount);
  void ReviewProject(const Project &project) const;
  void PrintInfo() const;

  double get_total_paid() const { return total_paid_; }

private:
  int customer_id_;
  std::string company_name_;
  std::string contact_person_;
  std::string email_;
  std::string phone_;
  std::string country_;
  int orders_count_;
  double total_paid_;
};

#endif // LAB4_CUSTOMER_H_
