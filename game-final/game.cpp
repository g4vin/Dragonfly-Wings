//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "Pause.h"
#include "ResourceManager.h"

// Game includes.
#include "GameStart.h"
#include "Star.h"

#include <iostream>

// Function prototypes.
void loadResources(void);
void populateWorld(Settings* info);
 
int main(int argc, char *argv[]) {
  df::LogManager &log_manager = df::LogManager::getInstance();

  // Start up game manager.
  df::GameManager &game_manager = df::GameManager::getInstance();
  if (game_manager.startUp())  {
    log_manager.writeLog("Error starting game manager!");
    game_manager.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  log_manager.setFlush(true);

  // Show splash screen.
  df::splash();

  // Load game resources.
  loadResources();

  //determine game settings
  Settings info(argc, argv);

  // Populate game world with some objects.
  populateWorld(&info);

  // Enable player to pause game or not because this is now a multiplayer game
  //new df::Pause(df::Keyboard::F10);
  
  // Run game (this blocks until game loop is over).
  game_manager.run();
  
  // Shut everything down.
  game_manager.shutDown();
}

// Load resources (sprites, sound effects, music).
void loadResources(void) {
  df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
  resource_manager.loadSprite("sprites/saucer-spr.txt", "saucer");
  resource_manager.loadSprite("sprites/ship-spr.txt", "ship");
  resource_manager.loadSprite("sprites/bullet-spr.txt", "bullet");
  resource_manager.loadSprite("sprites/explosion-spr.txt", "explosion");
  resource_manager.loadSprite("sprites/gamestart-spr.txt", "gamestart");
  resource_manager.loadSprite("sprites/gameover-spr.txt", "gameover");
  resource_manager.loadSound("sounds/fire.wav", "fire");
  resource_manager.loadSound("sounds/explode.wav", "explode");
  resource_manager.loadSound("sounds/nuke.wav", "nuke");
  resource_manager.loadSound("sounds/game-over.wav", "game over");
  resource_manager.loadMusic("sounds/start-music.wav", "start music");
}

// Populate world with some objects.
void populateWorld(Settings* info) {

  // Spawn some Stars.
  for (int i=0; i<16; i++) 
    new Star;
  
  new GameStart(info);
  
}
