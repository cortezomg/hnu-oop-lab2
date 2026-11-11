#ifndef LAB5_WORKSTATION_H_
#define LAB5_WORKSTATION_H_

#include <iostream>
#include <string>

#include "equipment.h"
#include "software_license.h"

// [ЛР5, п.1, п.2] Workstation — робоча станція: обладнання з попередньо
// встановленим ліцензійним ПЗ. Множинне наслідування від Equipment та
// SoftwareLicense ("ромб"); завдяки віртуальному наслідуванню містить лише
// один підоб'єкт Resource
class Workstation : public Equipment, public SoftwareLicense {
public:
  Workstation();
  // [ЛР5, п.2] Конструктор віртуального базового класу Resource викликає
  // безпосередньо найпохідніший клас Workstation
  Workstation(int id, const std::string &name, const std::string &vendor,
              int quantity, double unit_price,
              const std::string &serial_number, const std::string &os_name,
              int license_months, double monthly_support_fee,
              int setup_hours);
  Workstation(const Workstation &other);
  // [ЛР5, п.3] Віртуальний деструктор похідного класу
  ~Workstation() override;

  double CalculateCost() const override;
  std::string GetCategory() const override;
  void PrintInfo() const override;

  // [ЛР5, п.4] Власна віртуальна функція: вартість налаштування станцій
  virtual double CalculateSetupCost() const;

protected:
  void WriteDetails(std::ostream &os) const override;
  void ReadDetails(std::istream &is) override;

private:
  static constexpr double kSetupHourRate = 25.0;

  std::string os_name_;
  int setup_hours_;
};

#endif // LAB5_WORKSTATION_H_
