#include "Saucer.h"

#include "EventCollision.h"
#include "EventNuke.h"
#include "EventOut.h"
#include "EventView.h"
#include "Explosion.h"
#include "GameManager.h"
#include "LogManager.h"
#include "Points.h"
#include "ResourceManager.h"
#include "WorldManager.h"

Saucer::Saucer() {
  // Set sprite taken from game.cpp
  setSprite("saucer");

  setType("Saucer");
  setVelocity(df::Vector(-0.25, 0));

  moveToStart();

  registerInterest(NUKE_EVENT);
}

Saucer::~Saucer() {
  df::EventView ev(POINTS_STRING, 10, true);
  WM.onEvent(&ev);
}

int Saucer::eventHandler(const df::Event *p_e) {
  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }

  if (p_e->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *p_collision_event =
        dynamic_cast<const df::EventCollision *>(p_e);
    hit(p_collision_event);
    return 1;
  }

  if (p_e->getType() == NUKE_EVENT) {
    explode();
    return 1;
  }

  return 0;
}

void Saucer::out() {
  if (getPosition().getX() >= 0) {
    return;
  }

  new Saucer;
}

void Saucer::moveToStart() {
  df::Vector temp_position;

  float world_h = WM.getBoundary().getHorizontal();
  float world_v = WM.getBoundary().getVertical();

  temp_position.setX(world_h + rand() % (int)world_h + 3.0f);
  temp_position.setY(rand() % (int)(world_v - 4) + 3.0f);

  df::ObjectList collision_list = WM.getCollisions(this, temp_position);
  while (!collision_list.isEmpty()) {
    temp_position.setX(temp_position.getX() + 1);
    collision_list = WM.getCollisions(this, temp_position);
  }

  WM.moveObject(this, temp_position);
}

void Saucer::hit(const df::EventCollision *p_event_collision) {
  if (p_event_collision->getObject1()->getType() == "Hero" ||
      p_event_collision->getObject2()->getType() == "Hero") {
    WM.markForDelete(p_event_collision->getObject1());
    WM.markForDelete(p_event_collision->getObject2());

    df::Sound *p_sound = RM.getSound("explode");
    if (p_sound) p_sound->play();
  }
}

void Saucer::explode() {
  Explosion *p_explosion = new Explosion;
  p_explosion->setPosition(this->getPosition());
  WM.markForDelete(this);

  // Create an enemy when the old one dies
  new Saucer;
}