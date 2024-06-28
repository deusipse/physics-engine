#pragma once
#include "vec2.hpp"
#include <iostream>
#include <vector>

struct Ball { // Particles are balls with radius and mass
  vec2 position;
  vec2 velocity;
  vec2 acceleration;
  float mass;
  float radius;
  Ball(vec2 pos, float m, float r) : position(pos), velocity(0, 0), acceleration(0, 0), mass(m), radius(r) {}

  void update(float dt) {
    velocity += acceleration * dt;
    position += velocity * dt;
    acceleration = vec2(0, 0);
    // printf("(%f)\n", velocity.magnitude());
  }
};

class World {
private:
  std::vector<Ball> balls;
  vec2 gravity = vec2(0, 1000);
  int substeps = 1;
  vec2 constraintPosition = vec2(600, 425);
  float constraintRadius = 400;

public:
  void setVelocity(int i, vec2 velocity) {
    balls[i].velocity = velocity;
  }

  void setSubsteps(int i) {
    substeps = i;
  }

  void addBall(vec2 pos, float m, float r) {
    balls.emplace_back(pos, m, r);
  }

  void setConstraint(vec2 pos, float r) {
    constraintPosition = pos;
    constraintRadius = r;
  }

  void update(float dt) {
    dt = dt / substeps;
    for (int i = 0; i < substeps; ++i) {
      applyGravity();
      applyConstraint();
      applyCollisions();
      updateBalls(dt);
    }
  }

  void applyGravity() {
    for (Ball &ball : balls) {
      ball.acceleration += gravity;
    }
  }

  void applyConstraint() {
    for (Ball &ball : balls) {
      float dSquared = (ball.position - constraintPosition).magnitudeSquared();
      float minDist = constraintRadius - ball.radius;
      if (dSquared > minDist * minDist) {
        fuckUpBall(ball, minDist);
        vec2 normal = (ball.position - constraintPosition) * (-1 / sqrt(dSquared)); // normal of contact between ball and constraint
        ball.position = constraintPosition - normal * minDist;
        ball.velocity = (ball.velocity - normal * (2 * ball.velocity.dot(normal))) * 1;
      }
    }
  }

  void fuckUpBall(Ball &ball, float &minDist) {
    ball.radius *= 1.1;
    minDist = constraintRadius - ball.radius;
  }

  void applyCollisions() {
    int numBalls = balls.size();
    for (int i = 0; i < numBalls; ++i) {
      for (int j = i + 1; j < numBalls; ++j) {
        float dSquared = (balls[i].position - balls[j].position).magnitudeSquared();
        float minDist = balls[i].radius + balls[j].radius;
        if (dSquared < minDist * minDist) {
          vec2 normal = (balls[i].position - balls[j].position) * (1 / sqrt(dSquared)); // normal of contact
          float overlap = minDist - (balls[i].position - balls[j].position).magnitude();
          balls[i].position += normal * (overlap * balls[i].radius / minDist);
          balls[j].position -= normal * (overlap * balls[j].radius / minDist);
          balls[i].velocity = (balls[i].velocity - normal * (2 * balls[i].velocity.dot(normal))) * 1;
          balls[j].velocity = (balls[j].velocity - normal * (2 * balls[j].velocity.dot(normal))) * 1;
        }
      }
    }
  }

  void updateBalls(float dt) {
    for (Ball &ball : balls) {
      ball.update(dt);
    }
  }

  std::vector<Ball> getBalls() {
    return balls;
  }

  int getNumBalls() {
    return balls.size();
  }

  vec3 getConstraint() {
    return {constraintPosition.x, constraintPosition.y, constraintRadius};
  }
};
