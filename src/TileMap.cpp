//
// Created by hewis on 01/04/2021.
//

#include "GameObjects/Tilemap/TileMap.h"

#include <Engine/FileIO.h>
#include <iostream>
#include <utility>
TileMap::TileMap(ASGE::Renderer* _renderer, std::string _tileset_path, size_t num_layers) :
  renderer(_renderer), tileset_path(std::move(_tileset_path))
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
void TileMap::setTile(size_t layer, size_t index, std::array<float, 4> rect)
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
nlohmann::json TileMap::saveTileMap()
{
  auto j          = nlohmann::json();
  j["tileset"]    = tileset_path;
  j["level_name"] = "untitled";
  std::vector<std::string> layer_strings;
  for (auto& layer : tiles)
  {
    std::string this_string;
    for (auto& tile : layer)
    {
      this_string += std::to_string(tile.getIndex()) + ',';
    }
    layer_strings.emplace_back(this_string);
  }
  j["tile_layers"] = layer_strings;
  return j;
}
TileMap::TileMap(ASGE::Renderer* _renderer, const std::string& file_path) : renderer(_renderer)
{
  ASGE::FILEIO::File file;
  if (file.open(file_path, ASGE::FILEIO::File::IOMode::READ))
  {
    ASGE::FILEIO::IOBuffer buffer = file.read();
    auto json_file = nlohmann::json::parse(buffer.as_char(), buffer.as_char() + buffer.length);
    file.close();
    loadFromJson(json_file);
  }
}
void TileMap::loadFromJson(nlohmann::json j)
{
  tileset_path     = j["tileset"].get<std::string>();
  auto tile_layers = j["tile_layers"].get<std::vector<std::string>>();
  int layer_index  = 0;
  tiles.clear();
  for (auto& layer : tile_layers)
  {
    auto& this_layer = tiles.emplace_back(std::array<Tile, 2500>());
    size_t index     = 0;
    std::string tile_string;
    for (auto& c : layer)
    {
      if (c >= '0' && c <= '9')
      {
        tile_string += c;
      }
      else if (c == ',')
      {
        int sprite_index = std::stoi(tile_string);
        if (sprite_index != 0)
        {
          sprite_index--;
          int vertical_index = sprite_index / 8;
          std::array<float, 4> uvs{ static_cast<float>(sprite_index % 8) * 32,
                                    static_cast<float>(vertical_index) * 32,
                                    32,
                                    32 };
          size_t vertical_pos = index / 50;
          ASGE::Point2D pos{ static_cast<float>(index % 50) * 32,
                             static_cast<float>(vertical_pos) * 32 };
          this_layer[index] = Tile(renderer, tileset_path, uvs, pos, layer_index);
        }
        index++;
        tile_string = std::string();
      }
    }
    layer_index++;
  }
}
