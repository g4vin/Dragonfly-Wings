//
// Bullet.cpp
//

// Engine includes.
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"

// Game includes.
#include "Bullet.h"
#include "Saucer.h"

#include "NetworkManager.h"
#include <iostream>
#include <sstream>

Bullet::Bullet(df::Position hero_pos) {

    // Link to "bullet" sprite.#include "NetworkManager.h"
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::Sprite *p_temp_sprite = resource_manager.getSprite("bullet");
    if (!p_temp_sprite) {
        df::LogManager &log_manager = df::LogManager::getInstance();
        log_manager.writeLog("Bullet::Bullet(): Warning! Sprite '%s' not found",
                             "bullet");
    } else {
        setSprite(p_temp_sprite);
        setSpriteSlowdown(5);
    }

    // Set other object properties.
    setType("Bullet");
    setXVelocity(1); // Move 1 space right every game loop.

    // Set starting location, based on hero's position passed in.
    df::Position pos(hero_pos.getX()+3, hero_pos.getY());
    setPosition(pos);
}

// Handle event.
// Return 0 if ignored, else 1.
int Bullet::eventHandler(const df::Event *p_e) {

    if (p_e->getType() == df::OUT_EVENT) {
        out();
        return 1;
    }

    if (p_e->getType() == df::COLLISION_EVENT) {

        const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);

        hit(p_collision_event);

        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

// If Bullet moves outside world, mark self for deletion.
void Bullet::out() {
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    world_manager.markForDelete(this);
}

// If Bullet hits Saucer, mark Saucer and Bullet for deletion.
void Bullet::hit(const df::EventCollision *p_collision_event) {
    if(this->getType() == "Bullet")
    {
        std::ostringstream os, ss, bs , ds;
        df::NetworkManager &network_manager = df::NetworkManager::getInstance();

        //delete bullet and saucer over network
        //os << "DELETEB,id:" << (this->getId()) << ",";

        os << "DELETEID,id:" << (p_collision_event->getObject1()->getId()) << ",";
        std::string tempMessage = os.str();

        bs << "DELETEID,id:" << (p_collision_event->getObject2()->getId()) << ",";
        std::string otherMes = bs.str();

        ss << "02" << tempMessage.length() << tempMessage << otherMes.length() << otherMes;
        std::string message = ss.str();
        network_manager.send2((void *)message.c_str(), message.length());



        //delete locally
        df::WorldManager &world_manager = df::WorldManager::getInstance();
        world_manager.markForDelete(p_collision_event->getObject1());
        world_manager.markForDelete(p_collision_event->getObject2());
    }
}
