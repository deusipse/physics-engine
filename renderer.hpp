#pragma once
#include "solver.hpp"
#include <SFML/Graphics.hpp>

class Renderer {
private:
  sf::RenderWindow &window;

public:
  Renderer(sf::RenderWindow &window) : window(window) {}
  void render(const World &world) const {
    window.clear();

    vec3 constraint = world.getConstraint();
    sf::CircleShape constraint_draw(constraint.z);
    constraint_draw.setOutlineColor(sf::Color::White);
    constraint_draw.setOutlineThickness(10);
    constraint_draw.setFillColor(sf::Color::Black);
    constraint_draw.setPosition(constraint.x - constraint.z, constraint.y - constraint.z);
    constraint_draw.setPointCount(128);
    window.draw(constraint_draw);

    const auto &balls = world.getBalls();
    for (const auto &ball : balls) {
      sf::CircleShape shape(ball.radius);
      shape.setFillColor(sf::Color::White);
      shape.setPosition(ball.position_cur.x - ball.radius, ball.position_cur.y - ball.radius);
      window.draw(shape);
    }

    window.display();
  }
};
