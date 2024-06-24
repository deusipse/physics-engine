#pragma once
#include "vec2.hpp"
#include <iostream>
#include <vector>

struct Ball {
  vec2 position_prev;
  vec2 position_cur;
  vec2 acceleration;
  float mass;
  float radius;

  Ball(vec2 pos, float m, float r) : position_prev(pos), position_cur(pos), acceleration(0, 0), mass(m), radius(r) {}

  float getVelocity(float dt) {
    return (position_cur - position_prev).magnitude() * 1 / dt;
  }

  void update(float dt) {
    vec2 displacement = position_cur - position_prev;
    position_prev = position_cur;
    position_cur = position_cur + displacement + acceleration * dt * dt;
    // std::cout << getVelocity(dt) << ' ';

    acceleration = {0, 0};
  }
};

class World {
private:
  vec2 gravity = vec2(0, 500);
  std::vector<Ball> balls;
  vec2 constraint = vec2(500, 400);
  float constraint_radius = 300;

public:
  void addBall(vec2 position, float mass, float radius) {
    balls.emplace_back(position, mass, radius);
  }

  void setAcceleration(int i, vec2 acceleration) {
    balls[i].acceleration = acceleration;
  }

  void update(float dt) {
    applyGravity();
    applyConstraint();
    applyCollisions();
    updateBalls(dt);
  }

  void applyGravity() {
    for (auto &ball : balls) {
      ball.acceleration += gravity;
    }
  }

  void updateBalls(float dt) {
    for (auto &ball : balls) {
      ball.update(dt);
    }
    // std::cout << '\n';
  }

  void applyConstraint() {
    for (auto &ball : balls) {
      float dist = (constraint - ball.position_cur).magnitude_squared();
      float min_dist = constraint_radius - ball.radius;
      if (dist > min_dist * min_dist) {
        vec2 n = (constraint - ball.position_cur) * (1.0 / sqrt(dist));
        ball.position_cur = constraint - n * (min_dist);
      }
    }
  }

  void applyCollisions() {
    int num_balls = balls.size();
    for (int i = 0; i < num_balls; i++) {
      for (int j = i + 1; j < num_balls; j++) {
        float dist = (balls[i].position_cur - balls[j].position_cur).magnitude_squared(); // distance between the balls squared
        float min_dist = balls[i].radius + balls[j].radius;                               // minimum radius before intersection
        if (dist < min_dist * min_dist) {
          dist = (balls[i].position_cur - balls[j].position_cur).magnitude();      // distance between the balls
          vec2 n = (balls[i].position_cur - balls[j].position_cur) * (1.0 / dist); // normalised vector between balls
          float intersection = balls[i].radius + balls[j].radius - dist;
          balls[i].position_cur += n * (intersection / balls[i].radius);
          balls[j].position_cur -= n * (intersection / balls[j].radius);
        }
      }
    }
  }

  void setConstraint(float x, float y, float z) {
    constraint = vec2(x, y);
    constraint_radius = z;
  }

  const vec3 getConstraint() const {
    return {constraint.x, constraint.y, constraint_radius};
  }

  const std::vector<Ball> &getBalls() const {
    return balls;
  }

  int getNumBalls() {
    return balls.size();
  }
};
