//
// Created by hewis on 11/04/2021.
//

#include "ASGEGameLib/Scenes/GameScene.h"
#include <utility>
GameScene::GameScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)), tile_map(renderer, "levels/dotonbori.json"),
  players(std::array<Player, 4>{ Player(
                                   renderer, "data/images/player/survivor-idle_shotgun_0.png",
                                   ASGE::Point2D(400, 400), ASGE::Point2D(50, 50), 1, 1, 0),
                                 Player(
                                   renderer, "data/images/player/survivor-idle_shotgun_0.png",
                                   ASGE::Point2D(500, 500), ASGE::Point2D(50, 50), 1, 1, 1),
                                 Player(
                                   renderer, "data/images/player/survivor-idle_shotgun_0.png",
                                   ASGE::Point2D(600, 600), ASGE::Point2D(50, 50), 1, 1, 2),
                                 Player(
                                   renderer, "data/images/player/survivor-idle_shotgun_0.png",
                                   ASGE::Point2D(700, 700), ASGE::Point2D(50, 50), 1, 1, 3) })
{
  addObject(std::make_unique<Text>(renderer, "Game Scene", ASGE::Point2D(200, 200)));
}
void GameScene::render(ASGE::Renderer* renderer)
{
  Scene::render(renderer);

  tile_map.render(renderer);
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
