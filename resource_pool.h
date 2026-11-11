#ifndef LAB4_RESOURCE_POOL_H_
#define LAB4_RESOURCE_POOL_H_

#include <string>

// [ЛР4, п.4] ResourcePool — другий додатковий базовий клас для множинного
// наслідування (обладнання, програмне забезпечення, матеріали)
class ResourcePool {
public:
  ResourcePool();
  // [ЛР4, п.5] Конструктор базового класу з 6 параметрами
  ResourcePool(int pool_id, const std::string &pool_name,
               const std::string &location, int equipment_units,
               int software_licenses, int material_units);
  ResourcePool(const ResourcePool &other);
  ~ResourcePool();

  bool AllocateEquipment(int units);
  bool AllocateLicenses(int count);
  bool AllocateMaterials(int units);
  int GetFreeUnits() const;
  void PrintInfo() const;

private:
  int pool_id_;
  std::string pool_name_;
  std::string location_;
  int equipment_units_;
  int software_licenses_;
  int material_units_;
  int allocated_equipment_;
  int allocated_licenses_;
  int allocated_materials_;
};

#endif // LAB4_RESOURCE_POOL_H_
