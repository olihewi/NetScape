//
// Created by hewis on 01/04/2021.
//

#include "GameObjects/Tilemap/TileMap.h"

#include <Engine/FileIO.hpp>
#include <utility>
TileMap::TileMap(ASGE::Renderer* _renderer, std::string _tileset_path, size_t num_layers) :
  collisions(), renderer(_renderer), tileset_path(std::move(_tileset_path))
{
  for (size_t i = 0; i < num_layers; i++)
  {
    tiles.emplace_back(std::array<Tile, 2500>());
  }
  spawn_points.emplace_back(ASGE::Point2D(100, 100));
  spawn_points.emplace_back(ASGE::Point2D(200, 200));
  spawn_points.emplace_back(ASGE::Point2D(300, 300));
  spawn_points.emplace_back(ASGE::Point2D(400, 400));
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
  for (auto& animation : animations)
  {
    animation.update(input, dt);
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
  for (auto& animation : animations)
  {
    animation.render(renderer);
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
      auto tile_index = tile.getIndex();
      this_string += std::to_string(tile_index) + ',';
    }
    layer_strings.emplace_back(this_string);
  }
  j["tile_layers"] = layer_strings;
  std::string collision_string;
  for (auto& collision : collisions)
  {
    collision_string += std::to_string(collision) + ',';
  }
  j["collisions"]  = collision_string;
  auto spawn_pairs = std::vector<std::pair<float, float>>();
  for (auto& spawn_point : spawn_points)
  {
    spawn_pairs.emplace_back(std::make_pair(spawn_point.x, spawn_point.y));
  }
  j["spawn_points"] = spawn_pairs;
  std::vector<nlohmann::json> j_animations;
  for (auto& animation : animations)
  {
    nlohmann::json this_json;
    this_json["path"]     = animation.getFilePath();
    this_json["position"] = std::make_pair(animation.position().x, animation.position().y);
    this_json["layer"]    = animation.zOrder();
    this_json["speed"]    = animation.getPlaybackSpeed();
    j_animations.emplace_back(this_json);
  }
  j["animations"] = j_animations;
  return j;
}
TileMap::TileMap(ASGE::Renderer* _renderer, const std::string& file_path) :
  collisions(), renderer(_renderer)
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
  collisions              = std::array<int, 2500>();
  tileset_path            = j["tileset"].get<std::string>();
  auto spawn_points_pairs = j["spawn_points"].get<std::vector<std::pair<float, float>>>();
  for (auto& spawn_point : spawn_points_pairs)
  {
    spawn_points.emplace_back(ASGE::Point2D(spawn_point.first, spawn_point.second));
  }

  auto tile_layers = j["tile_layers"].get<std::vector<std::string>>();

  int layer_index = 0;
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
  auto j_collisions = j["collisions"].get<std::string>();
  size_t index      = 0;
  std::string coll_string;
  for (auto& c : j_collisions)
  {
    if (c >= '0' && c <= '9')
    {
      coll_string += c;
    }
    else if (c == ',')
    {
      collisions[index] = std::stoi(coll_string);
      coll_string       = std::string();
      index++;
    }
  }
  for (auto& animation : j["animations"])
  {
    auto layer         = animation["layer"].get<int>();
    auto path          = animation["path"].get<std::string>();
    auto position_pair = animation["position"].get<std::pair<float, float>>();
    auto position      = ASGE::Point2D(position_pair.first, position_pair.second);
    auto speed         = animation["speed"].get<float>();
    auto& this_anim    = animations.emplace_back(AnimatedSprite(renderer, path, speed, position));
    this_anim.zOrder(static_cast<short>(layer));
  }
}
void TileMap::setCollision(size_t index, int _collision)
{
  collisions[index] = _collision;
}
int TileMap::getCollision(size_t index)
{
  return collisions[index];
}
int TileMap::getCollisionPos(ASGE::Point2D position)
{
  auto x     = static_cast<size_t>(position.x / 32);
  auto y     = static_cast<size_t>(position.y / 32);
  auto index = x + y * 50;
  return getCollision(index);
}
ASGE::Point2D TileMap::getSpawn(size_t index)
{
  return spawn_points[index % spawn_points.size()];
}
void TileMap::renderSection(ASGE::Point2D top_left, ASGE::Point2D bottom_right)
{
  int min_x       = static_cast<int>(top_left.x) / 32;
  int min_y       = static_cast<int>(top_left.y) / 32;
  int max_x       = static_cast<int>(bottom_right.x) / 32 + 1;
  int max_y       = static_cast<int>(bottom_right.y) / 32 + 1;
  size_t max_tile = tiles[0].size();
  for (int x = min_x; x < max_x; x++)
  {
    for (int y = min_y; y < max_y; y++)
    {
      int tile_int = x + y * 50;
      auto tile    = static_cast<size_t>(tile_int);
      if (tile >= max_tile)
      {
        continue;
      }
      for (auto& layer : tiles)
      {
        layer[tile].render(renderer);
      }
    }
  }
  for (auto& animation : animations)
  {
    if (
      animation.position().x < bottom_right.x && animation.position().y < bottom_right.y &&
      animation.position().x + animation.dimensions().x > top_left.x &&
      animation.position().y + animation.dimensions().y > top_left.y)
    {
      animation.render(renderer);
    }
  }
}
void TileMap::setAnimatedTile(size_t layer, size_t index, const std::string& file_path, float speed)
{
  size_t row      = index / 50;
  auto& this_anim = animations.emplace_back(AnimatedSprite(
    renderer,
    file_path,
    speed,
    ASGE::Point2D(static_cast<float>(index % 50) * 32, static_cast<float>(row) * 32)));
  this_anim.zOrder(static_cast<short>(layer));
}
