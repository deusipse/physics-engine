#pragma once
#include <cmath>

struct vec2 {
  float x, y;
  vec2(float x, float y) : x(x), y(y) {}
  void operator+=(const vec2 &v) {
    x += v.x;
    y += v.y;
  }
  vec2 operator+(const vec2 &v) {
    return vec2(x + v.x, y + v.y);
  }
  void operator-=(const vec2 &v) {
    x -= v.x;
    y -= v.y;
  }
  vec2 operator-(const vec2 &v) {
    return vec2(x - v.x, y - v.y);
  }
  void operator*=(const float c) {
    x *= c;
    y *= c;
  }
  vec2 operator*(const float c) {
    return vec2(x * c, y * c);
  }
  float magnitude() {
    return sqrtf(x * x + y * y);
  }
  float magnitude_squared() {
    return x * x + y * y;
  }
  float dot(const vec2 &v) {
    return x * v.x + y * v.y;
  }
};

struct vec3 {
  float x, y, z;
};
