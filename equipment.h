#ifndef LAB5_EQUIPMENT_H_
#define LAB5_EQUIPMENT_H_

#include <iostream>
#include <string>

#include "resource.h"

// [ЛР5, п.1, п.2] Equipment — обладнання проєкту. Віртуальне наслідування від
// Resource, щоб у Workstation був лише один підоб'єкт Resource
class Equipment : virtual public Resource {
public:
  Equipment();
  Equipment(int id, const std::string &name, const std::string &vendor,
            int quantity, double unit_price, int purchase_year,
            const std::string &serial_number, int warranty_months,
            int lifetime_years, double maintenance_cost);
  Equipment(const Equipment &other);
  // [ЛР5, п.3] Віртуальний деструктор похідного класу
  ~Equipment() override;

  double CalculateCost() const override;
  std::string GetCategory() const override;
  void PrintInfo() const override;

  // [ЛР5, п.4] Власна віртуальна функція: амортизація обладнання
  virtual double CalculateDepreciation(int years) const;

  // [ЛР5, п.10] Приховує невіртуальний Resource::Describe()
  void Describe() const;

protected:
  void WriteDetails(std::ostream &os) const override;
  void ReadDetails(std::istream &is) override;
  void PrintEquipmentDetails() const;

private:
  std::string serial_number_;
  int warranty_months_;
  int lifetime_years_;
  double maintenance_cost_;
};

#endif // LAB5_EQUIPMENT_H_
