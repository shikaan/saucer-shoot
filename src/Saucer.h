#include "Object.h"
#include "EventCollision.h"

class Saucer : public df::Object
{
public:
  Saucer();

  int eventHandler(const df::Event *p_e) override;

  // Callback when the object is out of bounds
  void out();
  // Moves the saucer to the start of the screen
  void moveToStart();

  void hit(const df::EventCollision *p_event_collision);
};
