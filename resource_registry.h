#ifndef LAB5_RESOURCE_REGISTRY_H_
#define LAB5_RESOURCE_REGISTRY_H_

#include <string>

#include "resource.h"

// [ЛР5, п.5, п.6] Реєстр ресурсів: масив статичних об'єктів (реєстр ними не
// володіє) та масив динамічних об'єктів (реєстр видаляє їх через delete)
class ResourceRegistry {
public:
  static constexpr int kStaticCapacity = 5;
  static constexpr int kDynamicCapacity = 8;

  ResourceRegistry();
  ResourceRegistry(const ResourceRegistry &) = delete;
  ResourceRegistry &operator=(const ResourceRegistry &) = delete;
  ~ResourceRegistry();

  void AddStatic(Resource *resource);
  void AddDynamic(Resource *resource);
  Resource *GetDynamic(int index) const;
  void RemoveDynamic(int index);

  // [ЛР5, п.6] Видалення з масивів за критерієм: статичні — за категорією,
  // динамічні — за вартістю, що перевищує ліміт бюджету
  int Service_Static(const std::string &category);
  int Service_Dinamic(double max_cost);

  void PrintAll() const;
  int static_count() const { return static_count_; }
  int dynamic_count() const { return dynamic_count_; }

private:
  Resource *static_items_[kStaticCapacity];
  Resource *dynamic_items_[kDynamicCapacity];
  int static_count_;
  int dynamic_count_;
};

#endif // LAB5_RESOURCE_REGISTRY_H_
