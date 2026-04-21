#pragma once

struct Vector final {
  Vector() noexcept : x(0), y(0) {}
  explicit Vector(const int x_, const int y_) : x(x_), y(y_) {}
  inline Vector operator-(const Vector &other) const noexcept {
    return Vector(x - other.x, y - other.y);
  }
  inline Vector operator+(const Vector &other) const noexcept {
    return Vector(x + other.x, y + other.y);
  }

  int x = 0, y = 0;
};
