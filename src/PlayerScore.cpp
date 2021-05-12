//
// Created by Work on 12/05/2021.
//

#include "ASGEGameLib/GameObjects/Player/HUD/PlayerScore.hpp"
#include <ASGEGameLib/Utilities/FontManager.h>
PlayerScore::PlayerScore(ASGE::Renderer* renderer, Player& _player, float x, float y) :
  position(ASGE::Point2D(x, y)), player(_player),
  score_card(renderer, "data/images/ui/score_card.png", position),
  score_text(std::array<Text, 3>{
    Text(renderer, "", ASGE::Point2D(), FONTS::PIXEL, ASGE::COLOURS::WHITE, 0.8F),
    Text(renderer, "", ASGE::Point2D(), FONTS::PIXEL, ASGE::COLOURS::WHITE, 0.7F),
    Text(renderer, "", ASGE::Point2D(), FONTS::PIXEL, ASGE::COLOURS::WHITE, 0.7F) })
{
  score_card.centrePos(ASGE::Point2D(position));
  score_text[0].position(ASGE::Point2D(475, 168));
  score_text[1].position(ASGE::Point2D(255, 230));
  score_text[2].position(ASGE::Point2D(550, 325));
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
      current_nemesis = std::to_integer<int>(static_cast<const std::byte>(i));
    }
  }

  score_text[0].contents("Player " + std::to_string(player.getID() + 1));
  score_text[1].contents(
    "Kills: " + std::to_string(player.getScore().kills) +
    "\nDeaths: " + std::to_string(player.getScore().deaths) +
    "\nMisses: " + std::to_string(static_cast<int>(player.getScore().miss)) +
    "\nHits: " + std::to_string(static_cast<int>(player.getScore().hit)) +
    "\nAccuracy: " + std::to_string(accuracy) + "%");
  if (player.getScore().deaths > 0)
  {
    score_text[2].contents("Nemesis:\nPlayer " + std::to_string(current_nemesis + 1));
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
