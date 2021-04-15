//
// Created by hewis on 15/04/2021.
//

#include "ASGEGameLib/Utilities/KeyboardTracker.h"
KeyboardTracker::KeyboardTracker(ASGE::Input* _input) :
  input(_input),
  keyboard_callback_id(input->addCallbackFnc(ASGE::E_KEY, &KeyboardTracker::keyInput, this))
{
}
KeyboardTracker::~KeyboardTracker()
{
  input->unregisterCallback(static_cast<unsigned int>(keyboard_callback_id));
}
void KeyboardTracker::keyInput(ASGE::SharedEventData data)
{
  queue.emplace_back(data);
}
void KeyboardTracker::updateInput()
{
  old_data = new_data;
  for (auto& data : queue)
  {
    const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());
    if (key->action != ASGE::KEYS::KEY_REPEATED)
    {
      bool pressed       = key->action == ASGE::KEYS::KEY_PRESSED;
      new_data[key->key] = pressed;
    }
  }
  queue.clear();
}
bool KeyboardTracker::getKey(int _key)
{
  return new_data[_key];
}
bool KeyboardTracker::getKeyDown(int _key)
{
  return new_data[_key] && !old_data[_key];
}
bool KeyboardTracker::getKeyUp(int _key)
{
  return !new_data[_key] && old_data[_key];
}
