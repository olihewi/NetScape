//
// Created by hewis on 01/04/2021.
//

#include "GameObjects/Tilemap/TileMap.h"
TileMap::TileMap(ASGE::Renderer* _renderer, size_t num_layers) : renderer(_renderer)
{
  for (size_t i = 0; i < num_layers; i++)
  {
    tiles.emplace_back(std::array<Tile, 2500>());
  }
}
void TileMap::update(InputTracker& input, float dt)
{
  for (auto& layer : tiles)
  {
    for (auto& tile : layer)
    {
      tile.update(input, dt);
    }
  }
}
void TileMap::render(ASGE::Renderer* _renderer)
{
  for (auto& layer : tiles)
  {
    for (auto& tile : layer)
    {
      tile.render(_renderer);
    }
  }
}
void TileMap::setTile(
  size_t layer, size_t index, const std::string& tileset_path, std::array<float, 4> rect)
{
  size_t row          = index / 50;
  tiles[layer][index] = Tile(
    renderer,
    tileset_path,
    rect,
    ASGE::Point2D(static_cast<float>(index % 50) * 32, static_cast<float>(row) * 32),
    static_cast<int>(layer));
}
void TileMap::deleteTile(size_t layer, size_t index)
{
  tiles[layer][index] = Tile();
}
