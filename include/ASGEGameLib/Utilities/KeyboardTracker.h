//
// Created by hewis on 15/04/2021.
//

#ifndef ASGEMOVIEGAME_KEYBOARDTRACKER_H
#define ASGEMOVIEGAME_KEYBOARDTRACKER_H
#include <Engine/Input.h>
class KeyboardTracker
{
 public:
  explicit KeyboardTracker(ASGE::Input* _input);
  KeyboardTracker(const KeyboardTracker& copy) = delete;
  KeyboardTracker& operator=(KeyboardTracker other) = delete;
  ~KeyboardTracker();
  void keyInput(ASGE::SharedEventData data);
  void updateInput();
  bool getKey(int _key);
  bool getKeyDown(int _key);
  bool getKeyUp(int _key);

 private:
  ASGE::Input* input;
  std::unordered_map<int, bool> old_data;
  std::unordered_map<int, bool> new_data;
  std::vector<ASGE::SharedEventData> queue;
  int keyboard_callback_id = -1;
};

#endif // ASGEMOVIEGAME_KEYBOARDTRACKER_H
