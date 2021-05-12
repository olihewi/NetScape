//
// Created by Bread on 12/05/2021.
//

#include "ASGEGameLib/GameObjects/Player/HUD/PlayerAbilities.hpp"
PlayerAbilities::PlayerAbilities(ASGE::Renderer* renderer, Player& _player, float x, float y) :
  player(_player), position(ASGE::Point2D(x, y)),
  ability_icons(std::array<Sprite, 3>{Sprite(renderer, "data/images/ui/sprint.png", 0),
                                      Sprite(renderer, "data/images/ui/invisible_icon.png", 0),
                                      Sprite(renderer, "data/images/ui/healing.png", 0)}),
  button_icons(std::array<Sprite, 3>{Sprite(renderer, "data/images/ui/controller/buttons.png", 0),
                                    Sprite(renderer, "data/images/ui/controller/buttons.png", 0),
                                    Sprite(renderer, "data/images/ui/controller/buttons.png", 0)})
{
  button_icons[0].srcRect(64, 0, 64, 64); /// B
  button_icons[1].srcRect(120, 210, 40, 47);
  button_icons[2].srcRect(161, 210, 40, 47);

  for (size_t i = 0; i < 3; i++)
  {
    ability_icons[i].dimensions(ASGE::Point2D(30, 30));
    ability_icons[i].position(ASGE::Point2D(position.x + (static_cast<float>(30 * i)), position.y));
  }
  for (size_t i = 0; i < 3; i++)
  {
    button_icons[i].dimensions(ASGE::Point2D(30, 30));
    button_icons[i].position(ASGE::Point2D(position.x + (static_cast<float>(30 * i)), position.y - 40));
  }
}

void PlayerAbilities::update(InputTracker& input, float dt)
{
  GameObject().update(input, dt);


  if(player.dashing)
  {
    ability_icons[0].colour(ASGE::COLOURS::GREEN);
  }
  else
  {
    ability_icons[0].colour(ASGE::COLOURS::WHITE);
  }
  ability_icons[0].opacity(1 -player.dash_cooldown / 10);


  if (player.is_invis)
  {
    ability_icons[1].colour(ASGE::COLOURS::GREEN);
  }
  else
  {
    ability_icons[1].colour(ASGE::COLOURS::WHITE);
  }
  ability_icons[1].opacity(1 -player.invis_cooldown / 15);


  if(player.healing)
  {
    ability_icons[2].colour(ASGE::COLOURS::GREEN);
  }
  else
  {
    ability_icons[2].colour(ASGE::COLOURS::WHITE);
  }
  ability_icons[2].opacity(1 - player.heal_cooldown / 15);

}

void PlayerAbilities::render(ASGE::Renderer* renderer)
{
  if (!player.is_dead)
  {
    for (auto& ability_icon : ability_icons)
    {
      ability_icon.render(renderer);
    }
    for (auto& button_icon : button_icons)
    {
      button_icon.render(renderer);
    }

  }
}
