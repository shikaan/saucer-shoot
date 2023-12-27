#include "Object.h"
#include "EventCollision.h"

class Bullet : public df::Object {
private:
  void out();
  void hit(const df::EventCollision* p_collision_event);

public:
  Bullet(const df::Vector hero_position);
  int eventHandler(const df::Event* p_e) override;
};