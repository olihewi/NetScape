//
// Created by hewis on 01/04/2021.
//

#include "GameObjects/Tilemap/Tile.h"
Tile::Tile(
  ASGE::Renderer* renderer, const std::string& tileset_path, std::array<float, 4> rect,
  ASGE::Point2D position, int collision_layer) :
  sprite(std::make_unique<Sprite>(renderer, tileset_path, position)),
  collision(collision_layer)
{
  sprite->dimensions(ASGE::Point2D(rect[2], rect[3]));
  sprite->srcRect(rect[0], rect[1], rect[2], rect[3]);
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
int Tile::collisionLayer() const
{
  return collision;
}
