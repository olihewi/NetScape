//
// Created by hewis on 11/04/2021.
//

#include "ASGEGameLib/Scenes/GameScene.h"
#include "Engine/Logger.hpp"
#include <ASGEGameLib/GameObjects/Player/HUD/Crosshair.h>
#include <ASGEGameLib/GameObjects/Player/HUD/PlayerAmmo.hpp>
#include <ASGEGameLib/GameObjects/Player/HUD/PlayerHealth.hpp>
#include <GameObjects/Player/HUD/PlayerLives.hpp>
#include <array>
#include <utility>

GameScene::GameScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)), m_renderer(renderer),
  tile_map(renderer, "levels/dotonbori.json"),
  players(std::array<Player, 4>{ Player(renderer, ASGE::Point2D(), 0, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(), 1, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(), 2, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(), 3, audio_engine.get()) }),
  window_divider(renderer, "images/ui/ingame_windowdivider.png")
{
  auto window = ASGE::Point2D(
    static_cast<float>(ASGE::SETTINGS.window_width),
    static_cast<float>(ASGE::SETTINGS.window_height));
  for (auto& player : players)
  {
    player.position(tile_map.getSpawn(player.getID()));
    player.setSpawnPoint(tile_map.getSpawn(player.getID()));
    addObject(std::make_unique<PlayerHealth>(renderer, player));
    auto& camera = player_cameras.emplace_back(
      std::make_pair(ASGE::Camera(1920.F / 2, 1080.F / 2), PlayerHUD(player)));
    camera.first.setZoom(0.5F);
    camera.second.addObject(std::make_unique<Text>(
      renderer, "Player " + std::to_string(player.getID()), ASGE::Point2D(100, 100)));
    camera.second.addObject((std::make_unique<PlayerAmmo>(
      renderer, player.getWeapon(), player, 1920 / 2 - 128, 1080 / 2 - 64)));
    camera.second.addObject(
      (std::make_unique<PlayerLives>(renderer, player, 1920 / 2 - 128, 1080 / 2 - 96)));
    camera.second.addObject(std::make_unique<Crosshair>(renderer, player.getID()));
  }
  window_divider.dimensions(window);
}

