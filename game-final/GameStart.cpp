//
// GameStart.cpp
//

// Engine includes.
#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "GameStart.h"
#include "Host.h"
#include "Client.h"
#include "Music.h"

GameStart::GameStart(Settings* info) {
    setType("GameStart");

    // Link to "message" sprite.
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::Sprite *p_temp_sprite = resource_manager.getSprite("gamestart");
    if (!p_temp_sprite) {
        df::LogManager &log_manager = df::LogManager::getInstance();
        log_manager.writeLog("GameStart::GameStart(): Warning! Sprite 'gamestart' not found");
    } else {
        setSprite(p_temp_sprite);
        setSpriteSlowdown(15);
    }

    // Put in center of screen.
    setLocation(df::CENTER_CENTER);

    // Register for "keyboard" event.
    registerInterest(df::KEYBOARD_EVENT);

    // Play start music.
    p_music = df::ResourceManager::getInstance().getMusic("start music");
    playMusic();

    //Setup with settingsptr
    theSet = info;
}

// Play start music.
void GameStart::playMusic() {
    p_music->play();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(const df::Event *p_e) {
    df::GameManager &game_manager = df::GameManager::getInstance();

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::P: 			// play
            start();
            break;
        case df::Keyboard::Q:			// quit
            game_manager.setGameOver();
            break;
        default:
            break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

void GameStart::start() {

    if(theSet->type == 0)
    {
        new Host(theSet);        
    }
    else
    {
        //new Host(theSet);
        new Client(theSet);
    }



    // Setup heads-up display.


    /*df::ViewObject *p_vo = new df::ViewObject; // Count of nukes.
  p_vo->setLocation(df::TOP_LEFT);
  p_vo->setViewString("Nukes");
  p_vo->setValue(1);
  p_vo->setColor(df::YELLOW);*/

    // Pause start music.
    p_music->pause();

    // When game starts, become inactive.
    setActive(false);
}

// Override default draw so as not to display "value".
void GameStart::draw() {
    df::Object::draw();
}
