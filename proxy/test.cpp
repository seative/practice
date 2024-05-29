#include <iostream>
#include <sstream>

#include "proxy.h"

// Abstraction
struct Draw : pro::dispatch<void(std::ostream&)> {
  template <class T>
  void operator()(const T& self, std::ostream& out) {
    self.Draw(out);
  }
};
struct Area : pro::dispatch<double()> {
  template <class T>
  double operator()(const T& self) {
    return self.Area();
  }
};
struct DrawableFacade : pro::facade<Draw, Area> {};

// Implementation (No base class)
class Rectangle {
 public:
  void Draw(std::ostream& out) const {
    out << "{Rectangle: width = " << width_ << ", height = " << height_ << "}";
  }
  void SetWidth(double width) { width_ = width; }
  void SetHeight(double height) { height_ = height; }
  double Area() const { return width_ * height_; }

 private:
  double width_;
  double height_;
};

// Client - Consumer
std::string PrintDrawableToString(pro::proxy<DrawableFacade> p) {
  std::stringstream result;
  result << "shape = ";
  p.invoke<Draw>(result);                     // Polymorphic call
  result << ", area = " << p.invoke<Area>();  // Polymorphic call
  return std::move(result).str();
}

// Client - Producer
pro::proxy<DrawableFacade> CreateRectangleAsDrawable(int width, int height) {
  Rectangle rect;
  rect.SetWidth(width);
  rect.SetHeight(height);
  return pro::make_proxy<DrawableFacade>(
      rect);  // No heap allocation is expected
}

int main() {
  auto rect = CreateRectangleAsDrawable(10, 20);
  std::cout << PrintDrawableToString(rect) << std::endl;
  return 0;
}