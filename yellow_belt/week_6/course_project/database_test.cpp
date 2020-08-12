#include "database.h"
#include "test_runner.h"
#include "condition_parser.h"

#include <sstream>
using namespace std;

void TestDatabase() {
  {
    Database db;
    db.Add(Date(2017, 11, 21), "Tuesday");
    db.Add(Date(2017, 11, 20), "Monday");
    db.Add(Date(2017, 11, 21), "Weekly meeting");
    istringstream is("date > 2017-11-20");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
      return condition->Evaluate(date, event);
    };
    db.RemoveIf(predicate);
    AssertEqual(db.Last(Date(2017, 11, 30)),
                make_pair<Date, string>(Date(2017, 11, 20), "Monday"),
                  "Incorrect Last work");
    try {
      db.Last(Date(2017, 11, 1));
      Assert(false, "No exception in the Last");
    } catch (invalid_argument& ex) {}
  }
  {
    Database db;
    db.Add(Date(1, 1, 1), "a");
    db.Add(Date(1, 1, 3), "b");
    db.Add(Date(1, 1, 5), "c");
    db.Add(Date(1, 1, 5), "d");
    AssertEqual(db.Last(Date(1, 1, 1)),
                make_pair<Date, string>(Date(1, 1, 1), "a"),
                "Incorrect Last work");
    AssertEqual(db.Last(Date(1, 1, 4)),
                make_pair<Date, string>(Date(1, 1, 3), "b"),
                "Incorrect Last work");
    AssertEqual(db.Last(Date(1, 1, 6)),
                make_pair<Date, string>(Date(1, 1, 5), "d"),
                "Incorrect Last work");
    AssertEqual(db.Last(Date(1000, 10, 25)),
                make_pair<Date, string>(Date(1, 1, 5), "d"),
                "Incorrect Last work");
  }
  {
    Database db;
    db.Add(Date(1, 1, 1), "a");
    db.Add(Date(1, 1, 3), "b");
    db.Add(Date(1, 1, 5), "c");
    db.Add(Date(1, 1, 5), "d");
    auto predicate = [](const Date &date, const string &event) {
      return true;
    };
    db.RemoveIf(predicate);
    AssertEqual(db.FindIf(predicate), vector<pair<Date, string>>(), "Incorrect RemoveIf work");
  }
  {
    Database db;
    try {
      db.Last(Date(1, 1, 1));
      Assert(false, "No exception in the Last");
    } catch (invalid_argument& ex) {}
  }
  {
    Database db;
    db.Add(Date(1, 1, 1), "a");
    auto predicate = [](const Date &date, const string &event) {
      return true;
    };
    db.RemoveIf(predicate);
    try {
      db.Last(Date(1, 1, 1));
      Assert(false, "No exception in the Last");
    } catch (invalid_argument& ex) {}
  }
  {
    Database db;
    db.Add(Date(1, 1, 1), "a");
    db.Add(Date(1, 1, 2), "b");
    auto predicate = [](const Date &date, const string &event) {
      return true;
    };
    db.RemoveIf(predicate);
    try {
      db.Last(Date(1, 1, 2));
      Assert(false, "No exception in the Last");
    } catch (invalid_argument& ex) {}
  }
}
