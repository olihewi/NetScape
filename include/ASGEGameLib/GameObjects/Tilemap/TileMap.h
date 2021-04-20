//
// Created by hewis on 01/04/2021.
//

#ifndef ASGEMOVIEGAME_TILEMAP_H
#define ASGEMOVIEGAME_TILEMAP_H

#include <ASGEGameLib/GameObjects/Tilemap/Tile.h>
#include <nlohmann/json.hpp>
#include <vector>
class TileMap : public GameObject
{
 public:
  TileMap(ASGE::Renderer* _renderer, std::string _tileset_path, size_t num_layers);

  /// Load from file
  TileMap(ASGE::Renderer* _renderer, const std::string& file_path);
  void loadFromJson(nlohmann::json j);
  /// Save to file
  nlohmann::json saveTileMap();

  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* _renderer) override;
  void setTile(size_t layer, size_t index, std::array<float, 4> rect);
  void deleteTile(size_t layer, size_t index);

 private:
  std::vector<std::array<Tile, 2500>> tiles;
  ASGE::Renderer* renderer;
  std::string tileset_path;
};

#endif // ASGEMOVIEGAME_TILEMAP_H
