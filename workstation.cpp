#include "workstation.h"

#include <iostream>
#include <string>

Workstation::Workstation()
    : Resource(), Equipment(), SoftwareLicense(), os_name_("None"),
      setup_hours_(0) {
  std::cout << "  [Constructor] Створено об'єкт Workstation #" << get_id()
            << "\n";
}

// [ЛР5, п.2] Resource ініціалізується один раз — тут; виклики Resource(...) у
// конструкторах Equipment та SoftwareLicense при цьому ігноруються
Workstation::Workstation(int id, const std::string &name,
                         const std::string &vendor, int quantity,
                         double unit_price, const std::string &serial_number,
                         const std::string &os_name, int license_months,
                         double monthly_support_fee, int setup_hours)
    : Resource(id, name, vendor, quantity, unit_price, 2026),
      Equipment(id, name, vendor, quantity, unit_price, 2026, serial_number,
                24, 4, 50.0 * quantity),
      SoftwareLicense(id, name, vendor, quantity, unit_price, 2026,
                      "OEM-" + serial_number, license_months,
                      monthly_support_fee),
      os_name_(os_name), setup_hours_(setup_hours) {
  std::cout << "  [Constructor] Створено об'єкт Workstation #" << get_id()
            << " (" << get_name() << ")\n";
}

Workstation::Workstation(const Workstation &other)
    : Resource(other), Equipment(other), SoftwareLicense(other),
      os_name_(other.os_name_), setup_hours_(other.setup_hours_) {
  std::cout << "  [Copy Constructor] Створено копію робочої станції: "
            << get_name() << "\n";
}

Workstation::~Workstation() {
  std::cout << "  [Destructor] Знищено об'єкт Workstation #" << get_id()
            << " (" << get_name() << ")\n";
}

double Workstation::CalculateCost() const {
  return Equipment::CalculateCost() + CalculateSupportCost() +
         CalculateSetupCost();
}

std::string Workstation::GetCategory() const { return "Workstation"; }

void Workstation::PrintInfo() const {
  Resource::PrintInfo();
  PrintEquipmentDetails();
  PrintLicenseDetails();
  std::cout << "    [Робоча станція] ОС: " << os_name_
            << " | Налаштування: " << setup_hours_
            << " год/шт. | Вартість налаштування: $" << CalculateSetupCost()
            << "\n";
}

double Workstation::CalculateSetupCost() const {
  return get_quantity() * setup_hours_ * kSetupHourRate;
}

void Workstation::WriteDetails(std::ostream &os) const {
  Equipment::WriteDetails(os);
  SoftwareLicense::WriteDetails(os);
  os << os_name_ << "\n" << setup_hours_ << "\n";
}

void Workstation::ReadDetails(std::istream &is) {
  Equipment::ReadDetails(is);
  SoftwareLicense::ReadDetails(is);
  std::string os_name = ReadText(is);
  int setup_hours = ReadInt(is);
  os_name_ = os_name;
  setup_hours_ = setup_hours;
}
