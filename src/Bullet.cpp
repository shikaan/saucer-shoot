#include "Bullet.h"
#include "EventOut.h"
#include "WorldManager.h"

void Bullet::out()
{
  WM.markForDelete(this);
}

void Bullet::hit(const df::EventCollision *p_collision_event)
{
  Object* first = p_collision_event->getObject1();
  Object* second = p_collision_event->getObject2();

  if (first->getType() == "Saucer" || second->getType() == "Saucer") {
    WM.markForDelete(first);
    WM.markForDelete(second);
  }
}

Bullet::Bullet(const df::Vector hero_position)
{
  setSprite("bullet");
  setType("Bullet");

  df::Vector p(hero_position.getX() + 3, hero_position.getY());
  setPosition(p);
  setSpeed(1);
}

int Bullet::eventHandler(const df::Event *p_e)
{
  if (p_e->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);
    hit(p_collision_event);
    return 1;
  }

  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }

  return 0;
}
