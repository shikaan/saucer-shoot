#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

#include "src/Saucer.h"

void loadResources(void) {
  RM.loadSprite("sprites/saucer-spr.txt", "saucer");
}

void populateWorld(void) {
  new Saucer;
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

