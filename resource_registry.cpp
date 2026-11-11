#include "resource_registry.h"

#include <iostream>
#include <stdexcept>
#include <string>

ResourceRegistry::ResourceRegistry()
    : static_items_{}, dynamic_items_{}, static_count_(0), dynamic_count_(0) {}

ResourceRegistry::~ResourceRegistry() {
  for (int i = 0; i < dynamic_count_; ++i) {
    delete dynamic_items_[i];
  }
}

// [ЛР5, п.5] Винятки: нульовий вказівник, переповнення масиву
void ResourceRegistry::AddStatic(Resource *resource) {
  if (resource == nullptr) {
    throw std::invalid_argument("AddStatic: передано нульовий вказівник");
  }
  if (static_count_ >= kStaticCapacity) {
    throw std::overflow_error("AddStatic: масив статичних об'єктів заповнено");
  }
  static_items_[static_count_++] = resource;
}

// [ЛР5, п.5] Реєстр приймає володіння об'єктом; якщо додати його неможливо,
// об'єкт видаляється, щоб уникнути витоку пам'яті, і генерується виняток
void ResourceRegistry::AddDynamic(Resource *resource) {
  if (resource == nullptr) {
    throw std::invalid_argument("AddDynamic: передано нульовий вказівник");
  }
  if (dynamic_count_ >= kDynamicCapacity) {
    delete resource;
    throw std::overflow_error(
        "AddDynamic: масив динамічних об'єктів заповнено");
  }
  dynamic_items_[dynamic_count_++] = resource;
}

// [ЛР5, п.5] Виняток: звернення за межі масиву динамічних об'єктів
Resource *ResourceRegistry::GetDynamic(int index) const {
  if (index < 0 || index >= dynamic_count_) {
    throw std::out_of_range("GetDynamic: індекс " + std::to_string(index) +
                            " поза межами [0, " +
                            std::to_string(dynamic_count_) + ")");
  }
  return dynamic_items_[index];
}

void ResourceRegistry::RemoveDynamic(int index) {
  Resource *resource = GetDynamic(index);
  for (int i = index; i < dynamic_count_ - 1; ++i) {
    dynamic_items_[i] = dynamic_items_[i + 1];
  }
  dynamic_items_[--dynamic_count_] = nullptr;
  delete resource;
}

// [ЛР5, п.6] Service_Static: вилучає з масиву статичні об'єкти заданої
// категорії (самі об'єкти не видаляються — вони не в динамічній пам'яті)
int ResourceRegistry::Service_Static(const std::string &category) {
  if (category.empty()) {
    throw std::invalid_argument("Service_Static: категорію не задано");
  }
  if (static_count_ == 0) {
    throw std::underflow_error("Service_Static: масив статичних об'єктів "
                               "порожній");
  }
  int kept = 0;
  int removed = 0;
  for (int i = 0; i < static_count_; ++i) {
    if (static_items_[i] == nullptr) {
      throw std::logic_error("Service_Static: у масиві нульовий вказівник");
    }
    if (static_items_[i]->GetCategory() == category) {
      std::cout << "  [Service_Static] Вилучено з масиву: "
                << static_items_[i]->get_name() << "\n";
      removed++;
    } else {
      static_items_[kept++] = static_items_[i];
    }
  }
  if (removed == 0) {
    throw std::runtime_error("Service_Static: об'єктів категорії '" +
                             category + "' не знайдено");
  }
  for (int i = kept; i < static_count_; ++i) {
    static_items_[i] = nullptr;
  }
  static_count_ = kept;
  return removed;
}

// [ЛР5, п.6] Service_Dinamic: видаляє (delete) динамічні об'єкти, вартість
// яких перевищує ліміт бюджету max_cost
int ResourceRegistry::Service_Dinamic(double max_cost) {
  if (max_cost < 0) {
    throw std::invalid_argument("Service_Dinamic: ліміт вартості не може "
                                "бути від'ємним");
  }
  if (dynamic_count_ == 0) {
    throw std::underflow_error("Service_Dinamic: масив динамічних об'єктів "
                               "порожній");
  }
  int kept = 0;
  int removed = 0;
  for (int i = 0; i < dynamic_count_; ++i) {
    if (dynamic_items_[i] == nullptr) {
      throw std::logic_error("Service_Dinamic: у масиві нульовий вказівник");
    }
    if (dynamic_items_[i]->CalculateCost() > max_cost) {
      std::cout << "  [Service_Dinamic] Видалено (вартість $"
                << dynamic_items_[i]->CalculateCost() << " > $" << max_cost
                << "): " << dynamic_items_[i]->get_name() << "\n";
      delete dynamic_items_[i];
      removed++;
    } else {
      dynamic_items_[kept++] = dynamic_items_[i];
    }
  }
  for (int i = kept; i < dynamic_count_; ++i) {
    dynamic_items_[i] = nullptr;
  }
  dynamic_count_ = kept;
  if (removed == 0) {
    throw std::runtime_error("Service_Dinamic: немає об'єктів дорожчих за $" +
                             std::to_string(max_cost));
  }
  return removed;
}

void ResourceRegistry::PrintAll() const {
  std::cout << "  --- Статичні об'єкти (" << static_count_ << "/"
            << kStaticCapacity << ") ---\n";
  for (int i = 0; i < static_count_; ++i) {
    std::cout << "  [" << i << "] " << static_items_[i]->GetCategory() << " '"
              << static_items_[i]->get_name() << "' — $"
              << static_items_[i]->CalculateCost() << "\n";
  }
  std::cout << "  --- Динамічні об'єкти (" << dynamic_count_ << "/"
            << kDynamicCapacity << ") ---\n";
  for (int i = 0; i < dynamic_count_; ++i) {
    std::cout << "  [" << i << "] " << dynamic_items_[i]->GetCategory()
              << " '" << dynamic_items_[i]->get_name() << "' — $"
              << dynamic_items_[i]->CalculateCost() << "\n";
  }
}
