#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

#include "src/Saucer.h"
#include "src/Hero.h"

void loadResources(void) {
  RM.loadSprite("sprites/saucer-spr.txt", "saucer");
  RM.loadSprite("sprites/ship-spr.txt", "ship");
  RM.loadSprite("sprites/bullet-spr.txt", "bullet");
}

void populateWorld(void) {
  new Saucer;
  new Hero;
}

int main(int argc, char *argv[]) {
  // Start up game manager.
  if (GM.startUp())  {
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

