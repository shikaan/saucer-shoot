#include "Reticle.h"
#include "SceneGraph.h"
#include "EventMouse.h"
#include "DisplayManager.h"

Reticle::Reticle()
{
  setType("Reticle");
  setSolidness(df::SPECTRAL);
  setAltitude(df::MAX_ALTITUDE);
  registerInterest(df::MSE_EVENT);
}

int Reticle::draw(void)
{
  return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}

int Reticle::eventHandler(const df::Event *p_e)
{
  if (p_e->getType() == df::MSE_EVENT)
  {
    const df::EventMouse *p_mouse_event = dynamic_cast<const df::EventMouse *>(p_e);
    if (p_mouse_event->getMouseAction() == df::MOVED)
    {
      setPosition(p_mouse_event->getMousePosition());
      return 1;
    }
  }
  return 0;
}