//
// Created by hewis on 31/03/2021.
//

#include "GameObjects/Sprites/Text.h"

Text::Text(
  ASGE::Renderer* renderer, const std::string& _contents, ASGE::Point2D _position, int _font_index,
  ASGE::Colour _colour, float _scale, short _z_order)
{
  contents(_contents);
  position(_position);
  setFont(renderer, _font_index);
  colour(_colour);
  scale(_scale);
  zOrder(_z_order);
}
std::string Text::contents()
{
  return text.getString();
}
void Text::contents(std::string _contents)
{
  text.setString(_contents);
}
bool Text::visibility() const
{
  return visible;
}
void Text::visibility(bool _visibility)
{
  visible = _visibility;
}
ASGE::Point2D Text::position()
{
  return text.getPosition();
}
void Text::position(ASGE::Point2D _position)
{
  text.setPosition(_position);
}
void Text::translate(ASGE::Point2D _translation)
{
  auto pos = position();
  text.setPosition(ASGE::Point2D(pos.x + _translation.x, pos.y + _translation.y));
}
ASGE::Colour Text::colour()
{
  return text.getColour();
}
void Text::colour(ASGE::Colour _colour)
{
  text.setColour(_colour);
}
short Text::zOrder()
{
  return text.getZOrder();
}
void Text::zOrder(short _z_order)
{
  text.setZOrder(_z_order);
}
void Text::setFont(ASGE::Renderer* renderer, int _font_index)
{
  text.setFont(renderer->getFont(_font_index));
}
float Text::scale()
{
  return text.getScale();
}
void Text::scale(float _scale)
{
  text.setScale(_scale);
}
void Text::render(ASGE::Renderer* renderer)
{
  renderer->renderText(text);
}
void Text::centrePos(ASGE::Point2D _position)
{
  text.setPosition(ASGE::Point2D(_position.x - text.getWidth() / 2, _position.y));
}
