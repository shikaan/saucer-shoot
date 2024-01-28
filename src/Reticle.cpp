#include "Reticle.h"

#include "DisplayManager.h"
#include "EventMouse.h"
#include "SceneGraph.h"

Reticle::Reticle() {
  setType("Reticle");
  setSolidness(df::SPECTRAL);
  setAltitude(df::MAX_ALTITUDE);
  subscribe(df::MSE_EVENT);
}

int Reticle::draw(void) {
  return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}

int Reticle::eventHandler(const df::Event *p_e) {
  if (p_e->getType() == df::MSE_EVENT) {
    const df::EventMouse *p_mouse_event =
        dynamic_cast<const df::EventMouse *>(p_e);
    if (p_mouse_event->getMouseAction() == df::MOVED) {
      setPosition(p_mouse_event->getMousePosition());
      return 1;
    }
  }
  return 0;
}