#include "renderer.hpp"
#include "solver.hpp"
#include "vec2.hpp"

constexpr int window_height = 850, window_width = 1200;
constexpr int frame_rate = 500;

int main() {
  sf::RenderWindow window(sf::VideoMode(window_width, window_height), "physics");
  Renderer renderer(window);
  World world;

  world.setConstraint(600, 425, 400);

  // world.addBall(vec2(50, 0), 1, 20);
  // world.addBall(vec2(400, 400), 1, 20);
  // world.addBall(vec2(400, 0), 1, 20);
  // world.setVelocity(0, {200, 0});
  // for (int i = 0; i < 500; i+=4) {
  //   world.addBall(vec2(i+220, 400), 1, 2);
  // }

  sf::Clock clock;
  sf::Clock clock2;
  float dt = 1.0 / frame_rate;
  float accumulator = 0;
  while (window.isOpen()) {
    sf::Time elapsed = clock.restart();
    float dt_frame = elapsed.asSeconds();
    accumulator += dt_frame;

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    while (accumulator >= dt) {
      if (world.getNumBalls() < 2700) {
      // if (clock2.getElapsedTime().asSeconds() > 1.0f / 1000) {
        clock2.restart();
        world.addBall(vec2(400, 200), 1, 7);
        // std::cout << world.getNumBalls() << '\n';
      }
      world.update(dt);
      accumulator -= dt;
    }
    renderer.render(world);
  }

  return 0;
}
