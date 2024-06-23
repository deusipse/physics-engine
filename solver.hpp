#pragma once
#include "vec2.hpp"
#include <iostream>
#include <vector>

struct Ball {
  vec2 position;
  vec2 velocity;
  vec2 acceleration;
  float mass;
  float radius;

  Ball(vec2 pos, float m, float r) : position(pos), velocity(0, 0), acceleration(0, 0), mass(m), radius(r) {}
};

struct Plane {
  vec2 position;
  float length;
  float angle;

  Plane(vec2 pos, float l, float th) : position(pos), length(l), angle(th) {}
};

class World {
private:
  vec2 gravity = vec2(0, 500);
  std::vector<Ball> balls;
  std::vector<Plane> planes;

public:
  void addBall(vec2 position, float mass, float radius) {
    balls.emplace_back(position, mass, radius);
  }

  void addPlane(vec2 position, float mass, float radius) {
    balls.emplace_back(position, mass, radius);
  }

  void setVelocity(int i, vec2 velocity) {
    balls[i].velocity = velocity;
  }

  void setAcceleration(int i, vec2 acceleration) {
    balls[i].acceleration = acceleration;
  }

  void update(float dt) {
    for (auto &ball : balls) {
      ball.position += ball.velocity * dt;
      ball.velocity += gravity * dt;
      std::cout << "(" << ball.position.x << ' ' << ball.position.y << ") [" << ball.velocity.x << ' ' << ball.velocity.y << "]  ";
    }
    std::cout << '\n';
    applyConstraint();
  }

  void applyConstraint() {
    for (auto &ball : balls) {
      vec2 circle_pos = vec2(500, 400);
      float circle_radius = 300;
      float dist = (circle_pos - ball.position).magnitude();
      if (dist > circle_radius - ball.radius) {
        vec2 n = (circle_pos - ball.position) * (1.0 / dist);
        ball.position = circle_pos - n * (circle_radius - ball.radius);
        // ball.velocity = {0, 0};
      }
    }
  }

  const std::vector<Ball> &getBalls() const {
    return balls;
  }

  const std::vector<Plane> &getPlanes() const {
    return planes;
  }
};
