#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <vector>
#include <cmath>

using namespace std;

class Figure {
public:
  virtual string Name() = 0;
  virtual double Perimeter() = 0;
  virtual double Area() = 0;
};

class Triangle: public Figure {
public:
  Triangle(int a, int b, int c):
    side1_(a),
    side2_(b),
    side3_(c)
  {}

  string Name() override { return "TRIANGLE";}
  double Perimeter() override { return side1_ + side2_ + side3_;}
  double Area() override {
    double p = (side1_ + side2_ + side3_) / 2.0;
    return sqrt(p * (p - side1_) * (p - side2_) * (p - side3_));
  }

protected:
  int side1_, side2_, side3_;
};

class Rect: public Figure {
public:
  Rect(int width, int height):
    width_(width),
    height_(height)
  {}

  string Name() override { return "RECT";}
  double Perimeter() override { return 2.0 * width_ + 2.0 * height_;}
  double Area() override { return static_cast<double>(width_) * height_;}

protected:
  int width_, height_;
};

class Circle: public Figure {
public:
  explicit Circle(int radius): radius_(radius) {}

  string Name() override { return "CIRCLE";}
  double Perimeter() override { return 2 * 3.14 * radius_;}
  double Area() override { return  3.14 * radius_ * radius_;}

protected:
  int radius_;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
  string figure_type;
  is >> figure_type;
  if (figure_type == "RECT") {
    int w, h;
    is >> w >> h;
    return make_shared<Rect>(w, h);
  } else if (figure_type == "TRIANGLE") {
    int a, b, c;
    is >> a >> b >> c;
    return make_shared<Triangle>(a, b, c);
  } else if (figure_type == "CIRCLE") {
    int r;
    is >> r;
    return make_shared<Circle>(r);
  }
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
