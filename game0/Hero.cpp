//Hero.cpp
#include "Bullet.h"
#include "Hero.h"
#include "EventStep.h"
#include "EventView.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"

Hero::Hero()
{
        move_slowdown = 2;
        move_countdown = move_slowdown;
        fire_slowdown = 15;
        fire_countdown = fire_slowdown;
        df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
        df::LogManager &log_manager = df::LogManager::getInstance();
        df::Sprite *p_temp_sprite;
        p_temp_sprite = resource_manager.getSprite("ship");
        if (!p_temp_sprite) {
                log_manager.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", 
                                "ship");
        } else {
                setSprite(p_temp_sprite);
                setSpriteSlowdown(3);  // 1/3 speed animation.
                setTransparency();       // Transparent sprite.
        }
       
        registerInterest(df::MOUSE_EVENT);
        registerInterest(df::KEYBOARD_EVENT);
        registerInterest(df::STEP_EVENT);

        setType("Hero");
        df::WorldManager &world_manager = df::WorldManager::getInstance();
        df::Position pos(7, world_manager.getBoundary().getVertical()/2);
        setPosition(pos);

        p_reticle = new Reticle();
        p_reticle->draw();
}

int Hero::eventHandler(const df::Event *p_e) {
        if (p_e->getType() == df::KEYBOARD_EVENT) {
                const df::EventKeyboard *p_keyboard_event = 
                        dynamic_cast <const df::EventKeyboard *> (p_e);
                kbd(p_keyboard_event);
                return 1;
        }

        if (p_e->getType() == df::STEP_EVENT) {
                step();
                return 1;
        }

        if (p_e->getType() == df::MOUSE_EVENT) {
                const df::EventMouse *p_mouse_event = 
                        dynamic_cast <const df::EventMouse *> (p_e);
                mouse(p_mouse_event);
                return 1;
        }

        return 0;
}

void Hero::kbd(const df::EventKeyboard *p_keyboard_event) {

        switch(p_keyboard_event->getKey()) {
                case df::Keyboard::Q:           // quit
                        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
                                df::GameManager &game_manager = df::GameManager::getInstance();
                                game_manager.setGameOver();
                        }
                        break;
                case df::Keyboard::W:           // up
                        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
                                move(-1);
                        break;
                case df::Keyboard::S:         // down
                        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
                                move(+1);
                        break;     

        }
}

void Hero::move(int dy)
{
        if (move_countdown > 0)
                return;
        move_countdown = move_slowdown;

        df::Position new_pos(getPosition().getX(), getPosition().getY() + dy);
        df::WorldManager &world_manager = df::WorldManager::getInstance();
        if ((new_pos.getY() > 3) && 
                        (new_pos.getY() < world_manager.getBoundary().getVertical()-1))
                world_manager.moveObject(this, new_pos);
}

void Hero::step()
{
        move_countdown--;
        if (move_countdown < 0)
                move_countdown = 0;

        fire_countdown--;
        if (fire_countdown < 0)
                fire_countdown = 0;
}

void Hero::fire(df::Position target)
{
        if (fire_countdown > 0)
                return;
        fire_countdown = fire_slowdown;

        Bullet *p = new Bullet(getPosition());
        p->setYVelocity((float) (target.getY() - getPosition().getY()) /
                        (float) (target.getX() - getPosition().getX()));

}

void Hero::mouse(const df::EventMouse *p_mouse_event) {
        df::LogManager &log_manager = df::LogManager::getInstance();

        if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
                        (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
                fire(p_mouse_event->getMousePosition());
}

