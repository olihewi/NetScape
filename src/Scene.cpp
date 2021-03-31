//
// Created by hewis on 31/03/2021.
//

#include "ASGEGameLib/Scenes/Scene.h"

void Scene::keyInput(const ASGE::KeyEvent* key)
{
  for (auto& game_object : game_objects)
  {
    game_object->keyInput(key);
  }
}
void Scene::clickInput(const ASGE::ClickEvent* click)
{
  for (auto& game_object : game_objects)
  {
    game_object->clickInput(click);
  }
}
void Scene::mouseInput(const ASGE::MoveEvent* mouse)
{
  for (auto& game_object : game_objects)
  {
    game_object->mouseInput(mouse);
  }
}
void Scene::scrollInput(const ASGE::ScrollEvent* scroll)
{
  for (auto& game_object : game_objects)
  {
    game_object->scrollInput(scroll);
  }
}
void Scene::update(float dt)
{
  for (auto& game_object : game_objects)
  {
    game_object->update(dt);
  }
}
void Scene::render(ASGE::Renderer* renderer)
{
  for (auto& game_object : game_objects)
  {
    game_object->render(renderer);
  }
}
