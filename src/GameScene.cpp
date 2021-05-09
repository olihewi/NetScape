//
// Created by hewis on 11/04/2021.
//

#include "ASGEGameLib/Scenes/GameScene.h"
#include "Engine/Logger.hpp"
#include <ASGEGameLib/GameObjects/Player/HUD/PlayerHealth.hpp>
#include <GameObjects/Player/HUD/PlayerAmmo.hpp>
#include <array>
#include <utility>

GameScene::GameScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)), tile_map(renderer, "levels/dotonbori.json"),
  players(std::array<Player, 4>{ Player(renderer, ASGE::Point2D(400, 400), 0, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(500, 500), 1, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(600, 600), 2, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(700, 700), 3, audio_engine.get()) })
{
  for (auto& player : players)
  {
    addObject(std::make_unique<PlayerHealth>(renderer, player));
    auto& camera = player_cameras.emplace_back(std::make_pair(
      ASGE::Camera(
        static_cast<float>(ASGE::SETTINGS.window_width) / 2,
        static_cast<float>(ASGE::SETTINGS.window_height) / 2),
      PlayerHUD()));
    camera.first.setZoom(0.5F);

    camera.second.addObject(std::make_unique<Text>(
      renderer, "Player " + std::to_string(player.getID()), ASGE::Point2D(100, 100)));
    camera.second.addObject((std::make_unique<PlayerAmmo>(renderer, player.getWeapon())));
  }
}
void GameScene::update(InputTracker& input, float dt)
{
  for (auto& player : players)
  {
    if (player.is_dead)
    {
      continue;
    }

    auto last_pos = player.AnimatedSprite::position();
    player.input(input, dt);
    /// Collisions
    std::array<ASGE::Point2D, 4> player_rect{ ASGE::Point2D(),
                                              ASGE::Point2D(player.dimensions().x, 0),
                                              ASGE::Point2D(0, player.dimensions().y),
                                              ASGE::Point2D(
                                                player.dimensions().x, player.dimensions().y) };
    for (auto& point : player_rect)
    {
      auto pos_last = ASGE::Point2D(last_pos.x + point.x, last_pos.y + point.y);
      auto pos      = ASGE::Point2D(
        player.AnimatedSprite::position().x + point.x,
        player.AnimatedSprite::position().y + point.y);
      if (tile_map.getCollisionPos(ASGE::Point2D(pos.x, pos_last.y)) > 0)
      {
        player.position(ASGE::Point2D(last_pos.x, player.AnimatedSprite::position().y));
      }
      if (tile_map.getCollisionPos(ASGE::Point2D(pos_last.x, pos.y)) > 0)
      {
        player.position(ASGE::Point2D(player.AnimatedSprite::position().x, last_pos.y));
      }
    }

    for (auto& other_player : players)
    {
      if (other_player.getID() == player.getID())
      {
        continue;
      }
      for (auto& trace_point : other_player.getWeapon().bullet.trace_points)
      {
        if (player.isInside(trace_point))
        {
          other_player.getWeapon().bullet.hit_point = trace_point;
          other_player.getWeapon().bullet.has_hit   = true;
          Logging::DEBUG(
            "Player " + std::to_string(other_player.getID() + 1) + " hit Player " +
            std::to_string(player.getID()) + " - " +
            std::to_string(other_player.getWeapon().bullet.damage) + " damage");
          player.takeDamage(other_player.getWeapon().bullet.damage);
          break;
        }
      }
    }
  }
  if (input.getKeyDown(ASGE::KEYS::KEY_ESCAPE))
  {
    setScene(Scenes::TITLE);
  }
  Scene::update(input, dt);
}
void GameScene::render(ASGE::Renderer* renderer)
{
  auto window_size = ASGE::Point2D(
    static_cast<float>(ASGE::SETTINGS.window_width),
    static_cast<float>(ASGE::SETTINGS.window_height));
  auto renderer_viewport = renderer->getViewport();
  int index              = 0;
  for (auto& camera : player_cameras)
  {
    auto player_pos = players[static_cast<size_t>(index)].centre();
    camera.first.lookAt(ASGE::Point2D(
      player_pos.x / camera.first.getZoom() + window_size.x / 4,
      player_pos.y / camera.first.getZoom() + window_size.y / 4));
    renderer->setViewport({ (index % 2) * ASGE::SETTINGS.window_width / 2,
                            (1 - index / 2) * ASGE::SETTINGS.window_height / 2,
                            static_cast<uint32_t>(ASGE::SETTINGS.window_width / 2),
                            static_cast<uint32_t>(ASGE::SETTINGS.window_height / 2) });
    renderer->setProjectionMatrix(camera.first.getView());

    Scene::render(renderer);

    tile_map.render(renderer);
    for (auto& player : players)
    {
      player.render(renderer);
    }

    renderer->setProjectionMatrix(0, 0, window_size.x / 2, window_size.y / 2);
    camera.second.render(renderer);

    index++;
  }
  renderer->setViewport(renderer_viewport);
  renderer->setProjectionMatrix(
    0,
    0,
    static_cast<float>(ASGE::SETTINGS.window_width),
    static_cast<float>(ASGE::SETTINGS.window_height));
}
