#ifndef LAB5_SOFTWARE_LICENSE_H_
#define LAB5_SOFTWARE_LICENSE_H_

#include <iostream>
#include <string>

#include "resource.h"

// [ЛР5, п.1, п.2] SoftwareLicense — ліцензія на програмне забезпечення.
// Віртуальне наслідування від Resource
class SoftwareLicense : virtual public Resource {
public:
  SoftwareLicense();
  SoftwareLicense(int id, const std::string &name, const std::string &vendor,
                  int quantity, double unit_price, int purchase_year,
                  const std::string &license_key, int duration_months,
                  double monthly_support_fee);
  SoftwareLicense(const SoftwareLicense &other);
  // [ЛР5, п.3] Віртуальний деструктор похідного класу
  ~SoftwareLicense() override;

  double CalculateCost() const override;
  std::string GetCategory() const override;
  void PrintInfo() const override;

  // [ЛР5, п.4] Власна віртуальна функція: перевірка терміну дії ліцензії
  virtual bool IsExpired(int months_passed) const;

protected:
  void WriteDetails(std::ostream &os) const override;
  void ReadDetails(std::istream &is) override;
  void PrintLicenseDetails() const;
  double CalculateSupportCost() const;

private:
  std::string license_key_;
  int duration_months_;
  double monthly_support_fee_;
};

#endif // LAB5_SOFTWARE_LICENSE_H_
