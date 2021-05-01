//
// Created by hewis on 01/04/2021.
//

#ifndef ASGEMOVIEGAME_LEVELEDITOR_H
#define ASGEMOVIEGAME_LEVELEDITOR_H

#include "Scene.h"
#include <ASGEGameLib/GameObjects/Tilemap/EditorTileSet.h>
#include <ASGEGameLib/GameObjects/Tilemap/TileMap.h>
#include <ASGEGameLib/GameObjects/UI/Cursor.h>
#include <ASGEGameLib/GameObjects/UI/UIButton.h>
#include <Engine/Camera.hpp>
class LevelEditor : public Scene
{
 public:
  explicit LevelEditor(ASGE::Renderer* _renderer, std::function<void(Scenes)> _scene_callback);
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* /*renderer*/) override;

  void saveLevel(const std::string& file_name);
  void loadLevel(const std::string& file_name);

 private:
  void placeTiles(ASGE::Point2D _position);
  ASGE::Renderer* renderer;
  TileMap tile_map;
  EditorTileSet tile_set;
  std::array<UIButton, 1> scene_change_buttons;
  Cursor cursor;
  ASGE::Camera tilemap_camera;
  size_t current_layer = 0;
};

#endif // ASGEMOVIEGAME_LEVELEDITOR_H
