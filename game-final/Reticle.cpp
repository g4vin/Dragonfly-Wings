//
// Reticle.cpp
//

// Engine includes.
#include "EventMouse.h"
#include "GraphicsManager.h"
#include "WorldManager.h"

// Game includes.
#include "Reticle.h"

Reticle::Reticle() {
  setType("Reticle");
  setSolidness(df::SPECTRAL);
  setAltitude(df::MAX_ALTITUDE); // Make Reticle in foreground.

  // Reticle moves with mouse, so register.
  registerInterest(df::MOUSE_EVENT);

  // Start reticle in center of window.
  df::WorldManager &world_manager = df::WorldManager::getInstance();
  df::Position pos(world_manager.getBoundary().getHorizontal()/2,
		   world_manager.getBoundary().getVertical()/2);
  setPosition(pos);
}

// Handle event.
// Return 0 if ignored, else 1.
int Reticle::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::MOUSE_EVENT) {
    const df::EventMouse *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);
    if (p_mouse_event->getMouseAction() == df::MOVED) {
      // Change location to new mouse position.
      setPosition(p_mouse_event->getMousePosition());
      return 1;
    }
  }

  // If get here, have ignored this event.
  return 0;
}

// Draw reticle on window.
void Reticle::draw() {
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  graphics_manager.drawCh(getPosition(), RETICLE_CHAR, df::RED); 
}
