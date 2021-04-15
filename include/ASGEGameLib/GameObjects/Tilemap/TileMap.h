//
// Created by hewis on 01/04/2021.
//

#ifndef ASGEMOVIEGAME_TILEMAP_H
#define ASGEMOVIEGAME_TILEMAP_H

#include <ASGEGameLib/GameObjects/Tilemap/Tile.h>
#include <vector>
class TileMap : public GameObject
{
 public:
  TileMap(ASGE::Renderer* _renderer, size_t num_layers);
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* _renderer) override;
  void
  setTile(size_t layer, size_t index, const std::string& tileset_path, std::array<float, 4> rect);
  void deleteTile(size_t layer, size_t index);

 private:
  std::vector<std::array<Tile, 2500>> tiles;
  ASGE::Renderer* renderer;
};

#endif // ASGEMOVIEGAME_TILEMAP_H
