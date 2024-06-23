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

    sf::CircleShape constraint(300);
    constraint.setOutlineColor(sf::Color::White);
    constraint.setOutlineThickness(10);
    constraint.setFillColor(sf::Color::Black);
    constraint.setPosition(500 - 300, 400 - 300);
    constraint.setPointCount(128);
    window.draw(constraint);

    const auto &balls = world.getBalls();
    for (const auto &ball : balls) {
      sf::CircleShape shape(ball.radius);
      shape.setFillColor(sf::Color::White);
      shape.setPosition(ball.position.x - ball.radius, ball.position.y - ball.radius);
      window.draw(shape);
    }

    window.display();
  }
};
