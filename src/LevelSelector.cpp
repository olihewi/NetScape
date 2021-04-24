//
// Created by hewis on 23/04/2021.
//

#include "GameObjects/UI/LevelSelector.h"
#include <Engine/FileIO.hpp>
#include <iostream>
LevelSelector::LevelSelector(ASGE::Renderer* /*renderer*/)
{
  auto set_levels  = ASGE::FILEIO::enumerateFiles("data/levels");
  auto user_levels = ASGE::FILEIO::enumerateFiles("userlevels");
  for (auto& level : set_levels)
  {
    level.insert(0, "data/levels/");
    std::cout << level << std::endl;
  }
  for (auto& level : user_levels)
  {
    std::cout << level << std::endl;
  }
}
/*std::string LevelSelector::getLevelSelection()
{
  return std::string();
}*/
