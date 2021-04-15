//
// Created by hewis on 31/03/2021.
//

#include "GameObjects/Sprites/Sprite.h"
Sprite::Sprite(ASGE::Renderer* renderer, const std::string& file_path, ASGE::Point2D _position)
{
  loadSprite(renderer, file_path);
  sprite->xPos(_position.x);
  sprite->yPos(_position.y);
}
bool Sprite::loadSprite(ASGE::Renderer* renderer, const std::string& file_path)
{
  if (sprite == nullptr)
  {
    sprite = renderer->createUniqueSprite();
  }
  return sprite->loadTexture(file_path);
}
void Sprite::render(ASGE::Renderer* renderer)
{
  if (visible)
  {
    renderer->renderSprite(*sprite);
  }
}
bool Sprite::visibility() const
{
  return visible;
}
void Sprite::visibility(bool _visibility)
{
  visible = _visibility;
}
ASGE::Point2D Sprite::position()
{
  return ASGE::Point2D(sprite->xPos(), sprite->yPos());
}
void Sprite::position(ASGE::Point2D _position)
{
  sprite->xPos(_position.x);
  sprite->yPos(_position.y);
}
void Sprite::translate(ASGE::Point2D _translation)
{
  sprite->xPos(sprite->xPos() + _translation.x);
  sprite->yPos(sprite->yPos() + _translation.y);
}
ASGE::Point2D Sprite::dimensions()
{
  return ASGE::Point2D(sprite->width(), sprite->height());
}
void Sprite::dimensions(ASGE::Point2D _dimensions)
{
  sprite->width(_dimensions.x);
  sprite->height(_dimensions.y);
}
float Sprite::rotation()
{
  return sprite->rotationInRadians();
}
void Sprite::rotation(float _radians)
{
  sprite->rotationInRadians(_radians);
}
void Sprite::rotate(float _radians)
{
  sprite->rotationInRadians(rotation() + _radians);
}
ASGE::Colour Sprite::colour()
{
  return sprite->colour();
}
void Sprite::colour(ASGE::Colour _colour)
{
  sprite->colour(_colour);
}
float Sprite::opacity()
{
  return sprite->opacity();
}
void Sprite::opacity(float _opacity)
{
  sprite->opacity(_opacity);
}
ASGE::Point2D Sprite::centre()
{
  return ASGE::Point2D(sprite->xPos() + sprite->width() / 2, sprite->yPos() + sprite->height() / 2);
}
bool Sprite::isInside(ASGE::Point2D _position)
{
  auto pos  = position();
  auto dims = dimensions();
  return _position.x >= pos.x && _position.x <= pos.x + dims.x && _position.y >= pos.y &&
         _position.y <= pos.y + dims.y;
}
short Sprite::zOrder()
{
  return sprite->getGlobalZOrder();
}
void Sprite::zOrder(short z_order)
{
  sprite->setGlobalZOrder(z_order);
}
void Sprite::srcRect(float x, float y, float w, float h)
{
  auto* src_rect = sprite->srcRect();
  src_rect[0]    = x;
  src_rect[1]    = y;
  src_rect[2]    = w;
  src_rect[3]    = h;
}
ASGE::Point2D Sprite::getTextureSize()
{
  auto* texture = sprite->getTexture();
  return ASGE::Point2D(texture->getWidth(), texture->getHeight());
}
void Sprite::centrePos(ASGE::Point2D position)
{
  sprite->xPos(position.x - sprite->width() / 2);
  sprite->yPos(position.y - sprite->height() / 2);
}
