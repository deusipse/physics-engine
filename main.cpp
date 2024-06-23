#include "renderer.hpp"
#include "solver.hpp"
#include "vec2.hpp"

constexpr int window_height = 800, window_width = 1000;
constexpr int frame_rate = 120;

int main() {
  sf::RenderWindow window(sf::VideoMode(window_width, window_height), "physics");
  Renderer renderer(window);
  World world;

  world.addBall(vec2(50, 100), 1, 20);
  world.addBall(vec2(500, 400), 1, 20);
  world.setVelocity(0, {200, -200});

  sf::Clock clock;
  float dt = 1.0 / frame_rate;
  window.setFramerateLimit(frame_rate);

  while (window.isOpen()) {
    sf::Time elapsed = clock.restart();
    dt = elapsed.asSeconds();

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    world.update(dt);
    renderer.render(world);
  }

  return 0;
}
