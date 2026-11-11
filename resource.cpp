#include "resource.h"

#include <iostream>
#include <string>

#include "resource_exceptions.h"

int Resource::total_count_ = 0;

Resource::Resource()
    : id_(0), name_("Undefined"), vendor_("None"), quantity_(0),
      unit_price_(0.0), purchase_year_(2026), holder_(nullptr) {
  total_count_++;
  std::cout << "  [Constructor] Створено об'єкт Resource #" << id_ << "\n";
}

Resource::Resource(int id, const std::string &name, const std::string &vendor,
                   int quantity, double unit_price, int purchase_year)
    : id_(id), name_(name), vendor_(vendor), quantity_(quantity),
      unit_price_(unit_price), purchase_year_(purchase_year),
      holder_(nullptr) {
  total_count_++;
  std::cout << "  [Constructor] Створено об'єкт Resource #" << id_ << " ("
            << name_ << ")\n";
}

Resource::Resource(const Resource &other)
    : id_(other.id_), name_(other.name_), vendor_(other.vendor_),
      quantity_(other.quantity_), unit_price_(other.unit_price_),
      purchase_year_(other.purchase_year_), holder_(other.holder_) {
  total_count_++;
  std::cout << "  [Copy Constructor] Створено копію ресурсу: " << name_
            << "\n";
}

Resource::~Resource() {
  total_count_--;
  std::cout << "  [Destructor] Знищено об'єкт Resource #" << id_ << " ("
            << name_ << ")\n";
}

void Resource::PrintInfo() const {
  std::cout << "  [" << GetCategory() << " #" << id_ << "] " << name_
            << " | Постачальник: " << vendor_ << " | К-сть: " << quantity_
            << " | Ціна за од.: $" << unit_price_
            << " | Рік: " << purchase_year_ << " | Відповідальний: "
            << (holder_ != nullptr ? holder_->name : "—")
            << " | Вартість: $" << CalculateCost() << "\n";
}

void Resource::Describe() const {
  std::cout << "  [Resource::Describe] Ресурс '" << name_
            << "' (невіртуальний метод базового класу)\n";
}

// [ЛР5, п.7] Запис полів даних: спільні поля пише базовий клас, власні —
// віртуальний метод WriteDetails похідного класу
void Resource::Write(std::ostream &os) const {
  os << GetCategory() << "\n"
     << id_ << "\n"
     << name_ << "\n"
     << vendor_ << "\n"
     << quantity_ << "\n"
     << unit_price_ << "\n"
     << purchase_year_ << "\n";
  WriteDetails(os);
}

// [ЛР5, п.7] Читання полів даних з генерацією винятків при помилках формату
void Resource::Read(std::istream &is) {
  std::string category;
  if (!std::getline(is, category)) {
    throw FileFormatError("файл порожній — немає даних для читання");
  }
  if (category != GetCategory()) {
    throw FileFormatError("тип об'єкта у файлі (" + category +
                          ") не відповідає типу " + GetCategory());
  }
  int id = ReadInt(is);
  std::string name = ReadText(is);
  std::string vendor = ReadText(is);
  int quantity = ReadInt(is);
  double unit_price = ReadDouble(is);
  int purchase_year = ReadInt(is);
  ReadDetails(is);

  id_ = id;
  name_ = name;
  vendor_ = vendor;
  quantity_ = quantity;
  unit_price_ = unit_price;
  purchase_year_ = purchase_year;
}

void Resource::AssignTo(const Worker *holder) {
  holder_ = holder;
  std::cout << "  [Resource] '" << name_ << "' закріплено за: "
            << (holder != nullptr ? holder->name : "—") << "\n";
}

int Resource::GetTotalCount() { return total_count_; }

std::string Resource::ReadText(std::istream &is) {
  std::string line;
  if (!std::getline(is, line)) {
    throw FileFormatError("неочікуваний кінець файлу");
  }
  return line;
}

int Resource::ReadInt(std::istream &is) {
  std::string line = ReadText(is);
  try {
    std::size_t pos = 0;
    int value = std::stoi(line, &pos);
    if (pos != line.size()) {
      throw FileFormatError("зайві символи");
    }
    return value;
  } catch (const std::exception &) {
    throw FileFormatError("пошкоджені дані: очікувалось ціле число, "
                          "отримано '" + line + "'");
  }
}

double Resource::ReadDouble(std::istream &is) {
  std::string line = ReadText(is);
  try {
    std::size_t pos = 0;
    double value = std::stod(line, &pos);
    if (pos != line.size()) {
      throw FileFormatError("зайві символи");
    }
    return value;
  } catch (const std::exception &) {
    throw FileFormatError("пошкоджені дані: очікувалось число, отримано '" +
                          line + "'");
  }
}
