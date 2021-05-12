//
// Created by Work on 12/05/2021.
//

#include "ASGEGameLib/GameObjects/Player/HUD/PlayerScore.hpp"
#include "Engine/Logger.hpp"
#include <ASGEGameLib/Utilities/FontManager.h>

PlayerScore::PlayerScore(ASGE::Renderer* renderer, Player& _player, float x, float y) :
  position(ASGE::Point2D(x, y)), player(_player),
  score_card(renderer, "data/images/ui/score_card.png", position),
  score_text(std::array<Text, 6>{
    Text(renderer, "", ASGE::Point2D(), FONTS::PIXEL, ASGE::COLOURS::WHITE, 0.8F),
    Text(renderer, "", ASGE::Point2D(), FONTS::PIXEL, ASGE::COLOURS::WHITE, 0.7F),
    Text(renderer, "", ASGE::Point2D(), FONTS::PIXEL, ASGE::COLOURS::WHITE, 0.6F),
    Text(renderer, "", ASGE::Point2D(), FONTS::PIXEL, ASGE::COLOURS::WHITE, 0.6F),
    Text(renderer, "", ASGE::Point2D(), FONTS::PIXEL, ASGE::COLOURS::WHITE, 0.6F),
    Text(renderer, "", ASGE::Point2D(), FONTS::PIXEL, ASGE::COLOURS::WHITE, 0.6F) })
{
  score_card.centrePos(ASGE::Point2D(position));
  score_text[0].position(ASGE::Point2D(475, 168));                      // PLAYER ID
  score_text[1].position(ASGE::Point2D(255, 230));                      // KILLS AND THAT
  score_text[2].position(ASGE::Point2D(525, 230));                      // FAVOURITE WEAPON
  score_text[3].position(ASGE::Point2D(score_text[2].getWidth(), 260)); // WEAPON NAME
  score_text[4].position(ASGE::Point2D(
    score_text[2].position().x + score_text[2].getWidth() - score_text[3].getWidth(),
    315));                                         // NEMESIS
  score_text[5].position(ASGE::Point2D(525, 345)); // PLAYER ID
}
void PlayerScore::update(InputTracker& input, float dt)
{
  // INPUT
  auto score_sheet_button =
    input.getControllerButtonDown(player.getID(), CONTROLLER::BUTTONS::BACK);
  // UPDATE TEXT
  if (score_sheet_button)
  {
    display_score_sheet = !display_score_sheet;
  }

  int accuracy = static_cast<int>(
    (player.getScore().hit / (player.getScore().hit + player.getScore().miss)) * 100);
  if (accuracy < 0)
  {
    accuracy = 0;
  }

  auto current_nemesis = 0;

  for (size_t i = 0; i < player.getScore().nemesis_points.size(); ++i)
  {
    if (player.getScore().nemesis_points[i] > current_nemesis)
    {
      current_nemesis = static_cast<int>(i);
    }
  }

  for (auto& i : player.getScore().favourite_gun)
  {
    if (i.second > current_favourite_weapon_index)
    {
      current_favourite_weapon_index = i.second;
      favourite_weapon               = i.first;
      Logging::DEBUG("FAVOURITE WEAPON = " + i.first);
    }
  }

  score_text[0].contents("Player " + std::to_string(player.getID() + 1));
  score_text[1].contents(
    "Kills: " + std::to_string(player.getScore().kills) +
    "\nDeaths: " + std::to_string(player.getScore().deaths) +
    "\nMisses: " + std::to_string(static_cast<int>(player.getScore().miss)) +
    "\nHits: " + std::to_string(static_cast<int>(player.getScore().hit)) +
    "\nAccuracy: " + std::to_string(accuracy) + "%");
  // if(player.getScore().kills > 0)
  //{
  score_text[2].contents("Deadliest Weapon:");
  score_text[3].contents(favourite_weapon);
  score_text[3].position(ASGE::Point2D(
    (score_text[2].position().x + score_text[2].getWidth()) - score_text[3].getWidth(),
    position.y));

  //}
  if (player.getScore().deaths > 0)
  {
    score_text[4].contents("Nemesis:");
    score_text[5].contents("PLAYER " + std::to_string(current_nemesis + 1));
    score_text[5].position(ASGE::Point2D(
      (score_text[2].position().x + score_text[2].getWidth()) - score_text[5].getWidth(), 345));
  }
  /*for(auto& i :score_text)
  {
    i.visibility(!i.visibility());
  }*/
  // score_card.visibility(!score_card.visibility());

  GameObject::update(input, dt);
}

void PlayerScore::render(ASGE::Renderer* renderer)
{
  // if (score_card.visibility())
  //{
  if (display_score_sheet)
  {
    for (auto& i : score_text)
    {
      i.render(renderer);
    }
    score_card.render(renderer);
  }
}
