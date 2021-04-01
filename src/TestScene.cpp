//
// Created by hewis on 01/04/2021.
//

#include "Scenes/TestScene.h"
#include <GameObjects/Sprites/AnimatedSprite.h>
TestScene::TestScene(ASGE::Renderer* renderer)
{
  auto crow_sprite = std::make_unique<AnimatedSprite>(
    renderer, "data/images/animations/japanese_city/crow_ground.png", 10, ASGE::Point2D(200, 200));
  crow_sprite->dimensions(ASGE::Point2D(200, 200));
  addObject(std::move(crow_sprite));
}
