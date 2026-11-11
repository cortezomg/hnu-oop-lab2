#ifndef LAB5_RESOURCE_H_
#define LAB5_RESOURCE_H_

#include <iostream>
#include <string>

#include "worker.h"

// [ЛР5, п.1] Resource — абстрактний базовий клас для ресурсів проєкту
// (обладнання, програмне забезпечення, матеріали). Об'єкт абстрактного класу
// створити не можна: він містить чисто віртуальні функції
class Resource {
public:
  Resource();
  Resource(int id, const std::string &name, const std::string &vendor,
           int quantity, double unit_price, int purchase_year);
  Resource(const Resource &other);
  // [ЛР5, п.3] Віртуальний деструктор базового класу
  virtual ~Resource();

  // [ЛР5, п.1, п.4] Чисто віртуальні функції
  virtual double CalculateCost() const = 0;
  virtual std::string GetCategory() const = 0;

  // [ЛР5, п.4] Віртуальна функція, яку уточнюють похідні класи
  virtual void PrintInfo() const;

  // [ЛР5, п.10] Невіртуальний метод — завжди раннє (статичне) зв'язування
  void Describe() const;

  // [ЛР5, п.7] Методи Write та Read для запису та читання полів даних
  void Write(std::ostream &os) const;
  void Read(std::istream &is);

  void AssignTo(const Worker *holder);

  static int GetTotalCount();

  int get_id() const { return id_; }
  const std::string &get_name() const { return name_; }
  int get_quantity() const { return quantity_; }
  double get_unit_price() const { return unit_price_; }

protected:
  // [ЛР5, п.7] Кожен похідний клас записує та читає власні поля
  virtual void WriteDetails(std::ostream &os) const = 0;
  virtual void ReadDetails(std::istream &is) = 0;

  double GetBaseCost() const { return quantity_ * unit_price_; }

  static std::string ReadText(std::istream &is);
  static int ReadInt(std::istream &is);
  static double ReadDouble(std::istream &is);

private:
  int id_;
  std::string name_;
  std::string vendor_;
  int quantity_;
  double unit_price_;
  int purchase_year_;
  const Worker *holder_;

  static int total_count_;
};

#endif // LAB5_RESOURCE_H_
