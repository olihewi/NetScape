//
// Created by hewis on 01/04/2021.
//

#include "Scenes/TestScene.h"
#include <GameObjects/Sprites/AnimatedSprite.h>

#include <utility>
TestScene::TestScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback))
{
  auto crow_sprite = std::make_unique<AnimatedSprite>(
    renderer, "data/images/animations/japanese_city/crow_ground.png", 10, ASGE::Point2D(200, 200));
  crow_sprite->dimensions(ASGE::Point2D(200, 200));
  addObject(std::move(crow_sprite));
}
