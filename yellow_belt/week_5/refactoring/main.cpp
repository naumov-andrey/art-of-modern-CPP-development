#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Citizen {
public:
  explicit Citizen(const string& name, const string& job):
    name_(name),
    job_(job)
  {}

  virtual void Walk(const string& destination) const {
    cout << job_ << ": " << name_ << " walks to: " << destination << endl;
  }

  string GetName() const { return name_;}
  string GetJob() const { return job_;}

protected:
  const string name_;
  const string job_;
};

class Student: public Citizen {
public:
  Student(const string& name, const string& favouriteSong):
    Citizen(name, "Student"),
    favouriteSong_(favouriteSong)
  {}

  void Learn() const {
    cout << job_ << ": " << name_ << " learns" << endl;
  }

  void Walk(const string& destination) const override{
    Citizen::Walk(destination);
    SingSong();
  }

  void SingSong() const {
    cout << job_ << ": " << name_ << " sings a song: " << favouriteSong_ << endl;
  }

protected:
  string favouriteSong_;
};


class Teacher: public Citizen {
public:
  Teacher(const string& name, const string& subject):
    Citizen(name, "Teacher"),
    subject_(subject)
  {}

  void Teach() const {
    cout << job_ << ": " << name_ << " teaches: " << subject_ << endl;
  }

protected:
  string name_;
  string subject_;
};


class Policeman: public Citizen {
public:
  explicit Policeman(const string& name):
    Citizen(name, "Policeman")
  {}

  void Check(const Citizen& c) const {
    cout << "Policeman: " << name_ << " checks " << c.GetJob() << ". "
      << c.GetJob() << "'s name is: " << c.GetName() << endl;
  }
};


void VisitPlaces(const Citizen& t, const vector<string>& places) {
  for (auto p : places) {
    t.Walk(p);
  }
}


int main() {
  Teacher t("Jim", "Math");
  Student s("Ann", "We will rock you");
  Policeman p("Bob");

  VisitPlaces(t, {"Moscow", "London"});
  p.Check(s);
  VisitPlaces(s, {"Moscow", "London"});
  return 0;
}
