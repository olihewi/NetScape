//
// Created by hewis on 31/03/2021.
//

#ifndef ASGEMOVIEGAME_TEXT_H
#define ASGEMOVIEGAME_TEXT_H

#include <GameObjects/GameObject.h>
class Text : public GameObject
{
 public:
  Text(
    ASGE::Renderer* renderer, const std::string& _contents,
    ASGE::Point2D position = ASGE::Point2D(), int font_index = 0,
    ASGE::Colour colour = ASGE::COLOURS::WHITE, float scale = 1, short z_order = 1);

  [[nodiscard]] std::string contents();
  void contents(std::string _contents);

  [[nodiscard]] bool visibility() const;
  void visibility(bool _visibility);

  [[nodiscard]] ASGE::Point2D position();
  void position(ASGE::Point2D _position);
  void translate(ASGE::Point2D _translation);

  [[nodiscard]] ASGE::Colour colour();
  void colour(ASGE::Colour _colour);

  [[nodiscard]] short zOrder();
  void zOrder(short _z_order);

  void setFont(ASGE::Renderer* renderer, int _font_index);

  [[nodiscard]] float scale();
  void scale(float _scale);

  void render(ASGE::Renderer* renderer) override;

 private:
  ASGE::Text text;
  bool visible = true;
};

#endif // ASGEMOVIEGAME_TEXT_H
