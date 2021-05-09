//
// Created by hewis on 31/03/2021.
//

#include "GameObjects/UI/ScalableSprite.h"
ScalableSprite::ScalableSprite(
  ASGE::Renderer* renderer, const std::string& file_path, std::array<float, 6> part_sizes,
  ASGE::Point2D _position, ASGE::Point2D _dimensions)
{
  for (size_t x = 0; x < 3; x++)
  {
    for (size_t y = 0; y < 3; y++)
    {
      auto& spr = sprites[y * 3 + x];
      spr       = renderer->createUniqueSprite();
      spr->loadTexture(file_path);
      auto* src_rect = spr->srcRect();
      src_rect[0]    = x == 0 ? 0 : x == 1 ? part_sizes[0] : part_sizes[0] + part_sizes[2];
      src_rect[1]    = y == 0 ? 0 : y == 1 ? part_sizes[1] : part_sizes[1] + part_sizes[3];
      src_rect[2]    = part_sizes[x * 2];
      src_rect[3]    = part_sizes[y * 2 + 1];
      spr->width(part_sizes[x * 2]);
      spr->height(part_sizes[y * 2 + 1]);
    }
  }
  position(_position);
  dimensions(_dimensions);
}
void ScalableSprite::position(ASGE::Point2D _position)
{
  float offset_x = 0;
  for (size_t x = 0; x < 3; x++)
  {
    float offset_y = 0;
    for (size_t y = 0; y < 3; y++)
    {
      auto& spr = sprites[y * 3 + x];
      spr->xPos(_position.x + offset_x);
      spr->yPos(_position.y + offset_y);
      offset_y += spr->height();
    }
    offset_x += sprites[x]->width();
  }
}
void ScalableSprite::dimensions(ASGE::Point2D _dimensions)
{
  float centre_w = _dimensions.x - sprites[3]->width() - sprites[5]->width();
  float centre_h = _dimensions.y - sprites[1]->height() - sprites[6]->height();
  sprites[4]->width(centre_w);
  sprites[4]->height(centre_h);
  sprites[1]->width(centre_w);
  sprites[3]->height(centre_h);
  sprites[5]->height(centre_h);
  sprites[7]->width(centre_w);
  position(ASGE::Point2D(sprites[0]->xPos(), sprites[0]->yPos()));
}
void ScalableSprite::render(ASGE::Renderer* renderer)
{
  for (auto& sprite : sprites)
  {
    renderer->renderSprite(*sprite);
  }
}
bool ScalableSprite::isInside(ASGE::Point2D position)
{
  return (
    position.x >= sprites[0]->xPos() && position.x <= sprites[8]->xPos() + sprites[8]->width() &&
    position.y >= sprites[0]->yPos() && position.y <= sprites[8]->yPos() + sprites[8]->height());
}
ASGE::Point2D ScalableSprite::dimensions()
{
  auto dim1 = ASGE::Point2D(sprites[0]->width(), sprites[0]->height());
  auto dim2 = ASGE::Point2D(sprites[4]->width(), sprites[4]->height());
  auto dim3 = ASGE::Point2D(sprites[8]->width(), sprites[8]->height());
  return ASGE::Point2D(dim1.x + dim2.x + dim3.x, dim1.y + dim2.y + dim3.y);
}
void ScalableSprite::translate(ASGE::Point2D _translation)
{
  for (auto& sprite : sprites)
  {
    sprite->xPos(sprite->xPos() + _translation.x);
    sprite->yPos(sprite->yPos() + _translation.y);
  }
}
