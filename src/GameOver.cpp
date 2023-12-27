#include "GameOver.h"

#include "EventStep.h"
#include "GameManager.h"
#include "WorldManager.h"

void GameOver::step() {
  time_to_live--;

  if (time_to_live <= 0) WM.markForDelete(this);
}

GameOver::GameOver() {
  setType("GameOver");
  if (setSprite("gameover") == 0)
    time_to_live = getAnimation().getSprite()->getFrameCount() *
                   getAnimation().getSprite()->getSlowdown();
  else
    time_to_live = 0;

  setLocation(df::CENTER_CENTER);
  registerInterest(df::STEP_EVENT);
}

GameOver::~GameOver() {
  df::ObjectList object_list = WM.getAllObjects(true);
  df::ObjectListIterator i(&object_list);
  for (i.first(); !i.isDone(); i.next()) {
    df::Object* p_o = i.currentObject();

    if (p_o->getType() != "Saucer" || p_o->getType() == "ViewObject")
      WM.markForDelete(p_o);
  }

  GM.setGameOver();
}

int GameOver::eventHandler(const df::Event* p_e) {
  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }

  return 0;
}

int GameOver::draw() { return df::Object::draw(); }
