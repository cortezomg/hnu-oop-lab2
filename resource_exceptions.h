#ifndef LAB5_RESOURCE_EXCEPTIONS_H_
#define LAB5_RESOURCE_EXCEPTIONS_H_

#include <stdexcept>

// [ЛР5, п.7] Власні класи винятків для роботи з файлами
class FileOpenError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

class FileFormatError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

#endif // LAB5_RESOURCE_EXCEPTIONS_H_
