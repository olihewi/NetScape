//
// Created by hewis on 31/03/2021.
//

#ifndef ASGEMOVIEGAME_SPRITE_H
#define ASGEMOVIEGAME_SPRITE_H

#include <ASGEGameLib/GameObjects/GameObject.h>
#include <Engine/Sprite.hpp>
class Sprite : public GameObject
{
 public:
  Sprite(
    ASGE::Renderer* renderer, const std::string& file_path,
    ASGE::Point2D _position = ASGE::Point2D());
  bool loadSprite(ASGE::Renderer* renderer, const std::string& file_path);

  void render(ASGE::Renderer* renderer) override;

  [[nodiscard]] bool visibility() const;
  void visibility(bool _visibility);

  [[nodiscard]] ASGE::Point2D position();
  virtual void position(ASGE::Point2D _position);
  virtual void translate(ASGE::Point2D _translation);

  [[nodiscard]] ASGE::Point2D dimensions();
  void dimensions(ASGE::Point2D _dimensions);

  [[nodiscard]] float rotation();
  void rotation(float _radians);
  void rotate(float _radians);

  [[nodiscard]] ASGE::Colour colour();
  void colour(ASGE::Colour _colour);

  [[nodiscard]] float opacity();
  void opacity(float _opacity);

  [[nodiscard]] ASGE::Point2D centre();
  void centrePos(ASGE::Point2D position);

  [[nodiscard]] bool isInside(ASGE::Point2D _position);

  [[nodiscard]] short zOrder();
  void zOrder(short z_order);

  void srcRect(float x, float y, float w, float h);
  [[nodiscard]] std::array<float, 4> srcRect();

  [[nodiscard]] ASGE::Point2D getTextureSize();

 private:
  std::unique_ptr<ASGE::Sprite> sprite;
  bool visible = true;
};

#endif // ASGEMOVIEGAME_SPRITE_H
