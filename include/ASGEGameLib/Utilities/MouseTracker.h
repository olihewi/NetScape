//
// Created by hewis on 15/04/2021.
//

#ifndef ASGEMOVIEGAME_MOUSETRACKER_H
#define ASGEMOVIEGAME_MOUSETRACKER_H
#include <Engine/Input.hpp>
#include <Engine/Point2D.hpp>
namespace MOUSE
{
  constexpr int LEFT_CLICK   = 0;
  constexpr int RIGHT_CLICK  = 1;
  constexpr int MIDDLE_CLICK = 2;
  constexpr int MOUSE_4      = 3;
  constexpr int MOUSE_5      = 4;
}
class MouseTracker
{
 public:
  explicit MouseTracker(ASGE::Input* _input);
  MouseTracker(const MouseTracker& copy) = delete;
  MouseTracker& operator=(MouseTracker other) = delete;
  ~MouseTracker();

  void mouseInput(ASGE::SharedEventData data);
  void updateInput();

  [[nodiscard]] bool getButton(int _index);
  [[nodiscard]] bool getButtonDown(int _index);
  [[nodiscard]] bool getButtonUp(int _index);

  [[nodiscard]] ASGE::Point2D getMousePos();
  [[nodiscard]] ASGE::Point2D getMouseDelta() const;

  [[nodiscard]] ASGE::Point2D getScroll();

 private:
  ASGE::Input* input;
  std::vector<ASGE::SharedEventData> queue;
  int click_callback_id  = -1;
  int move_callback_id   = -1;
  int scroll_callback_id = -1;

  ASGE::Point2D old_mouse_pos = ASGE::Point2D();
  ASGE::Point2D new_mouse_pos = ASGE::Point2D();

  std::unordered_map<int, bool> old_click_state;
  std::unordered_map<int, bool> new_click_state;

  ASGE::Point2D scroll_state = ASGE::Point2D();
};

#endif // ASGEMOVIEGAME_MOUSETRACKER_H
