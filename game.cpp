#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "src/Hero.h"
#include "src/Points.h"
#include "src/Saucer.h"
#include "src/Star.h"

void loadResources(void) {
  RM.loadSprite("sprites/saucer-spr.txt", "saucer");
  RM.loadSprite("sprites/ship-spr.txt", "ship");
  RM.loadSprite("sprites/bullet-spr.txt", "bullet");
  RM.loadSprite("sprites/explosion-spr.txt", "explosion");
  RM.loadSprite("sprites/gameover-spr.txt", "gameover");
}

void populateWorld(void) {
  for (int i = 0; i < 16; i++) new Saucer;

  new Hero;

  for (int i = 0; i < 16; i++) new Star;

  new Points;

  df::ViewObject *p_vo = new df::ViewObject;
  p_vo->setLocation(df::TOP_LEFT);
  p_vo->setViewString("Nukes");
  p_vo->setValue(1);
  p_vo->setColor(df::YELLOW);
}

int main(int argc, char *argv[]) {
  // Start up game manager.
  if (GM.startUp()) {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 1;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  // Show splash screen.
  df::splash();

  loadResources();
  populateWorld();

  GM.run();

  // Shut everything down.
  GM.shutDown();
  return 0;
}
