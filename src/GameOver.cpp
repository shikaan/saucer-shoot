#include "GameOver.h"

#include "DisplayManager.h"
#include "EventStep.h"
#include "GameStart.h"
#include "Object.h"
#include "ObjectListIterator.h"
#include "ResourceManager.h"
#include "WorldManager.h"

void GameOver::step() {
  time_to_live--;

  if (time_to_live <= 0)
    WM.markForDelete(this);
}

GameOver::GameOver() {
  setType("GameOver");
  if (setSprite("gameover") == 0)
    time_to_live = getAnimation().getSprite()->getFrameCount() *
                   getAnimation().getSprite()->getSlowdown();
  else
    time_to_live = 0;

  auto w = getAnimation().getBox().getWidth();
  auto h = getAnimation().getBox().getHeight();
  setPosition(df::Vector((DM.getHorizontalCells() / 2.0) - (w / 2.0),
                         (DM.getVerticalCells() / 2.0) - (h / 2.0)));

  subscribe(df::STEP_EVENT);
  setSolidness(df::SPECTRAL);
  setAltitude(df::MAX_ALTITUDE);

  df::Sound *p_sound = RM.getSound("game over");
  if (p_sound)
    p_sound->play();
}

GameOver::~GameOver() {
  df::ObjectList object_list = WM.getAllObjects(true);
  df::ObjectListIterator i(&object_list);
  for (i.first(); !i.isDone(); i.next()) {
    df::Object *p_o = i.currentObject();

    if (p_o->getType() == "GameStart") {
      p_o->setActive(true);
    } else if (p_o->getType() != "Star") {
      WM.markForDelete(p_o);
    }
  }
}

int GameOver::eventHandler(const df::Event *p_e) {
  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }

  return 0;
}
