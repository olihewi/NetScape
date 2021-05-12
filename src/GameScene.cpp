//
// Created by hewis on 11/04/2021.
//

#include "ASGEGameLib/Scenes/GameScene.h"
#include "Engine/Logger.hpp"
#include <ASGEGameLib/GameObjects/Player/HUD/Crosshair.h>
#include <ASGEGameLib/GameObjects/Player/HUD/PlayerAmmo.hpp>
#include <ASGEGameLib/GameObjects/Player/HUD/PlayerHealth.hpp>
#include <ASGEGameLib/Utilities/FontManager.h>
#include <GameObjects/Player/HUD/PlayerAbilities.hpp>
#include <GameObjects/Player/HUD/PlayerLives.hpp>
#include <GameObjects/Player/HUD/PlayerScore.hpp>
#include <array>
#include <utility>

GameScene::GameScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)), m_renderer(renderer),
  tile_map(renderer, "levels/dotonbori.json"),
  players(std::array<Player, 4>{ Player(renderer, ASGE::Point2D(), 0, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(), 1, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(), 2, audio_engine.get()),
                                 Player(renderer, ASGE::Point2D(), 3, audio_engine.get()) }),
  window_divider(renderer, "images/ui/ingame_windowdivider.png"),
  round_time_text(renderer, "", ASGE::Point2D(), FONTS::PIXEL)
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
    camera.second.addObject((std::make_unique<PlayerAmmo>(
      renderer, player.getWeapon(), player, 1920 / 2 - 40, 1080 / 2 - 40)));
    camera.second.addObject((std::make_unique<PlayerLives>(renderer, player, 40, 1080 / 2 - 40)));
    camera.second.addObject(std::make_unique<PlayerScore>(renderer,player, 1920.F / 4,1080.F / 4));
    camera.second.addObject(std::make_unique<Crosshair>(renderer, player.getID()));
    camera.second.addObject(std::make_unique<PlayerAbilities>(renderer, player, 1920 / 2 - 450, 1080 / 2 - 50));
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
    camera.first.lookAt(ASGE::Point2D(player_pos.x, player_pos.y));
    float right_mag = std::fmin(std::hypotf(right_stick.x, right_stick.y), 1.F);
    camera.first.setZoom(0.5F + (0.05F * right_mag * camera.second.getFocus()));
    index++;
  }
  round_timer -= dt;
  round_time_text.contents(std::to_string(static_cast<int>(round_timer)));
  round_time_text.centrePos(ASGE::Point2D(static_cast<float>(ASGE::SETTINGS.window_width) / 2, 64));

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
                            ASGE::SETTINGS.window_width / 2,
                            ASGE::SETTINGS.window_height / 2 });
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
  round_time_text.render(renderer);
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
    if (player.getWeapon().hasFired())
    {
      if (player.is_dead)
      {
        continue;
      }
      for (int i = 0; i < player.getWeapon().getWeaponData().num_bullets; i++)
      {
        ASGE::Point2D origin = player.centre();
        ASGE::Point2D dir    = ASGE::Point2D(
          std::cos(player.getWeapon().rotation()), std::sin(player.getWeapon().rotation()));
        origin            = ASGE::Point2D(origin.x + dir.x * 12, origin.y + dir.y * 12);
        float dist        = player.getWeapon().getWeaponData().range;
        ASGE::Point2D end = dir * dist;
        end               = ASGE::Point2D(end.x + origin.x, end.y + origin.y);
        end               = bulletVsTiles(origin, end);

        int closest_player_index = -1;
        float closest_dist       = 9999;
        for (auto& other_player : players)
        {
          if (other_player.getID() == player.getID() || other_player.is_dead)
          {
            continue;
          }
          float hit_dist = bulletVsPlayer(origin, end, other_player);
          if (hit_dist >= 0 && hit_dist < closest_dist)
          {
            closest_player_index = static_cast<int>(other_player.getID());
            closest_dist         = hit_dist;
            dist                 = hit_dist;
          }
        }
        if (closest_player_index != -1) /// Hit
        {
          auto& hit_player = players[static_cast<size_t>(closest_player_index)];
          end              = dir * dist;
          end              = ASGE::Point2D(end.x + origin.x, end.y + origin.y);

          player.getScore().hit++;
          auto& this_weapon = player.getWeapon().getWeaponData();
          float damage      = this_weapon.damage;
          damage *= 1 - dist / this_weapon.range * this_weapon.range_falloff;
          hit_player.takeDamage(damage);
          if (hit_player.is_dead)
          {
            hit_player.getScore().nemesis_points[player.getID()] += 1;
            player.getScore().kills++;
          }
        }
        else /// Miss
        {
          player.getScore().miss++;
        }

        player.getWeapon().trace(origin, end, static_cast<size_t>(i));
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
  auto& drops = tile_map.getDrops();
  for (auto& drop : drops)
  {
    drop.playerInRange(false);
  }
  for (auto& player : players)
  {
    int closest        = -1;
    float closest_dist = 9999;
    int index          = 0;
    for (auto& drop : drops)
    {
      if (drop.visibility())
      {
        float this_dist =
          std::hypot(player.centre().x - drop.centre().x, player.centre().y - drop.centre().y);
        if (this_dist < 24 && this_dist < closest_dist)
        {
          closest_dist = this_dist;
          closest      = index;
        }
      }
      index++;
    }
    if (closest != -1)
    {
      auto& drop = drops[static_cast<size_t>(closest)];
      drop.playerInRange(true);
      if (input.getControllerButtonDown(player.getID(), CONTROLLER::BUTTONS::Y))
      {
        player.getWeapon().setWeapon(m_renderer, drop.getWeapon());
        drop.setRespawnTimer();
      }
    }
  }
}
ASGE::Point2D GameScene::bulletVsTiles(ASGE::Point2D origin, ASGE::Point2D end)
{
  int x0    = static_cast<int>(origin.x) / 32;
  int y0    = static_cast<int>(origin.y) / 32;
  int x1    = static_cast<int>(end.x) / 32;
  int y1    = static_cast<int>(end.y) / 32;
  int dx    = std::abs(x1 - x0);
  int dy    = std::abs(y1 - y0);
  int x     = x0;
  int y     = y0;
  int x_inc = (x1 > x0) ? 1 : -1;
  int y_inc = (y1 > y0) ? 1 : -1;
  int error = dx - dy;
  dx *= 2;
  dy *= 2;

  for (int n = 1 + dx + dy; n > 0; --n)
  {
    auto grid_pos = static_cast<size_t>(x) + static_cast<size_t>(y) * 50;
    if (tile_map.getCollision(grid_pos) > 0)
    {
      ASGE::Point2D tile_pos =
        ASGE::Point2D(static_cast<float>(x) * 32, static_cast<float>(y) * 32);
      std::array<ASGE::Point2D, 4> intersections{
        lineIntersect(origin, end, tile_pos, ASGE::Point2D(tile_pos.x + 32, tile_pos.y)), // top
        lineIntersect(origin, end, tile_pos, ASGE::Point2D(tile_pos.x, tile_pos.y)),      // left
        lineIntersect(
          origin,
          end,
          ASGE::Point2D(tile_pos.x, tile_pos.y + 32),
          ASGE::Point2D(tile_pos.x + 32, tile_pos.y + 32)), // bottom
        lineIntersect(
          origin,
          end,
          ASGE::Point2D(tile_pos.x + 32, tile_pos.y),
          ASGE::Point2D(tile_pos.x + 32, tile_pos.y + 32)) // right
      };
      ASGE::Point2D closest_intersect = ASGE::Point2D(tile_pos.x + 16, tile_pos.y + 16);
      float closest_distance          = 9999;
      for (auto& intersection : intersections)
      {
        float this_distance = origin.distance(intersection);
        if (this_distance < closest_distance && intersection.x >= 0.1F && intersection.y >= 0.1F)
        {
          closest_intersect = intersection;
          closest_distance  = this_distance;
        }
      }
      return closest_intersect;
    }

    if (error > 0)
    {
      x += x_inc;
      error -= dy;
    }
    else
    {
      y += y_inc;
      error += dx;
    }
  }
  return end;
}
float GameScene::bulletVsPlayer(ASGE::Point2D origin, ASGE::Point2D end, Player& player)
{
  /// Check ends
  if (player.circleCollision(origin) || player.circleCollision(end))
  {
    return -1;
  }
  /// Get point along line
  ASGE::Point2D p    = player.centre();
  ASGE::Point2D dist = ASGE::Point2D(end.x - origin.x, end.y - origin.y);
  float mag          = std::hypot(dist.x, dist.y);
  float dot = (((p.x - origin.x) * (end.x - origin.x)) + ((p.y - origin.y) * (end.y - origin.y))) /
              std::powf(mag, 2);
  ASGE::Point2D closest =
    ASGE::Point2D(origin.x + (dot * (end.x - origin.x)), origin.y + (dot * (end.y - origin.y)));
  /// If point is on segment
  /// 1 2 closest
  float dist_1    = closest.distance(origin);
  float dist_2    = closest.distance(end);
  float buffer    = 0.1F; /// floating point inaccuracy
  bool on_segment = (dist_1 + dist_2 >= mag - buffer && dist_1 + dist_2 <= mag + buffer);
  if (!on_segment)
  {
    return -1;
  }
  dist = ASGE::Point2D(closest.x - p.x, closest.y - p.y);
  mag  = std::hypot(dist.x, dist.y);
  return (mag < 16 ? closest.distance(origin) : -1);
}
ASGE::Point2D GameScene::lineIntersect(
  ASGE::Point2D origin1, ASGE::Point2D end1, ASGE::Point2D origin2, ASGE::Point2D end2)
{
  float u_a =
    ((end2.x - origin2.x) * (origin1.y - origin2.y) -
     (end2.y - origin2.y) * (origin1.x - origin2.x)) /
    ((end2.y - origin2.y) * (end1.x - origin1.x) - (end2.x - origin2.x) * (end1.y - origin1.y));
  float u_b =
    ((end1.x - origin1.x) * (origin1.y - origin2.y) -
     (end1.y - origin1.y) * (origin1.x - origin2.x)) /
    ((end2.y - origin2.y) * (end1.x - origin1.x) - (end2.x - origin2.x) * (end1.y - origin1.y));
  if (u_a >= 0 && u_a <= 1 && u_b >= 0 && u_b <= 1)
  {
    ASGE::Point2D intersection = ASGE::Point2D(
      origin1.x + (u_a * (end1.x - origin1.x)), origin1.y + (u_a * (end1.y - origin1.y)));
    return intersection;
  }
  return ASGE::Point2D();
}
