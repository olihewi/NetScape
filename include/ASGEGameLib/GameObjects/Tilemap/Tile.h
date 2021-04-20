//
// Created by hewis on 01/04/2021.
//

#ifndef ASGEMOVIEGAME_TILE_H
#define ASGEMOVIEGAME_TILE_H
#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>
class Tile : public GameObject
{
 public:
  Tile() = default;
  Tile(
    ASGE::Renderer* renderer, const std::string& tileset_path, std::array<float, 4> rect,
    ASGE::Point2D position, int layer = 0);
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;

  [[nodiscard]] int getIndex();

 private:
  std::unique_ptr<Sprite> sprite;
};

#endif // ASGEMOVIEGAME_TILE_H
