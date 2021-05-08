//
// Created by hewis on 01/04/2021.
//

#include "Scenes/TestScene.h"
#include <GameObjects/Sprites/AnimatedSprite.h>

#include <utility>
TestScene::TestScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)),
  crow_sprite(
    renderer, "data/images/animations/japanese_city/crow_ground.png", 10, ASGE::Point2D(200, 200))
{
  crow_sprite.dimensions(ASGE::Point2D(200, 200));
}
void TestScene::update(InputTracker& input, float dt)
{
  Scene::update(input, dt);

  crow_sprite.update(input, dt);

  auto left_stick = input.getControllerStick(0, CONTROLLER::STICKS::LEFT);

  crow_sprite.translate(left_stick * dt * 100);
}

void TestScene::render(ASGE::Renderer* renderer)
{
  Scene::render(renderer);

  crow_sprite.render(renderer);
}
