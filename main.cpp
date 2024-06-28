#include "renderer.hpp"
#include "solver.hpp"

constexpr int windowWidth = 1200, windowHeight = 850;
constexpr int frameRate = 120;
constexpr int substeps = 8;

int main() {
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "physics");
  window.setFramerateLimit(frameRate);
  Renderer renderer(window);

  World world;
  world.setSubsteps(substeps);
  // for (int i = 0; i < 500; i += 40) {
  //   world.addBall(vec2(400 + i, 400), 1, 20);
  // }

  world.addBall(vec2(400, 400), 1, 20);

  // rendering
  sf::Clock clock;
  float stepTime = 1.0 / frameRate;
  float accumulator = 0.0;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    float frameTime = clock.restart().asSeconds();
    // printf("%f\n", 1 / frameTime);
    accumulator += frameTime;

    while (accumulator >= stepTime) {
      // if (world.getNumBalls() < 3000) {
      //   world.addBall(vec2(601, 400), 1, 4);
      //   printf("%d\n", world.getNumBalls());
      // }
      world.update(stepTime);
      accumulator -= stepTime;
    }

    renderer.render(world);
  }

  return 0;
}
