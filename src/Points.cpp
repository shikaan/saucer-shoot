#include "Points.h"

#include "EventStep.h"

Points::Points() {
  setLocation(df::TOP_RIGHT);
  setLabel(POINTS_STRING);
  setColor(df::YELLOW);

  subscribe(df::STEP_EVENT);
}

int Points::eventHandler(const df::Event *p_e) {
  if (df::ViewObject::eventHandler(p_e)) {
    return 1;
  }

  if (p_e->getType() == df::STEP_EVENT) {
    const df::EventStep *step_event = dynamic_cast<const df::EventStep *>(p_e);

    if (step_event->getStepCount() % 30 == 0) {
      setValue(getValue() + 1);
    }

    return 1;
  }

  return 0;
}
