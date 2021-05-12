//
// Created by hewis on 12/05/2021.
//

#include "../include/ASGEGameLib/GameObjects/Player/HUD/KillFeed.h"
#include <ASGEGameLib/Utilities/FontManager.h>

#include <utility>
KillFeed::KillFeed(ASGE::Renderer* renderer, Player& _player, ASGE::Point2D _position) :
  m_renderer(renderer), player(_player), position(std::move(_position))
{
}
void KillFeed::addMessage(Player& p1, Player& p2)
{
  auto pos = ASGE::Point2D(position.x, position.y + (static_cast<float>(messages.size()) + 1) * 24);
  auto colour =
    (p1.getID() == player.getID()
       ? ASGE::COLOURS::YELLOW
       : (p2.getID() == player.getID() ? ASGE::COLOURS::RED : ASGE::COLOURS::WHITE));
  messages.emplace_back(KillFeedElement(m_renderer, p1, p2, pos, colour));
}
void KillFeed::update(InputTracker& input, float dt)
{
  std::vector<int> messages_to_remove;
  int index = 0;
  for (auto& message : messages)
  {
    message.update(input, dt);
    if (message.timer < 0)
    {
      messages_to_remove.emplace_back(index);
    }
    index++;
  }
  index = 0;
  if (!messages_to_remove.empty())
  {
    messages.erase(messages.begin() + messages_to_remove[0]);
    index = 1;
  }
  for (auto& message : messages)
  {
    message.translate(ASGE::Point2D(0, static_cast<float>(-index) * 24));
  }
}
void KillFeed::render(ASGE::Renderer* renderer)
{
  for (auto& message : messages)
  {
    message.render(renderer);
  }
}
void KillFeed::addMessage(const std::string& message)
{
  auto pos = ASGE::Point2D(position.x, position.y + (static_cast<float>(messages.size()) + 1) * 24);
  messages.emplace_back(KillFeedElement(m_renderer, message, pos));
}

KillFeedElement::KillFeedElement(
  ASGE::Renderer* renderer, Player& p1, Player& p2, ASGE::Point2D _position, ASGE::Colour _colour) :
  name1(renderer, "P" + std::to_string(p1.getID() + 1), _position, FONTS::PIXEL, _colour, 0.6F),
  name2(renderer, "P" + std::to_string(p2.getID() + 1), _position, FONTS::PIXEL, _colour, 0.6F),
  weapon(renderer, p1.getWeapon().getWeaponData().sprite_floor, _position)
{
  weapon.srcRect(0, 0, weapon.getTextureSize().x / 2, weapon.getTextureSize().y);
  weapon.dimensions(ASGE::Point2D(weapon.getTextureSize().x / 2, weapon.getTextureSize().y));
  name2.position(ASGE::Point2D(_position.x - name2.getWidth() - 8, _position.y));
  weapon.position(ASGE::Point2D(
    name2.position().x - weapon.dimensions().x - 8, _position.y - weapon.dimensions().y));
  name1.position(ASGE::Point2D(weapon.position().x - name1.getWidth() - 8, _position.y));
}
void KillFeedElement::update(InputTracker& /*input*/, float dt)
{
  timer -= dt;
}
void KillFeedElement::render(ASGE::Renderer* renderer)
{
  name1.render(renderer);
  name2.render(renderer);
  weapon.render(renderer);
}
KillFeedElement::KillFeedElement(
  ASGE::Renderer* renderer, const std::string& message, ASGE::Point2D _position) :
  name1(renderer, message, _position, FONTS::PIXEL, ASGE::COLOURS::WHITE, 0.6F),
  name2(renderer, ""), weapon(renderer, "data/images/weapons/pistol.png")
{
  name1.position(ASGE::Point2D(_position.x - name1.getWidth(), _position.y));
  weapon.visibility(false);
}
void KillFeedElement::translate(ASGE::Point2D _translation)
{
  name1.translate(_translation);
  name2.translate(_translation);
  weapon.translate(_translation);
}
