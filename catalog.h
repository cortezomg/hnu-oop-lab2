#ifndef LAB6_CATALOG_H_
#define LAB6_CATALOG_H_

#include <iostream>
#include <stdexcept>
#include <string>

// [ЛР6, п.5] Шаблон класу Catalog<T> — каталог елементів проєкту довільного
// типу (оцінки задач, етапи, витрати тощо) з динамічним масивом, що
// розширюється. Шаблон визначено повністю в заголовному файлі, бо компілятор
// має бачити його код, щоб створити клас для конкретного типу T
template <typename T>
class Catalog {
public:
  explicit Catalog(const std::string &title, int capacity = 2)
      : title_(title), capacity_(CheckCapacity(capacity)), size_(0),
        items_(new T[capacity_]), last_removed_() {}

  Catalog(const Catalog &other)
      : title_(other.title_), capacity_(other.capacity_), size_(other.size_),
        items_(new T[other.capacity_]), last_removed_(other.last_removed_) {
    for (int i = 0; i < size_; ++i) {
      items_[i] = other.items_[i];
    }
  }

  Catalog &operator=(const Catalog &other) {
    if (this != &other) {
      T *copy = new T[other.capacity_];
      for (int i = 0; i < other.size_; ++i) {
        copy[i] = other.items_[i];
      }
      delete[] items_;
      items_ = copy;
      title_ = other.title_;
      capacity_ = other.capacity_;
      size_ = other.size_;
      last_removed_ = other.last_removed_;
    }
    return *this;
  }

  ~Catalog() { delete[] items_; }

  // [ЛР6, п.5] Шаблонні методи
  void Add(const T &item) {
    if (size_ == capacity_) {
      Grow();
    }
    items_[size_++] = item;
  }

  T RemoveAt(int index) {
    CheckIndex(index);
    last_removed_ = items_[index];
    for (int i = index; i < size_ - 1; ++i) {
      items_[i] = items_[i + 1];
    }
    --size_;
    return last_removed_;
  }

  T &operator[](int index) {
    CheckIndex(index);
    return items_[index];
  }

  const T &operator[](int index) const {
    CheckIndex(index);
    return items_[index];
  }

  bool Contains(const T &item) const {
    for (int i = 0; i < size_; ++i) {
      if (items_[i] == item) {
        return true;
      }
    }
    return false;
  }

  const T &FindMax() const {
    CheckNotEmpty("FindMax");
    int max_index = 0;
    for (int i = 1; i < size_; ++i) {
      if (items_[max_index] < items_[i]) {
        max_index = i;
      }
    }
    return items_[max_index];
  }

  T Total() const {
    CheckNotEmpty("Total");
    T total = items_[0];
    for (int i = 1; i < size_; ++i) {
      total = total + items_[i];
    }
    return total;
  }

  void Print() const {
    std::cout << "  Каталог \"" << title_ << "\" (" << size_ << " з "
              << capacity_ << "):\n";
    for (int i = 0; i < size_; ++i) {
      std::cout << "    [" << i << "] " << items_[i] << "\n";
    }
  }

  const std::string &title() const { return title_; }
  int size() const { return size_; }
  int capacity() const { return capacity_; }
  bool empty() const { return size_ == 0; }
  const T &last_removed() const { return last_removed_; }

private:
  static int CheckCapacity(int capacity) {
    if (capacity <= 0) {
      throw std::invalid_argument("Catalog: місткість має бути додатною");
    }
    return capacity;
  }

  void Grow() {
    T *bigger = new T[capacity_ * 2];
    for (int i = 0; i < size_; ++i) {
      bigger[i] = items_[i];
    }
    delete[] items_;
    items_ = bigger;
    capacity_ *= 2;
  }

  void CheckIndex(int index) const {
    if (index < 0 || index >= size_) {
      throw std::out_of_range("Catalog \"" + title_ + "\": індекс " +
                              std::to_string(index) + " поза межами [0, " +
                              std::to_string(size_) + ")");
    }
  }

  void CheckNotEmpty(const char *method) const {
    if (size_ == 0) {
      throw std::underflow_error(std::string("Catalog::") + method +
                                 ": каталог порожній");
    }
  }

  // [ЛР6, п.5] Шаблонні дані (5 полів)
  std::string title_;
  int capacity_;
  int size_;
  T *items_;
  T last_removed_;
};

#endif // LAB6_CATALOG_H_
