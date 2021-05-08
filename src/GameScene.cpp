//
// Created by hewis on 11/04/2021.
//

#include "ASGEGameLib/Scenes/GameScene.h"
#include "Engine/Logger.hpp"
#include <array>
#include <utility>

GameScene::GameScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)), tile_map(renderer, "levels/dotonbori.json"),
  players(
    std::array<Player, 4>{ Player(renderer, ASGE::Point2D(400, 400), 0, audio_engine.get()),
                           Player(renderer, ASGE::Point2D(500, 500), 1, audio_engine.get()),
                           Player(renderer, ASGE::Point2D(600, 600), 2, audio_engine.get()),
                           Player(renderer, ASGE::Point2D(700, 700), 3, audio_engine.get()) }),
  player_cameras(
    std::array<ASGE::Camera, 4>{ ASGE::Camera(
                                   static_cast<float>(ASGE::SETTINGS.window_width) / 2,
                                   static_cast<float>(ASGE::SETTINGS.window_height) / 2),
                                 ASGE::Camera(
                                   static_cast<float>(ASGE::SETTINGS.window_width) / 2,
                                   static_cast<float>(ASGE::SETTINGS.window_height) / 2),
                                 ASGE::Camera(
                                   static_cast<float>(ASGE::SETTINGS.window_width) / 2,
                                   static_cast<float>(ASGE::SETTINGS.window_height) / 2),
                                 ASGE::Camera(
                                   static_cast<float>(ASGE::SETTINGS.window_width) / 2,
                                   static_cast<float>(ASGE::SETTINGS.window_height) / 2)})
{
  for (auto& camera : player_cameras)
  {
    camera.setZoom(0.5F);
  }
}
void GameScene::update(InputTracker& input, float dt)
{
  Scene::update(input, dt);
  for (int i = 0; i < 4; i++)
  {
    if(!players[i].is_dead)
    {
      players[i].input(input, dt);
      for (auto& trace_point : players[0].getWeapon().bullet.trace_points)
      {
        if (players[i].isInside(trace_point))
        {
          if(i != 0)
          {
            players[0].getWeapon().bullet.hit_point = trace_point;
            players[0].getWeapon().bullet.has_hit = true;
            Logging::DEBUG("HIT by player 1");
            players[i].takeDamage(players[0].getWeapon().bullet.damage);
            break;
          }
        }
      }
      for (auto& trace_point : players[1].getWeapon().bullet.trace_points)
      {
        if (players[i].isInside(trace_point))
        {
          if(i != 1)
          {
            players[1].getWeapon().bullet.hit_point = trace_point;
            players[1].getWeapon().bullet.has_hit = true;
            Logging::DEBUG("HIT by player 2");
            players[i].takeDamage(players[1].getWeapon().bullet.damage);
            break;
          }
        }
      }
      for (auto& trace_point : players[2].getWeapon().bullet.trace_points)
      {
        if (players[i].isInside(trace_point))
        {
          if (i != 2)
          {
            players[2].getWeapon().bullet.hit_point = trace_point;
            players[2].getWeapon().bullet.has_hit = true;
            Logging::DEBUG("HIT by player 3");
            players[i].takeDamage(players[2].getWeapon().bullet.damage);
            break;
          }
        }
      }
      for (auto& trace_point : players[3].getWeapon().bullet.trace_points)
      {
        if (players[i].isInside(trace_point))
        {
          if(i != 3)
          {
            players[3].getWeapon().bullet.hit_point = trace_point;
            players[3].getWeapon().bullet.has_hit = true;
            Logging::DEBUG("HIT by player 4");
            players[i].takeDamage(players[3].getWeapon().bullet.damage);
            break;
          }
        }
      }
    }
  }
  if (input.getKeyDown(ASGE::KEYS::KEY_ESCAPE))
  {
    setScene(Scenes::TITLE);
  }
}
void GameScene::render(ASGE::Renderer* renderer)
{
  auto renderer_viewport = renderer->getViewport();
  int index              = 0;
  for (auto& camera : player_cameras)
  {
    auto player_pos = players[static_cast<size_t>(index)].centre();
    camera.lookAt(ASGE::Point2D(
      player_pos.x / camera.getZoom() + static_cast<float>(ASGE::SETTINGS.window_width) / 4,
      player_pos.y / camera.getZoom() + static_cast<float>(ASGE::SETTINGS.window_height) / 4));
    renderer->setViewport({ (index % 2) * ASGE::SETTINGS.window_width / 2,
                            (1 - index / 2) * ASGE::SETTINGS.window_height / 2,
                            static_cast<uint32_t>(ASGE::SETTINGS.window_width / 2),
                            static_cast<uint32_t>(ASGE::SETTINGS.window_height / 2) });
    renderer->setProjectionMatrix(camera.getView());


    Scene::render(renderer);

    tile_map.render(renderer);
    for (auto& player : players)
    {
      player.render(renderer);
    }

    index++;
  }
  renderer->setViewport(renderer_viewport);
  renderer->setProjectionMatrix(
    0,
    0,
    static_cast<float>(ASGE::SETTINGS.window_width),
    static_cast<float>(ASGE::SETTINGS.window_height));
}
