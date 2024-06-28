#pragma once
#include "solver.hpp"
#include <SFML/Graphics.hpp>

class Renderer {
private:
  sf::RenderWindow &window;

public:
  Renderer(sf::RenderWindow &window) : window(window) {}
  void render(World &world) {
    window.clear();

    vec3 c = world.getConstraint();
    sf::CircleShape constraint(c.z);
    constraint.setOutlineColor(sf::Color::White);
    constraint.setOutlineThickness(10);
    constraint.setFillColor(sf::Color::Black);
    constraint.setPosition(c.x - c.z, c.y - c.z);
    constraint.setPointCount(128);
    window.draw(constraint);

    const std::vector<Ball> balls = world.getBalls();
    for (const Ball &ball : balls) {
      sf::CircleShape shape(ball.radius);
      shape.setPosition(ball.position.x - ball.radius, ball.position.y - ball.radius);
      shape.setPointCount(128);
      window.draw(shape);
    }

    window.display();
  }
};
