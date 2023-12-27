#include "Object.h"
#include "EventCollision.h"

class Saucer : public df::Object
{
private:
  void out();
  void moveToStart();
  void explode();
  void hit(const df::EventCollision *p_event_collision);

public:
  Saucer();
  ~Saucer();

  int eventHandler(const df::Event *p_e) override;
};
