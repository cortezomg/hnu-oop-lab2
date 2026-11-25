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

  // [ЛР6, п.3] Оператор [] як функція-член: доступ до динамічного об'єкта за
  // індексом з перевіркою меж (виняток out_of_range, як у GetDynamic)
  Resource &operator[](int index);
  const Resource &operator[](int index) const;

  // [ЛР6, п.4] Шаблонна функція-член: рахує статичні та динамічні ресурси,
  // що задовольняють умову. Predicate — будь-який тип, який можна викликати
  // як функцію (лямбда, вказівник на функцію, функтор); компілятор створює
  // окрему версію функції для кожного такого типу
  template <typename Predicate>
  int CountIf(Predicate predicate) const {
    int count = 0;
    for (int i = 0; i < static_count_; ++i) {
      if (predicate(*static_items_[i])) {
        ++count;
      }
    }
    for (int i = 0; i < dynamic_count_; ++i) {
      if (predicate(*dynamic_items_[i])) {
        ++count;
      }
    }
    return count;
  }

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
