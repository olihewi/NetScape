//
// Created by hewis on 31/03/2021.
//

#ifndef ASGEMOVIEGAME_SCALABLESPRITE_H
#define ASGEMOVIEGAME_SCALABLESPRITE_H

#include <ASGEGameLib/GameObjects/GameObject.h>
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>
class ScalableSprite : public GameObject
{
 public:
  ScalableSprite(
    ASGE::Renderer* renderer, const std::string& file_path, std::array<float, 6> part_sizes,
    ASGE::Point2D _position, ASGE::Point2D _dimensions);
  void position(ASGE::Point2D _position);
  [[nodiscard]] ASGE::Point2D dimensions();
  void dimensions(ASGE::Point2D _dimensions);
  void render(ASGE::Renderer* renderer) override;

  [[nodiscard]] bool isInside(ASGE::Point2D position);

 protected:
  std::array<std::unique_ptr<ASGE::Sprite>, 9> sprites;
};

#endif // ASGEMOVIEGAME_SCALABLESPRITE_H
