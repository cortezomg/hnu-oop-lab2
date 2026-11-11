#include "equipment.h"

#include <algorithm>
#include <iostream>
#include <string>

Equipment::Equipment()
    : Resource(), serial_number_("N/A"), warranty_months_(0),
      lifetime_years_(1), maintenance_cost_(0.0) {
  std::cout << "  [Constructor] Створено об'єкт Equipment #" << get_id()
            << "\n";
}

Equipment::Equipment(int id, const std::string &name,
                     const std::string &vendor, int quantity,
                     double unit_price, int purchase_year,
                     const std::string &serial_number, int warranty_months,
                     int lifetime_years, double maintenance_cost)
    : Resource(id, name, vendor, quantity, unit_price, purchase_year),
      serial_number_(serial_number), warranty_months_(warranty_months),
      lifetime_years_(lifetime_years), maintenance_cost_(maintenance_cost) {
  std::cout << "  [Constructor] Створено об'єкт Equipment #" << get_id()
            << " (" << get_name() << ")\n";
}

Equipment::Equipment(const Equipment &other)
    : Resource(other), serial_number_(other.serial_number_),
      warranty_months_(other.warranty_months_),
      lifetime_years_(other.lifetime_years_),
      maintenance_cost_(other.maintenance_cost_) {
  std::cout << "  [Copy Constructor] Створено копію обладнання: "
            << get_name() << "\n";
}

Equipment::~Equipment() {
  std::cout << "  [Destructor] Знищено об'єкт Equipment #" << get_id()
            << " (" << get_name() << ")\n";
}

double Equipment::CalculateCost() const {
  return GetBaseCost() + maintenance_cost_;
}

std::string Equipment::GetCategory() const { return "Equipment"; }

void Equipment::PrintInfo() const {
  Resource::PrintInfo();
  PrintEquipmentDetails();
}

double Equipment::CalculateDepreciation(int years) const {
  int used_years = std::min(std::max(years, 0), lifetime_years_);
  return GetBaseCost() * used_years / lifetime_years_;
}

void Equipment::Describe() const {
  std::cout << "  [Equipment::Describe] Обладнання '" << get_name()
            << "', S/N " << serial_number_ << "\n";
}

void Equipment::WriteDetails(std::ostream &os) const {
  os << serial_number_ << "\n"
     << warranty_months_ << "\n"
     << lifetime_years_ << "\n"
     << maintenance_cost_ << "\n";
}

void Equipment::ReadDetails(std::istream &is) {
  std::string serial_number = ReadText(is);
  int warranty_months = ReadInt(is);
  int lifetime_years = ReadInt(is);
  double maintenance_cost = ReadDouble(is);
  serial_number_ = serial_number;
  warranty_months_ = warranty_months;
  lifetime_years_ = lifetime_years;
  maintenance_cost_ = maintenance_cost;
}

void Equipment::PrintEquipmentDetails() const {
  std::cout << "    [Обладнання] S/N: " << serial_number_
            << " | Гарантія: " << warranty_months_
            << " міс. | Термін служби: " << lifetime_years_
            << " р. | Обслуговування: $" << maintenance_cost_
            << " | Амортизація за 1 рік: $" << CalculateDepreciation(1)
            << "\n";
}
