//
// Created by Work on 08/05/2021.
//

#include "ASGEGameLib/GameObjects/Player/HUD/PlayerAmmo.hpp"
#include <Engine/Logger.hpp>
#include <cmath>
PlayerAmmo::PlayerAmmo(
  ASGE::Renderer* renderer, Weapon& _weapon, Player& _player, float x, float y) :
  weapon(_weapon),
  player(_player), m_renderer(renderer), position(ASGE::Point2D(x, y)),
  AmmoReserveDisplay(renderer, ""), weapon_name(renderer, ""),
  weapon_sprite(renderer, "data/images/weapons/pistol.png")
{
}

void PlayerAmmo::update(InputTracker& input, float dt)
{
  if (weapon.getWeaponData().weapon_name != last_weapon)
  {
    last_weapon = weapon.getWeaponData().weapon_name;
    counters.clear();
    for (int i = 0; i <= (weapon.getWeaponData().max_ammo - 1) / 10; i++)
    {
      counters.emplace_back(Sprite(
        m_renderer,
        weapon.getWeaponData().sprite_ammo,
        ASGE::Point2D(position.x, position.y - 16.F * static_cast<float>(i))));
    }
    weapon_name.contents(weapon.getWeaponData().weapon_name);
    weapon_name.position(ASGE::Point2D(position.x, counters.back().position().y - 4));
    weapon_sprite.loadSprite(m_renderer, weapon.getWeaponData().sprite_floor);
    weapon_sprite.dimensions(
      ASGE::Point2D(weapon_sprite.getTextureSize().x, weapon_sprite.getTextureSize().y * 2));
    weapon_sprite.srcRect(
      0.1F,
      0.1F,
      weapon_sprite.getTextureSize().x / 2.F - 0.2F,
      weapon_sprite.getTextureSize().y - 0.2F);
    weapon_sprite.position(ASGE::Point2D(
      position.x + 16 * 10 - weapon_sprite.dimensions().x,
      counters.back().position().y - weapon_sprite.dimensions().y - 8));
    weapon_sprite.setFlipFlags(ASGE::Sprite::FLIP_X);
  }
  int i = 0;
  for (auto& counter : counters)
  {
    float this_width =
      std::fmax(std::fmin(static_cast<float>(weapon.getCurrentAmmo() - i * 10), 10.F), 0.F) *
      counter.getTextureSize().x;
    counter.dimensions(ASGE::Point2D(this_width, counter.dimensions().y));
    counter.srcRect(0, 0, this_width, counter.getTextureSize().y);
    i++;
  }
  AmmoReserveDisplay.contents(std::to_string(weapon.getAmmoReserves()) + "x ");
  AmmoReserveDisplay.position(ASGE::Point2D(
    position.x - AmmoReserveDisplay.getWidth(),
    counters.front().position().y + counters.front().dimensions().y));

  GameObject::update(input, dt);
}

void PlayerAmmo::render(ASGE::Renderer* renderer)
{
  if (!player.is_dead)
  {
    for (auto& counter : counters)
    {
      counter.render(renderer);
    }
    AmmoReserveDisplay.render(renderer);
    weapon_name.render(renderer);
    weapon_sprite.render(renderer);
  }
}
