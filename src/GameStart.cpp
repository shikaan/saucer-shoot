#include "GameStart.h"

#include "EventKeyboard.h"
#include "GameManager.h"
#include "Hero.h"
#include "Points.h"
#include "ResourceManager.h"
#include "Saucer.h"

GameStart::GameStart() {
  setType("GameStart");
  setSprite("gamestart");
  setLocation(df::CENTER_CENTER);
  registerInterest(df::KEYBOARD_EVENT);

  p_music = RM.getMusic("start music");
  toggleMusic(true);
}

void GameStart::toggleMusic(bool on) {
  if (!p_music) return;

  if (on)
    p_music->play(true);
  else
    p_music->pause();
}

int GameStart::eventHandler(const df::Event *p_e) {
  if (p_e->getType() == df::KEYBOARD_EVENT) {
    const df::EventKeyboard *p_kdb_evt =
        dynamic_cast<const df::EventKeyboard *>(p_e);

    switch (p_kdb_evt->getKey()) {
      case df::Keyboard::P:
        start();
        break;

      case df::Keyboard::Q:
        GM.setGameOver();
        break;

      default:
        break;
    }

    return 1;
  }
  return 0;
}

int GameStart::draw() { return df::Object::draw(); }

int GameStart::setActive(bool new_active) {
  toggleMusic(new_active);

  return df::Object::setActive(new_active);
}

void GameStart::start() {
  for (int i = 0; i < 16; i++) new Saucer;

  new Hero;

  new Points;

  df::ViewObject *p_vo = new df::ViewObject;
  p_vo->setLocation(df::TOP_LEFT);
  p_vo->setViewString("Nukes");
  p_vo->setValue(1);
  p_vo->setColor(df::YELLOW);

  setActive(false);
  p_music->pause();
}