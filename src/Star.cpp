#include "Star.h"

#include "DisplayManager.h"
#include "EventOut.h"
#include "WorldManager.h"

void Star::out() {
  df::Vector p((float)(WM.getBoundary().getWidth() + rand() % 20),
               (float)(rand() % (int)WM.getBoundary().getHeight()));
  setPosition(p);
  setVelocity(getRandomVelocity());
}

df::Vector Star::getRandomVelocity(void) {
  return df::Vector(-1.0 / (rand() % 10 + 1), 0);
}

Star::Star() {
  setType("Star");
  setSolidness(df::SPECTRAL);
  setVelocity(getRandomVelocity());
  setAltitude(0);

  df::Vector p((float)(rand() % (int)WM.getBoundary().getWidth()),
               (float)(rand() % (int)WM.getBoundary().getHeight()));
  setPosition(p);
}

int Star::draw(void) { return DM.drawCh(getPosition(), STAR_CHAR, df::WHITE); }

int Star::eventHandler(const df::Event *p_e) {
  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }

  return 0;
}
