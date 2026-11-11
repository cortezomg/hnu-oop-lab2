#ifndef LAB5_MATERIAL_H_
#define LAB5_MATERIAL_H_

#include <iostream>
#include <string>

#include "resource.h"

// [ЛР5, п.1] Material — витратні матеріали проєкту (відкрите наслідування від
// Resource; у ромбі не бере участі, тому наслідування звичайне)
class Material : public Resource {
public:
  Material();
  Material(int id, const std::string &name, const std::string &vendor,
           int quantity, double unit_price, int purchase_year,
           const std::string &unit_of_measure, int min_stock,
           bool is_hazardous);
  Material(const Material &other);
  // [ЛР5, п.3] Віртуальний деструктор похідного класу
  ~Material() override;

  double CalculateCost() const override;
  std::string GetCategory() const override;
  void PrintInfo() const override;

  // [ЛР5, п.4] Власна віртуальна функція: списання матеріалу
  virtual bool Consume(int units);

  int GetAvailable() const { return get_quantity() - consumed_; }

protected:
  void WriteDetails(std::ostream &os) const override;
  void ReadDetails(std::istream &is) override;

private:
  std::string unit_of_measure_;
  int consumed_;
  int min_stock_;
  bool is_hazardous_;
};

#endif // LAB5_MATERIAL_H_