void GameScene::update(InputTracker& input, float dt)
{
  Scene::update(input, dt);
  tile_map.update(input, dt);

  playerMovement(input, dt);
  checkBullets();
  updateDrops(input);

  size_t index = 0;
  for (auto& camera : player_cameras)
  {
    camera.second.update(input, dt);
    auto player_pos  = players[index].centre();
    auto right_stick = input.getControllerStick(index, CONTROLLER::STICKS::RIGHT);
    player_pos       = ASGE::Point2D(
      player_pos.x + right_stick.x * camera.second.getFocus() * 64,
      player_pos.y + right_stick.y * camera.second.getFocus() * 64);
    player_pos = ASGE::Point2D(
      player_pos.x + camera.second.getCameraShake().x,
      player_pos.y + camera.second.getCameraShake().y);
    camera.first.lookAt(ASGE::Point2D(
      player_pos.x / camera.first.getZoom() + 1920.F / 4,
      player_pos.y / camera.first.getZoom() + 1080.F / 4));
    index++;
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
    auto camera_view = camera.first.getView();
    renderer->setViewport({ (index % 2) * ASGE::SETTINGS.window_width / 2,
                            (1 - index / 2) * ASGE::SETTINGS.window_height / 2,
                            static_cast<uint32_t>(ASGE::SETTINGS.window_width / 2),
                            static_cast<uint32_t>(ASGE::SETTINGS.window_height / 2) });
    renderer->setProjectionMatrix(camera_view);

    Scene::render(renderer);

    tile_map.renderSection(
      ASGE::Point2D(camera_view.min_x, camera_view.min_y),
      ASGE::Point2D(camera_view.max_x, camera_view.max_y));
    for (auto& player : players)
    {
      player.render(renderer);
    }

    renderer->setProjectionMatrix(0, 0, 1920.F / 2, 1080.F / 2);
    camera.second.render(renderer);

    index++;
  }
  renderer->setViewport(renderer_viewport);
  renderer->setProjectionMatrix(
    0,
    0,
    static_cast<float>(ASGE::SETTINGS.window_width),
    static_cast<float>(ASGE::SETTINGS.window_height));
  window_divider.render(renderer);
}
void GameScene::playerMovement(InputTracker& input, float dt)
{
  for (auto& player : players)
  {
    if (player.is_dead)
    {
      continue;
    }
    ASGE::Point2D last_pos = playerVsTiles(input, dt, player);
    for (auto& other_player : players)
    {
      if (other_player.getID() == player.getID() || other_player.is_dead)
      {
        continue;
      }
      auto dist_1 = ASGE::Point2D(
        player.centre().x - other_player.centre().x, player.centre().y - other_player.centre().y);
      if (std::hypot(dist_1.x, dist_1.y) < 24)
      {
        auto push_dist =
          ASGE::Point2D((last_pos.x - player.centre().x) / 2, (last_pos.y - player.centre().y) / 2);
        player.translate(push_dist);
      }
    }
  }
}
ASGE::Point2D GameScene::playerVsTiles(InputTracker& input, float dt, Player& player)
{
  auto last_pos = player.centre();
  player.input(input, dt);
  player.update(input, dt);
  std::vector<ASGE::Point2D> collision_tiles;
  for (int x = -32; x <= 32; x++)
  {
    for (int y = -32; y <= 32; y++)
    {
      ASGE::Point2D this_pos = ASGE::Point2D(
        player.centre().x + static_cast<float>(x), player.centre().y + static_cast<float>(y));
      if (tile_map.getCollisionPos(this_pos) > 0)
      {
        collision_tiles.emplace_back(
          ASGE::Point2D(floor(this_pos.x / 32) * 32, floor(this_pos.y / 32) * 32));
      }
    }
  }
  for (auto& tile : collision_tiles)
  {
    if (playerCollidesWithTile(ASGE::Point2D(player.centre().x, last_pos.y), tile))
    {
      player.position(ASGE::Point2D(
        last_pos.x - player.dimensions().x / 2, player.centre().y - player.dimensions().y / 2));
    }
    if (playerCollidesWithTile(ASGE::Point2D(last_pos.x, player.centre().y), tile))
    {
      player.position(ASGE::Point2D(
        player.centre().x - player.dimensions().x / 2, last_pos.y - player.dimensions().y / 2));
    }
  }
  return last_pos;
}
void GameScene::checkBullets()
{
  for (auto& player : players)
  {
    if (player.is_dead)
    {
      continue;
    }
    for (auto& other_player : players)
    {
      if (other_player.getID() == player.getID())
      {
        continue;
      }
      size_t index = 0;
      for (auto& trace_point : player.getWeapon().bullet.trace_points)
      {
        if (!player.getWeapon().bullet.has_hit)
        {
          index++;
          if (other_player.isInside(trace_point))
          {
            player.getWeapon().bullet.hit_point = index;
            player.getWeapon().bullet.has_hit   = true;
            Logging::DEBUG(
              "Player " + std::to_string(player.getID() + 1) + " hit Player " +
              std::to_string(other_player.getID()) + " - " +
              std::to_string(player.getWeapon().bullet.damage) + " damage");
            other_player.takeDamage(player.getWeapon().bullet.damage);
            break;
          }

          if (tile_map.getCollisionPos(trace_point))
          {
            other_player.getWeapon().bullet.hit_point = index;
            other_player.getWeapon().bullet.has_hit   = true;
            break;
          }
        }
      }
    }
  }
}
bool GameScene::playerCollidesWithTile(ASGE::Point2D player, ASGE::Point2D tile)
{
  float p_radius     = 12;
  ASGE::Point2D temp = player;
  /// Which edge is closest?
  if (player.x < tile.x)
  {
    temp.x = tile.x;
  }
  else if (player.x > tile.x + 32)
  {
    temp.x = tile.x + 32;
  }
  if (player.y < tile.y)
  {
    temp.y = tile.y;
  }
  else if (player.y > tile.y + 32)
  {
    temp.y = tile.y + 32;
  }
  /// Get distance from closest edges
  ASGE::Point2D dist = ASGE::Point2D(player.x - temp.x, player.y - temp.y);
  float mag          = std::hypot(dist.x, dist.y);
  /// If the distance is less than the radius, collision!
  return mag <= p_radius;
}
void GameScene::updateDrops(InputTracker& input)
{
  for (auto& drop : tile_map.getDrops())
  {
    if (!drop.visibility())
    {
      continue;
    }
    drop.playerInRange(false);
    for (auto& player : players)
    {
      if (std::hypot(player.centre().x - drop.centre().x, player.centre().y - drop.centre().y) < 48)
      {
        drop.playerInRange(true);
        if (input.getControllerButtonDown(player.getID(), CONTROLLER::BUTTONS::Y))
        {
          player.getWeapon().setWeapon(m_renderer, drop.getWeapon());
          drop.visibility(false);
        }
      }
    }
  }
}
