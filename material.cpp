#include "material.h"

#include <iostream>
#include <string>

Material::Material()
    : Resource(), unit_of_measure_("pcs"), consumed_(0), min_stock_(0),
      is_hazardous_(false) {
  std::cout << "  [Constructor] Створено об'єкт Material #" << get_id()
            << "\n";
}

Material::Material(int id, const std::string &name, const std::string &vendor,
                   int quantity, double unit_price, int purchase_year,
                   const std::string &unit_of_measure, int min_stock,
                   bool is_hazardous)
    : Resource(id, name, vendor, quantity, unit_price, purchase_year),
      unit_of_measure_(unit_of_measure), consumed_(0), min_stock_(min_stock),
      is_hazardous_(is_hazardous) {
  std::cout << "  [Constructor] Створено об'єкт Material #" << get_id()
            << " (" << get_name() << ")\n";
}

Material::Material(const Material &other)
    : Resource(other), unit_of_measure_(other.unit_of_measure_),
      consumed_(other.consumed_), min_stock_(other.min_stock_),
      is_hazardous_(other.is_hazardous_) {
  std::cout << "  [Copy Constructor] Створено копію матеріалу: " << get_name()
            << "\n";
}

Material::~Material() {
  std::cout << "  [Destructor] Знищено об'єкт Material #" << get_id() << " ("
            << get_name() << ")\n";
}

double Material::CalculateCost() const {
  return GetBaseCost() * (is_hazardous_ ? 1.1 : 1.0);
}

std::string Material::GetCategory() const { return "Material"; }

void Material::PrintInfo() const {
  Resource::PrintInfo();
  std::cout << "    [Матеріал] Одиниця: " << unit_of_measure_
            << " | Використано: " << consumed_
            << " | Доступно: " << GetAvailable()
            << " | Мін. запас: " << min_stock_
            << " | Небезпечний: " << (is_hazardous_ ? "так" : "ні")
            << " | Потрібне поповнення: "
            << (GetAvailable() < min_stock_ ? "так" : "ні") << "\n";
}

bool Material::Consume(int units) {
  if (units <= 0 || units > GetAvailable()) {
    std::cout << "  [Material] Неможливо списати " << units << " "
              << unit_of_measure_ << " '" << get_name() << "' (доступно "
              << GetAvailable() << ")\n";
    return false;
  }
  consumed_ += units;
  std::cout << "  [Material] Списано " << units << " " << unit_of_measure_
            << " '" << get_name() << "'\n";
  return true;
}

void Material::WriteDetails(std::ostream &os) const {
  os << unit_of_measure_ << "\n"
     << consumed_ << "\n"
     << min_stock_ << "\n"
     << (is_hazardous_ ? 1 : 0) << "\n";
}

void Material::ReadDetails(std::istream &is) {
  std::string unit_of_measure = ReadText(is);
  int consumed = ReadInt(is);
  int min_stock = ReadInt(is);
  int is_hazardous = ReadInt(is);
  unit_of_measure_ = unit_of_measure;
  consumed_ = consumed;
  min_stock_ = min_stock;
  is_hazardous_ = is_hazardous != 0;
}
