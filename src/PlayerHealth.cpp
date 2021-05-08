//
// Created by Work on 07/05/2021.
//

#include "ASGEGameLib/GameObjects/Player/HUD/PlayerHealth.hpp"

PlayerHealth::PlayerHealth(ASGE::Renderer* renderer, Player& _player):
    Sprite(renderer, "data/images/player/player_health_bar.png", ASGE::Point2D(0,0)),
    player(_player)
{

}

void PlayerHealth::update(InputTracker& input, float dt)
{
  GameObject::update(input, dt);
  position(player.AnimatedSprite::position());


}
