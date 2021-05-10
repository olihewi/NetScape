//
// Created by hewis on 01/04/2021.
//

#ifndef ASGEMOVIEGAME_TILEMAP_H
#define ASGEMOVIEGAME_TILEMAP_H

#include <ASGEGameLib/GameObjects/Player/Weapons/WeaponDrop.h>
#include <ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h>
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
  void renderSection(ASGE::Point2D top_left, ASGE::Point2D bottom_right);
  void setTile(size_t layer, size_t index, std::array<float, 4> rect);
  void setAnimatedTile(size_t layer, size_t index, const std::string& file_path, float speed);
  void setCollision(size_t index, int _collision);
  void deleteTile(size_t layer, size_t index);

  [[nodiscard]] int getCollision(size_t index);
  [[nodiscard]] int getCollisionPos(ASGE::Point2D position);

  [[nodiscard]] ASGE::Point2D getSpawn(size_t index);
  [[nodiscard]] std::vector<WeaponDrop>& getDrops();

 private:
  std::vector<std::array<Tile, 2500>> tiles;
  std::array<int, 2500> collisions;
  ASGE::Renderer* renderer;
  std::string tileset_path;
  std::vector<ASGE::Point2D> spawn_points;
  std::vector<AnimatedSprite> animations;
  std::vector<WeaponDrop> weapon_drops;
};

#endif // ASGEMOVIEGAME_TILEMAP_H
