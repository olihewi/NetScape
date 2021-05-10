//
// Created by hewis on 10/05/2021.
//

#ifndef ASGEMOVIEGAME_CROSSHAIR_H
#define ASGEMOVIEGAME_CROSSHAIR_H

#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>
class Crosshair : public Sprite
{
 public:
  Crosshair(ASGE::Renderer* renderer, size_t _player_id);
  void update(InputTracker& input, float dt) override;

 private:
  size_t player_id;
};

#endif // ASGEMOVIEGAME_CROSSHAIR_H
