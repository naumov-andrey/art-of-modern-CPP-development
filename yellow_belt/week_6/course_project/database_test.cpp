#include "database.h"
#include "test_runner.h"
#include "condition_parser.h"

#include <sstream>
using namespace std;

void TestDatabase() {
  const auto any = [](const Date &date, const string &event) {
    return true;
  };
  const vector<pair<Date, string>> empty;
  const Date zero_date(0, 1, 1);
  const Date last_date(9999, 12, 31);

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
    db.RemoveIf(any);
    AssertEqual(db.FindIf(any), empty, "Empty DB: incorrect RemoveIf or FindIf");
  }

  {
    Database db;
    try {
      db.Last(zero_date);
      Assert(false, "Empty DB: incorrect Last");
    } catch (invalid_argument&) {}
  }

  {
    Database db;
    db.Add(zero_date, "a");
    db.Add(zero_date, "aa");
    db.Add(zero_date, "aaa");

    istringstream is("event >= \"aa\"");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
      return condition->Evaluate(date, event);
    };

    AssertEqual(db.RemoveIf(predicate), 2, "Should be deleted 2 records: incorrect RemoveIf");

    vector<pair<Date, string>> expected;
    expected.emplace_back(zero_date, "a");

    AssertEqual(db.FindIf(any), expected, "Should be one record 0-1-1 'a': incorrect FindIf");
  }

  {
    Database db;
    for (int i = 0; i < 3; ++i) {
      db.Add(zero_date, "a");
      db.Add(zero_date, "aa");
      db.Add(zero_date, "aaa");
      db.Add(zero_date, "aaaa");
      AssertEqual(db.RemoveIf(any), 4, "Should be deleted 2 records: incorrect RemoveIf");
    }
  }

  {
    Database db;
    db.Add(zero_date, "a");
    db.Add(zero_date, "aa");
    db.Add(zero_date, "aaa");

    vector<pair<Date, string>> expected;
    expected.emplace_back(zero_date, "a");
    expected.emplace_back(zero_date, "aa");
    expected.emplace_back(zero_date, "aaa");

    AssertEqual(db.FindIf(any), expected, "Should be in order: a aa aaa");
  }

  {
    Database db;

    stringstream ios;

    db.Print(ios);
    AssertEqual(ios.str(), "", "Empty DB: incorrect Print");
  }

  {
    Database db;
    db.Add(zero_date, "a");

    stringstream ios;

    db.Print(ios);
    AssertEqual(ios.str(), "0000-01-01 a\n", "Should be '0000-01-01 a': incorrect Print");
  }

  {
    Database db;
    db.Add(zero_date, "a");
    db.Add(zero_date, "aa");
    db.Add(zero_date, "aaa");
    auto result = db.Last(zero_date);
    AssertEqual(result.first, zero_date, "Should be '0000-01-01': incorrect Last");
    AssertEqual(result.second, "aaa", "Should be 'aaa': incorrect Last");
    result = db.Last(last_date);
    AssertEqual(result.first, zero_date, "Should be '0000-01-01': incorrect Last");
    AssertEqual(result.second, "aaa", "Should be 'aaa': incorrect Last");
  }

  {
    Database db;
    db.Add(zero_date, "a");
    db.Add(zero_date, "aa");
    db.Add(zero_date, "aaa");
    db.Add(last_date, "b");
    db.Add(last_date, "bb");
    db.Add(last_date, "bbb");
    {
      istringstream is("event >= \"bb\"");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
      };

      AssertEqual(db.RemoveIf(predicate), 2, "Should be removed 2 records: incorrect RemoveIf");
      AssertEqual(db.RemoveIf(predicate), 0, "Should be removed 0 records: incorrect RemoveIf");
    }
    {
      istringstream is("date > 0-1-1 AND event != \"b\"");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
      };

      AssertEqual(db.RemoveIf(predicate), 0, "Should be removed 0 records: incorrect RemoveIf");
    }
    {
      istringstream is("date >= 0-1-1 AND event > \"aa\"");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
      };

      AssertEqual(db.RemoveIf(predicate), 2, "Should be removed 2 records: incorrect RemoveIf");
      AssertEqual(db.RemoveIf(predicate), 0, "Should be removed 0 records: incorrect RemoveIf");
    }
    {
      istringstream is("date < 0-1-2");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
      };

      AssertEqual(db.RemoveIf(predicate), 2, "Should be removed 2 records: incorrect RemoveIf");
      AssertEqual(db.RemoveIf(predicate), 0, "Should be removed 0 records: incorrect RemoveIf");
    }
  }

  {
    Database db;
    db.Add( { 2017, 6, 1 }, "work");
    db.Add( { 2017, 6, 1 }, "sleep");
    db.Add( { 2017, 6, 2 }, "work");
    db.Add( { 2017, 6, 3 }, "work");
    db.Add( { 2017, 6, 4 }, "work");
    db.Add( { 2017, 6, 5 }, "sleep");
    {
      istringstream is("event == \"work\"");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
      };

      AssertEqual(db.RemoveIf(predicate), 4, "Should be removed 4 records: incorrect RemoveIf");
      AssertEqual(db.RemoveIf(predicate), 0, "Should be removed 0 records: incorrect RemoveIf");
    }

    stringstream ios;

    db.Print(ios);
    AssertEqual(ios.str(), "2017-06-01 sleep\n2017-06-05 sleep\n", "Print after RemoveIf work");

    vector<pair<Date, string>> expected;
    expected.emplace_back(Date(2017, 6, 1), "sleep");

    {
      istringstream is("date <= 2017-06-03");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
      };

      AssertEqual(db.FindIf(predicate), expected, "Check 2017-06-03 work");
    }
  }

  {
    Database db;
    db.Add({2017, 1, 1}, "first");
    db.Add({2017, 1, 1}, "second");
    db.Add({2017, 1, 1}, "third");
    db.Add({2017, 1, 1}, "fourth");
    db.Add({2017, 1, 1}, "five");
    {
      istringstream is("event == \"second\" OR event == \"fourth\"");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
      };

      AssertEqual(db.RemoveIf(predicate), 2, "Should be removed 2 records: incorrect RemoveIf");
      AssertEqual(db.RemoveIf(predicate), 0, "Should be removed 0 records: incorrect RemoveIf");
    }

    stringstream ios;

    db.Print(ios);
    AssertEqual(ios.str(), "2017-01-01 first\n2017-01-01 third\n2017-01-01 five\n",
                "Check print after remove several- 3");
  }

  {
    Database db;
    db.Add(Date(1, 1, 1), "a");
    db.Add(Date(2, 2, 2), "b");

    auto result = db.Last(Date(1, 12, 31));
    AssertEqual(result.first, Date(1, 1, 1), "Last check");
    AssertEqual(result.second, "a", "Last check");
  }

  {
    Database db;
    db.Add(zero_date, "a");
    db.Add(zero_date, "b");
    db.Add(zero_date, "c");
    db.Add(zero_date, "d");
    db.Add(zero_date, "e");
    db.Add(zero_date, "j");
    db.Add(zero_date, "g");
    db.Add(zero_date, "k");
    db.Add(zero_date, "l");
    db.Add(zero_date, "m");
    db.Add(zero_date, "n");
    db.Add(zero_date, "o");
    db.Add(zero_date, "p");
    db.Add(zero_date, "r");
    db.Add(zero_date, "s");
    db.Add(zero_date, "t");
    db.Add(zero_date, "y");
    db.Add(zero_date, "x");
    db.Add(zero_date, "z");
    {
      istringstream is("event >= \"b\"");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
      };

      AssertEqual(db.RemoveIf(predicate), 18, "Should be removed 18 records: incorrect RemoveIf");
      AssertEqual(db.RemoveIf(predicate), 0, "Should be removed 0 records: incorrect RemoveIf");
    }

    vector<pair<Date, string>> expected;
    expected.emplace_back(zero_date, "a");

    AssertEqual(db.FindIf(any), expected, "Check FindIf");
  }
}
