//
// Created by hewis on 11/04/2021.
//

#include "ASGEGameLib/Scenes/GameScene.h"
#include "Utilities/FontManager.h"
#include "GameObjects/Sprites/AnimatedSprite.h"

GameScene::GameScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
Scene(std::move(_scene_callback))
{
  player.player->render(renderer);

}

void GameScene::controllerInput(ControllerTracker& controllers, float)
{

}
