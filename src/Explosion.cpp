#include "Explosion.h"
#include "EventStep.h"
#include "WorldManager.h"

void Explosion::step()
{
  time_to_live--;
  if (time_to_live <= 0)
    WM.markForDelete(this);
}

Explosion::Explosion()
{
  setType("Explosion");
  if (setSprite("explosion") == 0) {
    time_to_live = getAnimation().getSprite()->getFrameCount();
  } else {
    time_to_live = 0;
  }

  setSolidness(df::SPECTRAL);
  registerInterest(df::STEP_EVENT );
}

int Explosion::eventHandler(const df::Event *p_event)
{
  if (p_event->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }

  return 0;
}
