//
// Host.h
//
#ifndef __HOST_H__ 
#define __HOST_H__

#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventNetwork.h"
#include "Object.h"
#include "Reticle.h"

#include "Settings.h"
#include "Sync.h"
#include "RemoteShip.h"
#include "Saucer.h"
#include "Points.h"

#include <vector>

class Host : public df::Object {

 private:
  Reticle *p_reticle;
  Settings* theSet;
  Sync* syncHalp;
  RemoteShip* otherPlayer;  
  Points* thepoints;
  std::vector<Saucer*> saucers;
 
  int fire_slowdown;
  int fire_countdown;
  int move_slowdown;
  int move_countdown;
  int nuke_count;
  void network(const df::EventNetwork *p_network_event);
  void mouse(const df::EventMouse *p_mouse_event);
  void kbd(const df::EventKeyboard *p_keyboard_event);
  void move(int dy);
  void fire(df::Position target);
  void step();
  void nuke();
  
 public:
  
  int killchild;
  Host(Settings* info);
  ~Host();
  int eventHandler(const df::Event *p_e);
};
#endif //HOST_H
