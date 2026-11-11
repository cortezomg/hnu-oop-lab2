#include "resource_pool.h"

#include <iostream>
#include <string>

ResourcePool::ResourcePool()
    : pool_id_(0), pool_name_("Undefined"), location_("None"),
      equipment_units_(0), software_licenses_(0), material_units_(0),
      allocated_equipment_(0), allocated_licenses_(0),
      allocated_materials_(0) {
  std::cout << "  [Constructor] Створено об'єкт ResourcePool #" << pool_id_
            << "\n";
}

ResourcePool::ResourcePool(int pool_id, const std::string &pool_name,
                           const std::string &location, int equipment_units,
                           int software_licenses, int material_units)
    : pool_id_(pool_id), pool_name_(pool_name), location_(location),
      equipment_units_(equipment_units), software_licenses_(software_licenses),
      material_units_(material_units), allocated_equipment_(0),
      allocated_licenses_(0), allocated_materials_(0) {
  std::cout << "  [Constructor] Створено об'єкт ResourcePool #" << pool_id_
            << " (" << pool_name_ << ")\n";
}

ResourcePool::ResourcePool(const ResourcePool &other)
    : pool_id_(other.pool_id_), pool_name_(other.pool_name_),
      location_(other.location_), equipment_units_(other.equipment_units_),
      software_licenses_(other.software_licenses_),
      material_units_(other.material_units_),
      allocated_equipment_(other.allocated_equipment_),
      allocated_licenses_(other.allocated_licenses_),
      allocated_materials_(other.allocated_materials_) {
  std::cout << "  [Copy Constructor] Створено копію пулу ресурсів: "
            << pool_name_ << "\n";
}

ResourcePool::~ResourcePool() {
  std::cout << "  [Destructor] Знищено об'єкт ResourcePool #" << pool_id_
            << " (" << pool_name_ << ")\n";
}

bool ResourcePool::AllocateEquipment(int units) {
  if (allocated_equipment_ + units > equipment_units_) {
    std::cout << "  [ResourcePool] Недостатньо обладнання у '" << pool_name_
              << "'\n";
    return false;
  }
  allocated_equipment_ += units;
  return true;
}

bool ResourcePool::AllocateLicenses(int count) {
  if (allocated_licenses_ + count > software_licenses_) {
    std::cout << "  [ResourcePool] Недостатньо ліцензій у '" << pool_name_
              << "'\n";
    return false;
  }
  allocated_licenses_ += count;
  return true;
}

bool ResourcePool::AllocateMaterials(int units) {
  if (allocated_materials_ + units > material_units_) {
    std::cout << "  [ResourcePool] Недостатньо матеріалів у '" << pool_name_
              << "'\n";
    return false;
  }
  allocated_materials_ += units;
  return true;
}

int ResourcePool::GetFreeUnits() const {
  return (equipment_units_ - allocated_equipment_) +
         (software_licenses_ - allocated_licenses_) +
         (material_units_ - allocated_materials_);
}

void ResourcePool::PrintInfo() const {
  std::cout << "    [Ресурси #" << pool_id_ << "] " << pool_name_ << " ("
            << location_ << ") | Обладнання: " << allocated_equipment_ << "/"
            << equipment_units_ << " | Ліцензії ПЗ: " << allocated_licenses_
            << "/" << software_licenses_
            << " | Матеріали: " << allocated_materials_ << "/"
            << material_units_ << " | Вільно одиниць: " << GetFreeUnits()
            << "\n";
}
