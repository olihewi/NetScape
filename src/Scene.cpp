//
// Created by hewis on 31/03/2021.
//

#include "Scenes/Scene.h"

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
void Scene::addObject(std::unique_ptr<GameObject> object)
{
  game_objects.emplace_back(std::move(object));
}
Scene::Scene(std::function<void(Scenes)> _scene_callback) :
  audio_engine(std::make_unique<SoLoud::Soloud>()), scene_callback(std::move(_scene_callback))
{
  audio_engine->init();
}
void Scene::setScene(Scene::Scenes _scene)
{
  scene_callback(_scene);
}
Scene::~Scene()
{
  audio_engine->deinit();
}
