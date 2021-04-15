//
// Created by hewis on 11/04/2021.
//

#include "ASGEGameLib/Scenes/GameScene.h"
#include "GameObjects/Sprites/AnimatedSprite.h"
#include "Utilities/FontManager.h"

#include <GameObjects/Sprites/Text.h>
#include <utility>
GameScene::GameScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback))
{
  addObject(std::make_unique<Text>(renderer, "Game Scene", ASGE::Point2D(200, 200)));
  addObject(std::make_unique<AnimatedSprite>(
    renderer, "data/images/animations/japanese_city/crow_ground.png", 10, ASGE::Point2D(300, 200)));
}
void GameScene::render(ASGE::Renderer* renderer)
{
  Scene::render(renderer);
}
void GameScene::controllerInput(ControllerTracker& /*controllers*/, float /*dt*/) {}
