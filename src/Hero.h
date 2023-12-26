#include "Object.h"
#include "EventKeyboard.h"

class Hero : public df::Object {
  private:
    void kbd(const df::EventKeyboard *p_keyboard_event);
    void move(int dy);
    int move_slowdown;
    int move_countdown;
    void step();

  public:
    Hero();
    int eventHandler(const df::Event *p_e) override;
};