//
// Created by Work on 07/05/2021.
//

#include "ASGEGameLib/GameObjects/Player/HUD/PlayerHealth.hpp"
#include "Engine/Logger.hpp"
PlayerHealth::PlayerHealth(ASGE::Renderer* renderer, Player& _player) :
  Sprite(renderer, "data/images/player/player_health_bar.png", ASGE::Point2D(0, 0)),
  player(_player),
  background(renderer, "data/images/player/player_health_bar.png", ASGE::Point2D(0, 0))
{
}

void PlayerHealth::update(InputTracker& input, float dt)
{
  GameObject::update(input, dt);
  // position(player.AnimatedSprite::position());
  dimensions(ASGE::Point2D((player.getHealth() / player.getMaxHealth()) * 32, 5));
  position(
    ASGE::Point2D(player.AnimatedSprite::position().x, player.AnimatedSprite::position().y - 5));
  colour(ASGE::COLOURS::GREEN);
  zOrder(4);

  background.position(
    ASGE::Point2D(player.AnimatedSprite::position().x, player.AnimatedSprite::position().y - 5));
  background.dimensions(ASGE::Point2D(32, 5));
  background.colour(ASGE::COLOURS::RED);
  background.zOrder(3);
}
void PlayerHealth::render(ASGE::Renderer* renderer)
{
  if (player.getHealth() > 0 && player.getHealth() < player.getMaxHealth())
  {
    Sprite::render(renderer);
    background.render(renderer);
  }
}
