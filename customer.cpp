#include "customer.h"

#include <iostream>
#include <string>

Customer::Customer()
    : customer_id_(0), company_name_("Undefined"), contact_person_("None"),
      email_("None"), phone_("None"), country_("None"), orders_count_(0),
      total_paid_(0.0) {
  std::cout << "  [Constructor] Створено об'єкт Customer #" << customer_id_
            << "\n";
}

Customer::Customer(int customer_id, const std::string &company_name,
                   const std::string &contact_person, const std::string &email,
                   const std::string &phone, const std::string &country)
    : customer_id_(customer_id), company_name_(company_name),
      contact_person_(contact_person), email_(email), phone_(phone),
      country_(country), orders_count_(0), total_paid_(0.0) {
  std::cout << "  [Constructor] Створено об'єкт Customer #" << customer_id_
            << " (" << company_name_ << ")\n";
}

Customer::Customer(const Customer &other)
    : customer_id_(other.customer_id_), company_name_(other.company_name_),
      contact_person_(other.contact_person_), email_(other.email_),
      phone_(other.phone_), country_(other.country_),
      orders_count_(other.orders_count_), total_paid_(other.total_paid_) {
  std::cout << "  [Copy Constructor] Створено копію замовника: "
            << company_name_ << "\n";
}

Customer::~Customer() {
  std::cout << "  [Destructor] Знищено об'єкт Customer #" << customer_id_
            << " (" << company_name_ << ")\n";
}

void Customer::OrderProject(Project &project, Manager &manager) {
  orders_count_++;
  std::cout << "  [Customer] " << company_name_ << " замовляє проєкт '"
            << project.title << "' у менеджера " << manager.name << "\n";
  manager.AcceptProject(project);
}

void Customer::PayInvoice(double amount) {
  total_paid_ += amount;
  std::cout << "  [Customer] " << company_name_ << ": оплачено $" << amount
            << " (усього: $" << total_paid_ << ")\n";
}

void Customer::ReviewProject(const Project &project) const {
  std::cout << "  [Customer] " << contact_person_ << " переглядає проєкт '"
            << project.title << "': статус " << project.status
            << ", витрачено $" << project.get_current_expenses() << " з $"
            << project.get_total_budget() << "\n";
}

void Customer::PrintInfo() const {
  std::cout << "  [Замовник #" << customer_id_ << "] " << company_name_
            << " | Контакт: " << contact_person_ << " | Email: " << email_
            << " | Тел.: " << phone_ << " | Країна: " << country_
            << " | Замовлень: " << orders_count_ << " | Сплачено: $"
            << total_paid_ << "\n";
}
