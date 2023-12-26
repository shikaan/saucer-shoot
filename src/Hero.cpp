#include "Hero.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventStep.h"

void Hero::kbd(const df::EventKeyboard *p_keyboard_event)
{
  switch (p_keyboard_event->getKey())
  {
  case df::Keyboard::Q:
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) GM.setGameOver();
    break;
  case df::Keyboard::W:
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) move(-1);
    break;
  case df::Keyboard::S:
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) move(+1);
    break;
  default:
    break;
  }
}

void Hero::move(int dy)
{
   // See if time to move.
  if (move_countdown > 0)
    return;
  move_countdown = move_slowdown;

  df::Vector old_position = getPosition();
  df::Vector new_position(old_position.getX(), old_position.getY() + dy);

  bool is_within_boundaries = new_position.getY() > 3 && new_position.getY() < WM.getBoundary().getVertical()-1;

  if (is_within_boundaries) {
    WM.moveObject(this, new_position);
  }
}

void Hero::step() {
  move_countdown--;
  if (move_countdown < 0) {
    move_countdown = 0;
  }
}

Hero::Hero()
{
  setSprite("ship");
  setType("Hero");

  df::Vector p(7, WM.getBoundary().getVertical()/2);
  setPosition(p);

  move_slowdown = 2;
  move_countdown = move_slowdown;

  registerInterest(df::STEP_EVENT);
  registerInterest(df::KEYBOARD_EVENT);
}

int Hero::eventHandler(const df::Event *p_e)
{
  if (p_e->getType() == df::KEYBOARD_EVENT) {
    const df::EventKeyboard *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
    kbd(p_keyboard_event);
    return 1;
  }

  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }

  return 0;
}