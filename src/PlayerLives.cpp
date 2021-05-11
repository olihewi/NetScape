//
// Created by Work on 10/05/2021.
//

#include "ASGEGameLib/GameObjects/Player/HUD/PlayerLives.hpp"
#include "Engine/Logger.hpp"
#include <ASGEGameLib/Utilities/FontManager.h>
PlayerLives::PlayerLives(ASGE::Renderer* renderer, Player& _player, float x, float y) :
  player(_player), lives(renderer, "data/images/ui/player_lives_icon.png"), position(x, y),
  health_bd(renderer, "data/images/ui/player_health_bar.png", position),
  health_bg(renderer, "data/images/ui/player_health_bar.png"),
  health_bar(renderer, "data/images/ui/player_health_bar.png"),
  player_name(
    renderer, "Player " + std::to_string(player.getID() + 1), position, FONTS::PIXEL,
    ASGE::COLOURS::WHITE, 0.75F)
{
  health_bd.dimensions(ASGE::Point2D(3 * player.getMaxHealth() + 4, 20));
  health_bg.dimensions(ASGE::Point2D(3 * player.getMaxHealth(), 16));
  health_bar.position(ASGE::Point2D(position.x + 2, position.y + 2));
  health_bg.position(ASGE::Point2D(position.x + 2, position.y + 2));
  health_bar.colour(ASGE::COLOURS::GREEN);
  health_bg.colour(ASGE::COLOURS::RED);

  player_name.position(ASGE::Point2D(position.x, health_bd.position().y - 4));
}
void PlayerLives::update(InputTracker& input, float dt)
{
  float lives_scale = std::fmin(
    (health_bd.dimensions().x - player_name.getWidth() - 4) /
      (lives.getTextureSize().x * static_cast<float>(player.getLives())),
    2.F);
  lives.dimensions(ASGE::Point2D(
    static_cast<float>(player.getLives()) * lives.getTextureSize().x * lives_scale,
    lives.getTextureSize().y * lives_scale));
  lives.srcRect(
    0,
    0,
    static_cast<float>(player.getLives()) * lives.getTextureSize().x,
    lives.getTextureSize().y);
  lives.position(ASGE::Point2D(
    position.x + health_bd.dimensions().x - lives.dimensions().x,
    position.y - lives.dimensions().y));

  health_bar.dimensions(ASGE::Point2D(3 * player.getHealth(), 16));
  GameObject::update(input, dt);

  playerRespawn();
}

void PlayerLives::playerRespawn()
{
  if (player.is_dead && player.getLives() > 0)
  {
    player.visibility(true);
    player.getWeapon().visibility(true);
    player.setLives(player.getLives() - 1);
    player.setHealth(player.getMaxHealth());
    player.position(player.getSpawnPoint());
    player.is_dead = false;
  }
}

void PlayerLives::render(ASGE::Renderer* renderer)
{
  if (!player.is_dead)
  {
    lives.render(renderer);
    health_bd.render(renderer);
    health_bg.render(renderer);
    health_bar.render(renderer);
    player_name.render(renderer);
  }
}
