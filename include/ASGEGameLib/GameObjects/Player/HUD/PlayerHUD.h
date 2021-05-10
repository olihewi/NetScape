//
// Created by hewis on 08/05/2021.
//

#ifndef ASGEMOVIEGAME_PLAYERHUD_H
#define ASGEMOVIEGAME_PLAYERHUD_H

#include <ASGEGameLib/GameObjects/GameObject.h>
class PlayerHUD : public GameObject
{
 public:
  explicit PlayerHUD(size_t _index);
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;
  void addObject(std::unique_ptr<GameObject> _object);

  [[nodiscard]] float getFocus() const;

 private:
  size_t index;
  std::vector<std::unique_ptr<GameObject>> objects;
  float lerped_focus = 0;
};

#endif // ASGEMOVIEGAME_PLAYERHUD_H
