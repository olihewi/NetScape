//
// Created by hewis on 11/04/2021.
//

#include "ASGEGameLib/Scenes/GameScene.h"
#include <utility>
#include <array>
#include "Engine/Logger.hpp"

GameScene::GameScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)), tile_map(renderer, "levels/dotonbori.json"),
  players(std::array<Player, 4>{ Player(renderer, ASGE::Point2D(400, 400), 0, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(500, 500), 1, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(600, 600), 2, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(700, 700), 3, audio_engine.get())})

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

/*    if(players[0].weapon.bullet.bullet_sprite.isInside(player.AnimatedSprite::position()))
    {
      player.takeDamage(players[0].bullet.damage);
    }

    if(players[1].bullet.bullet_sprite.isInside(player.AnimatedSprite::position()))
    {
      Logging::DEBUG("Shot by player 2");
      player.takeDamage(players[1].bullet.damage);
    }

    if(players[2].bullet.bullet_sprite.isInside(player.AnimatedSprite::position()))
    {
      Logging::DEBUG("Shot by player 3");
      player.takeDamage(players[2].bullet.damage);
    }

    if(players[3].bullet.bullet_sprite.isInside(player.AnimatedSprite::position()))
    {
      Logging::DEBUG("Shot by player 4");
      player.takeDamage(players[3].bullet.damage);
    }*/
  }
  if (input.getKeyDown(ASGE::KEYS::KEY_ESCAPE))
  {
    setScene(Scenes::TITLE);
  }
}