//
// Created by hewis on 11/04/2021.
//

#include "ASGEGameLib/Scenes/GameScene.h"

#include <GameObjects/Sprites/Text.h>
#include <utility>
GameScene::GameScene(ASGE::Renderer* renderer, std::function<void(Scene::Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback))
{
  addObject(std::make_unique<Text>(renderer, "Game Scene", ASGE::Point2D(200, 200)));
}
