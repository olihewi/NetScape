//
// Created by hewis on 23/04/2021.
//

#ifndef ASGEMOVIEGAME_LEVELSELECTOR_H
#define ASGEMOVIEGAME_LEVELSELECTOR_H

#include <ASGEGameLib/GameObjects/UI/UIButton.h>
class LevelSelector : public GameObject
{
 public:
  explicit LevelSelector(ASGE::Renderer* renderer);
  //[[nodiscard]] std::string getLevelSelection();
 private:
  // std::vector<UIButton> level_buttons;
};

#endif // ASGEMOVIEGAME_LEVELSELECTOR_H
