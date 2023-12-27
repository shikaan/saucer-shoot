#include "Saucer.h"
#include "WorldManager.h"
#include "EventOut.h"

Saucer::Saucer()
{
  // Set sprite taken from game.cpp
  setSprite("saucer");

  setType("Saucer");
  setVelocity(df::Vector(-0.25, 0));

  moveToStart();
}

int Saucer::eventHandler(const df::Event *p_e)
{
  if (p_e->getType() == df::OUT_EVENT)
  {
    out();
    return 1;
  }

  return 0;
}

void Saucer::out()
{
  if (getPosition().getX() >= 0)
  {
    return;
  }

  moveToStart();
}

void Saucer::moveToStart()
{
  df::Vector temp_position;

  float world_h = WM.getBoundary().getHorizontal();
  float world_v = WM.getBoundary().getVertical();

  temp_position.setX(world_h + rand() % (int)world_h + 3.0f);
  temp_position.setY(rand() % (int)(world_v - 1) + 1.0f);

  WM.moveObject(this, temp_position);
}