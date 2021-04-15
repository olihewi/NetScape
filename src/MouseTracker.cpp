//
// Created by hewis on 15/04/2021.
//

#include "ASGEGameLib/Utilities/MouseTracker.h"
MouseTracker::MouseTracker(ASGE::Input* _input) :
  input(_input),
  click_callback_id(input->addCallbackFnc(ASGE::E_MOUSE_CLICK, &MouseTracker::mouseInput, this)),
  move_callback_id(input->addCallbackFnc(ASGE::E_MOUSE_MOVE, &MouseTracker::mouseInput, this)),
  scroll_callback_id(input->addCallbackFnc(ASGE::E_MOUSE_SCROLL, &MouseTracker::mouseInput, this))
{
}
MouseTracker::~MouseTracker()
{
  input->unregisterCallback(static_cast<unsigned int>(click_callback_id));
  input->unregisterCallback(static_cast<unsigned int>(move_callback_id));
  input->unregisterCallback(static_cast<unsigned int>(scroll_callback_id));
}
void MouseTracker::mouseInput(ASGE::SharedEventData data)
{
  queue.emplace_back(data);
}
void MouseTracker::updateInput()
{
  old_mouse_pos   = new_mouse_pos;
  old_click_state = new_click_state;
  scroll_state    = ASGE::Point2D();
  for (auto& data : queue)
  {
    const auto* mouse = dynamic_cast<const ASGE::MoveEvent*>(data.get());
    if (mouse != nullptr)
    {
      new_mouse_pos =
        ASGE::Point2D(static_cast<float>(mouse->xpos), static_cast<float>(mouse->ypos));
      continue;
    }
    const auto* click = dynamic_cast<const ASGE::ClickEvent*>(data.get());
    if (click != nullptr)
    {
      if (click->action != ASGE::KEYS::KEY_REPEATED)
      {
        new_click_state[click->button] = click->action == ASGE::KEYS::KEY_PRESSED;
      }
      continue;
    }
    const auto* scroll = dynamic_cast<const ASGE::ScrollEvent*>(data.get());
    if (scroll != nullptr)
    {
      scroll_state =
        ASGE::Point2D(static_cast<float>(scroll->xoffset), static_cast<float>(scroll->yoffset));
      continue;
    }
  }
  queue.clear();
}
bool MouseTracker::getButton(int _index)
{
  return new_click_state[_index];
}
bool MouseTracker::getButtonDown(int _index)
{
  return new_click_state[_index] && !old_click_state[_index];
}
bool MouseTracker::getButtonUp(int _index)
{
  return !new_click_state[_index] && old_click_state[_index];
}
ASGE::Point2D MouseTracker::getMousePos()
{
  return new_mouse_pos;
}
ASGE::Point2D MouseTracker::getMouseDelta() const
{
  return ASGE::Point2D(new_mouse_pos.x - old_mouse_pos.x, new_mouse_pos.y - old_mouse_pos.y);
}
ASGE::Point2D MouseTracker::getScroll()
{
  return scroll_state;
}
