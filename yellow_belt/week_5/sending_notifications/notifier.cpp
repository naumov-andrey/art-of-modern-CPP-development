#include <string>

using namespace std;

void SendSms(const string& number, const string& message);

void SendEmail(const string& email, const string& message);

struct INotifier {
  virtual void Notify(const string& message) = 0;
};

class SmsNotifier : public INotifier {
public:
  explicit SmsNotifier(const string& number) : number_(number) {}

  void Notify(const string &message) override {
    SendSms(number_, message);
  }

private:
  string number_;
};

class EmailNotifier : public INotifier {
public:
  explicit EmailNotifier(const string& email) : email_(email) {}

  void Notify(const string &message) override {
    SendEmail(email_, message);
  }

private:
  string email_;
};
