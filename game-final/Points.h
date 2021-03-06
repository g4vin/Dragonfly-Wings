//
// Points.h
// 
#ifndef __POINTS_H__ 
#define __POINTS_H__
#include "Event.h"		
#include "ViewObject.h"

#define POINTS_STRING "Points"

class Points : public df::ViewObject {

 private:
 int type;
 public:
  Points(int type);
  int eventHandler(const df::Event *p_e);
  int scoreUpdate;
};
#endif //POINTS_H
