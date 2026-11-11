#include "software_license.h"

#include <iostream>
#include <string>

SoftwareLicense::SoftwareLicense()
    : Resource(), license_key_("N/A"), duration_months_(0),
      monthly_support_fee_(0.0) {
  std::cout << "  [Constructor] Створено об'єкт SoftwareLicense #" << get_id()
            << "\n";
}

SoftwareLicense::SoftwareLicense(int id, const std::string &name,
                                 const std::string &vendor, int quantity,
                                 double unit_price, int purchase_year,
                                 const std::string &license_key,
                                 int duration_months,
                                 double monthly_support_fee)
    : Resource(id, name, vendor, quantity, unit_price, purchase_year),
      license_key_(license_key), duration_months_(duration_months),
      monthly_support_fee_(monthly_support_fee) {
  std::cout << "  [Constructor] Створено об'єкт SoftwareLicense #" << get_id()
            << " (" << get_name() << ")\n";
}

SoftwareLicense::SoftwareLicense(const SoftwareLicense &other)
    : Resource(other), license_key_(other.license_key_),
      duration_months_(other.duration_months_),
      monthly_support_fee_(other.monthly_support_fee_) {
  std::cout << "  [Copy Constructor] Створено копію ліцензії: " << get_name()
            << "\n";
}

SoftwareLicense::~SoftwareLicense() {
  std::cout << "  [Destructor] Знищено об'єкт SoftwareLicense #" << get_id()
            << " (" << get_name() << ")\n";
}

double SoftwareLicense::CalculateCost() const {
  return GetBaseCost() + CalculateSupportCost();
}

std::string SoftwareLicense::GetCategory() const { return "SoftwareLicense"; }

void SoftwareLicense::PrintInfo() const {
  Resource::PrintInfo();
  PrintLicenseDetails();
}

bool SoftwareLicense::IsExpired(int months_passed) const {
  return months_passed >= duration_months_;
}

void SoftwareLicense::WriteDetails(std::ostream &os) const {
  os << license_key_ << "\n"
     << duration_months_ << "\n"
     << monthly_support_fee_ << "\n";
}

void SoftwareLicense::ReadDetails(std::istream &is) {
  std::string license_key = ReadText(is);
  int duration_months = ReadInt(is);
  double monthly_support_fee = ReadDouble(is);
  license_key_ = license_key;
  duration_months_ = duration_months;
  monthly_support_fee_ = monthly_support_fee;
}

void SoftwareLicense::PrintLicenseDetails() const {
  std::cout << "    [Ліцензія] Ключ: " << license_key_
            << " | Термін: " << duration_months_
            << " міс. | Підтримка: $" << monthly_support_fee_
            << "/міс. | Вартість підтримки: $" << CalculateSupportCost()
            << " | Прострочена через 12 міс.: "
            << (IsExpired(12) ? "так" : "ні") << "\n";
}

double SoftwareLicense::CalculateSupportCost() const {
  return get_quantity() * monthly_support_fee_ * duration_months_;
}
