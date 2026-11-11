#ifndef LAB4_INTERN_H_
#define LAB4_INTERN_H_

#include <string>

#include "worker.h"

// [ЛР4, п.1, п.2] Intern — закрите (private) наслідування від Worker:
// відкриті та захищені члени Worker стають закритими в Intern
class Intern : private Worker {
public:
  Intern();
  Intern(int id, const char *name_str, double rate,
         const std::string &university, const std::string &specialty,
         int course_year, int internship_weeks, double stipend,
         int mentor_id);
  Intern(const Intern &other);
  ~Intern();

  void CompleteTrainingTask();
  double CalculateStipend() const;
  void ExtendInternship(int weeks);
  void ShowInheritedAccess();
  void PrintInfo() const;

  int get_mentor_id() const { return mentor_id_; }

private:
  std::string university_;
  std::string specialty_;
  int course_year_;
  int internship_weeks_;
  double stipend_;
  int mentor_id_;
  int learned_skills_count_;
  bool is_paid_;
};

#endif // LAB4_INTERN_H_
