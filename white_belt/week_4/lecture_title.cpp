#include <string>

struct Specialization {
  std::string data;
  explicit Specialization(const std::string& s)
  {
    data = s;
  }
};

struct Course {
  std::string data;
  explicit Course(const std::string& c)
  {
    data = c;
  }
};

struct Week {
  std::string data;
  explicit Week(const std::string& w)
  {
    data = w;
  }
};

struct LectureTitle {
  std::string specialization;
  std::string course;
  std::string week;

  LectureTitle(const Specialization& s, const Course& c, const Week& w)
  {
    specialization = s.data;
    course = c.data;
    week = w.data;
  }
};
