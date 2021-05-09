//
// Created by hewis on 08/05/2021.
//

#ifndef ASGEMOVIEGAME_PLAYERHUD_H
#define ASGEMOVIEGAME_PLAYERHUD_H

#include <ASGEGameLib/GameObjects/GameObject.h>
class PlayerHUD : public GameObject
{
 public:
  PlayerHUD() = default;
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;
  void addObject(std::unique_ptr<GameObject> _object);

 private:
  std::vector<std::unique_ptr<GameObject>> objects;
};

#endif // ASGEMOVIEGAME_PLAYERHUD_H
