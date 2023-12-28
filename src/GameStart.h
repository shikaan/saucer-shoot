#include "Music.h"
#include "ViewObject.h"

class GameStart : public df::ViewObject {
 private:
  void start();
  df::Music *p_music;

 public:
  GameStart();
  void toggleMusic(bool on);
  int eventHandler(const df::Event *p_e) override;
  int draw() override;
  int setActive(bool new_active = true);
};