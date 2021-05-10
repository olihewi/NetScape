//
// Created by hewis on 01/04/2021.
//

#include "GameObjects/Tilemap/Tile.h"
#include "GameObjects/Sprites/AnimatedSprite.h"
Tile::Tile(
  ASGE::Renderer* renderer, const std::string& tileset_path, std::array<float, 4> rect,
  ASGE::Point2D position, int layer) :
  sprite(std::make_unique<Sprite>(renderer, tileset_path, position))
{
  sprite->dimensions(ASGE::Point2D(rect[2], rect[3]));
  sprite->srcRect(rect[0], rect[1], rect[2], rect[3]);
  sprite->zOrder(static_cast<short>(layer));
}
void Tile::update(InputTracker& input, float dt)
{
  if (sprite == nullptr)
  {
    return;
  }
  sprite->update(input, dt);
}
void Tile::render(ASGE::Renderer* renderer)
{
  if (sprite == nullptr)
  {
    return;
  }
  sprite->render(renderer);
}
int Tile::getIndex()
{
  if (sprite == nullptr)
  {
    return 0;
  }
  auto src_rect = sprite->srcRect();
  int x_index   = static_cast<int>(src_rect[0]) / 32;
  int y_index   = static_cast<int>(src_rect[1] / 32);
  return x_index + y_index * 8 + 1;
}
Tile::Tile(
  ASGE::Renderer* renderer, const std::string& animation_path, float animation_speed,
  ASGE::Point2D position, int layer) :
  sprite(std::make_unique<AnimatedSprite>(renderer, animation_path, animation_speed, position))
{
  sprite->dimensions(ASGE::Point2D(32, 32));
  sprite->zOrder(static_cast<short>(layer));
}
