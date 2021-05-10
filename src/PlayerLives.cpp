//
// Created by Work on 10/05/2021.
//

#include "ASGEGameLib/GameObjects/Player/HUD/PlayerLives.hpp"
#include "Engine/Logger.hpp"
PlayerLives::PlayerLives(ASGE::Renderer* renderer, Player& _player, float x, float y) :
  player(_player),
  lives(std::array<Sprite, 10>{
    Sprite(renderer, "data/images/ui/player_lives_icon.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/ui/player_lives_icon.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/ui/player_lives_icon.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/ui/player_lives_icon.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/ui/player_lives_icon.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/ui/player_lives_icon.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/ui/player_lives_icon.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/ui/player_lives_icon.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/ui/player_lives_icon.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/ui/player_lives_icon.png", ASGE::Point2D(0, 0)) }),
  posX(x), posY(y),
  LivesReserveDisplay(renderer, std::to_string(player.getLives()), ASGE::Point2D(0, 0)),
  LivesReserveDisplayX(renderer, "x", ASGE::Point2D(0, 0))
{
  posX -= lives[0].dimensions().x * (static_cast<float>(player.getMaxLives()) / 2);
  for (size_t i = 0; i < static_cast<size_t>(player.getMaxLives()); ++i)
  {
    lives[i].position(
      ASGE::Point2D((posX + static_cast<float>(i) * lives[i].dimensions().x), posY));
  }
  LivesReserveDisplayX.position(
    ASGE::Point2D(lives[0].position().x - 15, lives[0].position().y + lives[0].dimensions().y));
}
void PlayerLives::update(InputTracker& input, float dt)
{
  LivesReserveDisplay.position(ASGE::Point2D(
    LivesReserveDisplayX.position().x - LivesReserveDisplay.getWidth() - 5,
    lives[0].position().y + lives[0].dimensions().y));

  GameObject::update(input, dt);
  LivesReserveDisplay.contents(std::to_string(player.getLives()));

  playerRespawn();
}

void PlayerLives::playerRespawn()
{
  if (player.is_dead && player.getLives() > 0)
  {
    Logging::DEBUG("isdead: " + std::to_string(player.is_dead));
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
    for (size_t i = 0; i < static_cast<size_t>(player.getLives()); ++i)
    {
      lives[i].Sprite::render(renderer);
    }
    LivesReserveDisplayX.render(renderer);
    LivesReserveDisplay.render(renderer);
  }
}
