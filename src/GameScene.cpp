//
// Created by hewis on 11/04/2021.
//

#include "ASGEGameLib/Scenes/GameScene.h"
#include "GameObjects/Sprites/AnimatedSprite.h"
#include "Utilities/FontManager.h"

#include <GameObjects/Sprites/Text.h>
#include <utility>
GameScene::GameScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)),
  players(std::array<Player, 4>{ Player(
                                   renderer, "data/images/tilesets/cursor.png",
                                   ASGE::Point2D(400, 400), ASGE::Point2D(50, 50), 1, 1, 1),
                                 Player(
                                   renderer, "data/images/animations/japanese_city/crow_ground.png",
                                   ASGE::Point2D(500, 500), ASGE::Point2D(50, 50), 1, 1, 2),
                                 Player(
                                   renderer, "data/images/animations/japanese_city/crow_ground.png",
                                   ASGE::Point2D(600, 600), ASGE::Point2D(50, 50), 1, 1, 3),
                                 Player(
                                   renderer, "data/images/animations/japanese_city/crow_ground.png",
                                   ASGE::Point2D(700, 700), ASGE::Point2D(50, 50), 1, 1, 4) })
{
  addObject(std::make_unique<Text>(renderer, "Game Scene", ASGE::Point2D(200, 200)));
}
void GameScene::render(ASGE::Renderer* renderer)
{
  Scene::render(renderer);

  for (auto& player : players)
  {
    player.render(renderer);
  }
}
void GameScene::update(InputTracker& input, float dt)
{
  Scene::update(input, dt);

  for (auto& player : players)
  {
    player.input(input, dt);
  }
}
