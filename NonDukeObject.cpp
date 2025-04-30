/*
 * Copyright (C) 2021 Thomas Lenck
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 * File:   Object.cpp
 * Author: Thomas Lenck
 * 
 * Created on 16. Februar 2021, 00:09
 */

#include "NonDukeObject.h"
#include "DukeDrawSupport.h"
#include "ObjectFactory.h"




int *NonDukeObject::tick = NULL;


/**
    bool simpleObject;
    ObjectTextureFile objectTextureFile;
    unsigned short int objectTextureFileIndex;
    unsigned short int index;
    unsigned short int animCount;
    bool falling;
    bool movingOnGround;
    bool collectable;
    int injureTouch;
    int scoreCollect;
    bool canHit;
    int health;
    int tileWidth;
    int tileHeight;
    int successorType;
 */

ObjectTableType ObjectProperties::destroyableWall = {false, object, 2, 0, 1, false, false, false, false, 0, true, 1, 1, 1, 0};
ObjectTableType ObjectProperties::objectTableTypeDummy = {false, object, 2, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0};

const int ObjectProperties::OBJECT_MAX = 0x68;
ObjectTableType ObjectProperties::objectTable[OBJECT_MAX + 1] = {
    /*0x00 blue box with confetti*/
    {true, object, 2, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0x5f},
    /*0x01 elevator*/
    {true, object, 0, 5, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x02 conveyor left end, transporting to the left*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x03 conveyor right end, transporting to the left*/
    {true, object, 0, 0, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x04 conveyor left end, transporting to the right*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x05 conveyor right end, transporting to the right*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x06 grey box with shoe*/
    {true, object, 0, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0x5a},
    /*0x07 rocket*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x08 grey box with claw*/
    {true, object, 0, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0x5b},
    /*0x09 flamethrower right*/
    {true, object, 0, 24, 5, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x0A flamethrower left*/
    {true, object, 0, 29, 5, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x0B flying robot*/
    {true, anim, 0, 0, 1, false, false, false, 1, 0, true, 1, 1, 1, 0},
    /*0x0C huge jumping robot*/
    {true, anim, 0, 10, 1, false, false, false, 1, 0, true, 1, 2, 2, 0},
    /*0x0D moving canon*/
    {true, anim, 0, 34, 2, false, true, false, 1, 0, true, 1, 2, 1, 0},
    /*0x0E fire wheel*/
    {false, anim, 1, 0, 4, false, true, false, 1, 0, true, 1, 2, 2, 0},
    /*0x0F grey box with gun*/
    {true, object, 0, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0x5e},
    /*0x10 small robot*/
    {true, anim, 1, 32, 3, true, true, false, 1, 0, true, 1, 1, 1, 0},
    /*0x11 exit door*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 2, 2, 0},
    /*0x12 grey box with dynamite*/
    {true, object, 0, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0},
    /*0x13 worm out of balls*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x14 mirror/Ice?*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x15 red box with coke*/
    {true, object, 2, 1, 1, true, false, false, 0, 0, true, 1, 1, 1, 0x52},
    /*0x16 green alien left wall*/
    {true, anim, 2, 40, 4, false, false, false, 1, 0, true, 1, 1, 1, 0},
    /*0x17 green alien right wall*/
    {true, anim, 2, 44, 4, false, false, false, 1, 0, true, 1, 1, 1, 0},
    /*0x18 red box with chicken thigh*/
    {true, object, 2, 1, 1, true, false, false, 0, 0, true, 1, 1, 1, 0x51},
    /*0x19 dissolving ground*/
    {true, anim, 3, 0, 1, false, false, false, false, 0, false, 0, 4, 1, 0},
    /*0x1A Energy beam horizontal*/
    {true, object, 1, 0, 4, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x1B propeller?*/
    {false, object, 0, 0, 4, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x1C propeller*/
    {true, anim, 3, 12, 4, false, false, false, false, 0, false, 1, 1, 2, 0},
    /*0x1D blue box with football*/
    {true, object, 2, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0x50},
    /*0x1E blue box with joystick*/
    {true, object, 2, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0x54},
    /*0x1F blue box with DN disk*/
    {true, object, 2, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0x53},
    /*0x20 grey box glove*/
    {true, object, 0, 0, 1, false, false, false, false, 0, true, 1, 1, 1, 0x5c},
    /*0x21 energy beam verticale*/
    {false, object, 0, 0, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x22 helicopter*/
    {true, anim, 3, 20, 3, false, false, false, false, 0, true, 1, 2, 1, 0},
    /*0x23 grey box with balloon*/
    {true, object, 0, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0},
    /*0x24 camera*/
    {true, anim, 4, 8, 1, false, false, false, false, 0, true, 1, 1, 1, 0},
    /*0x25 broken steel beam*/
    {true, anim, 4, 11, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x26 Black cloud (looks like that)*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x27 broken concrete beam*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x28 Grilled window*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x29 grey box with bubbles*/
    {true, object, 0, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0x62},
    /*0x2A ACME sign*/
    {true, object, 1, 33, 1, false, false, false, true, 0, true, 1, 2, 1, 0},
    /*0x2B energy field*/
    {true, object, 1, 40, 5, false, false, false, 0xFFFF, 0, true, 10, 1, 1, 0},
    /*0x2C small sting*/
    {true, object, 1, 45, 1, false, false, false, 1, 0, false, 1, 1, 1, 0},
    /*0x2D blue box with flag*/
    {true, object, 2, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0x55},
    /*0x2E blue box with radio*/
    {true, object, 2, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0x56},
    /*0x2F teleporter*/
    {true, anim, 4, 20, 1, false, false, false, false, 0, false, 1, 3, 3, 0},
    /*0x30 Teleporter*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x31 red ball*/
    {true, anim, 4, 31, 1, false, false, false, 1, 0, false, 1, 1, 1, 0},
    /*0x32 duke's starting position*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x33 Grey box with board (PCB)*/
    {true, object, 0, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0x68},
    /*0x34 Board (PCB) lock*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x35 glove door opener*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x36 Steel beam for claw, extends to a bridge, when activated by glove*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x37 grey box with 'D'*/
    {true, object, 0, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0},
    /*0x38 grey box with 'U'*/
    {true, object, 0, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0},
    /*0x39 grey box with 'K'*/
    {true, object, 0, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0},
    /*0x3A grey box with 'E'*/
    {true, object, 0, 0, 1, true, false, false, false, 0, true, 1, 1, 1, 0},
    /*0x3B rabbit*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x3C running flame*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x3D grilled window transverse*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x3E window left side*/
    {true, anim, 5, 13, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x3F window right side*/
    {true, anim, 5, 14, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x40 note*/
    {true, object, 2, 23, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x41 screen with Dr Proton*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x42 Dr Proton (end boss) (seems to be the same as 0x43, possibly with more energy?)*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x43 Dr Proton (end boss)*/
    {false, object, 0, 0, 0, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x44 Red key*/
    {true, object, 2, 24, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x45 Green key*/
    {true, object, 2, 25, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x46 Blue key*/
    {true, object, 2, 26, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x47 Purple key*/
    {true, object, 2, 27, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x48 Red lock */
    {true, object, 2, 37, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x49 Green lock*/
    {true, object, 2, 38, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x4A Blue lock*/
    {true, object, 2, 39, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x4B Purple lock*/
    {true, object, 2, 40, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x4C red door*/
    {true, object, 2, 28, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x4D green door*/
    {true, object, 2, 28, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x4E blue door*/
    {true, object, 2, 28, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x4F purple door*/
    {true, object, 2, 28, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x50 Football*/
    {true, object, 1, 8, 1, true, false, true, false, 100, false, 1, 1, 1, 0},
    /*0x51 Chicken thighs*/
    {true, object, 0, 44, 1, true, false, true, false, 100, true, 1, 1, 1, 0x67},
    /*0x52 coke*/
    {true, anim, 2, 32, 4, true, false, true, 0, 0, true, 1, 1, 1, 0},
    /*0x53 DN floppy disc*/
    {true, object, 1, 10, 1, true, false, true, false, 100, false, 1, 1, 1, 0},
    /*0x54 Joystick*/
    {true, object, 1, 9, 1, true, false, true, false, 100, false, 1, 1, 1, 0},
    /*0x55 Flag*/
    {true, object, 1, 47, 3, true, false, true, false, 100, false, 1, 1, 1, 0},
    /*0x56 Radio*/
    {true, object, 2, 2, 3, true, false, true, false, 100, false, 1, 1, 1, 0},
    /*0x57 Ball (on the floor)*/
    {false, object, 0, 0, 0, true, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x58 Spike floor*/
    {true, object, 2, 48, 1, false, false, false, 1, 0, false, 1, 1, 1, 0},
    /*0x59 Spike ceiling*/
    {true, object, 2, 49, 1, false, false, false, 1, 0, false, 1, 1, 1, 0},
    /*0x5A not in use) INVENTORY_SHOE*/
    {true, object, 0, 10, 1, true, false, true, false, 0, false, 1, 1, 1, 0},
    /*0x5B not in use) INVENTORY_CLAW*/
    {true, object, 0, 19, 1, true, false, true, false, 0, false, 1, 1, 1, 0},
    /*0x5C not in use) INVENTORY_GLOVE*/
    {true, object, 1, 13, 1, true, false, true, false, 0, false, 1, 1, 1, 0},
    /*0x5D not in use) INVENTORY_BOARD*/
    {true, object, 1, 14, 1, true, false, true, false, 0, false, 1, 1, 1, 0},
    /*0x5E not in use) gun*/
    {true, object, 0, 44, 1, true, false, true, false, 0, false, 1, 1, 1, 0},
    /*0x5F not in use) confetti*/
    {true, object, 0, 1, 1, true, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x60 not in use) dynamite*/
    {true, anim, 2, 17, 1, true, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x61 not in use) balloon*/
    {true, object, 0, 44, 1, true, false, false, false, 0, false, 1, 1, 1, 0},
    /*0x62 not in use) bubbles*/
    {true, object, 1, 24, 9, true, false, true, 0, 0, false, 1, 1, 1, 0},
    /*0x63 not in use) 'D'*/
    {true, object, 2, 18, 1, true, false, true, false, 0, false, 1, 1, 1, 0},
    /*0x64 not in use) 'U'*/
    {true, object, 2, 19, 1, true, false, true, false, 0, false, 1, 1, 1, 0},
    /*0x65 not in use) 'K'*/
    {true, object, 2, 20, 1, true, false, true, false, 0, false, 1, 1, 1, 0},
    /*0x66 not in use) 'E'*/
    {true, object, 2, 21, 1, true, false, true, false, 0, false, 1, 1, 1, 0},
    /*0x67 not in use) double chicken thigh*/
    {true, object, 0, 45, 1, true, false, true, 0, 100, false, 1, 1, 1, 0},
    /*0x68 Board (PCB)*/
    {true, object, 1, 14, 1, false, false, false, false, 0, false, 1, 1, 1, 0},
};


DukeTextureContainer NonDukeObject::textureContainer;

//NonDukeObject::NonDukeObject(int x, int y, int type) : MapObject(x, y, 1, 1, type) {
//    health = getHealth();
//    setTileWidth(getTileWidth());
//    setTileHeight(getTileHeight());
//}

NonDukeObject::NonDukeObject(int x, int y, int w, int h, int type) : MapObject(x, y, w, h, type) {
    health = getHealth();
}

//NonDukeObject::~NonDukeObject() {
//}

void NonDukeObject::touch(Duke *duke, std::list<MapObject*> &objectVector) {
    // TODO: deside touch action to Duke: DO_NOTHING, HURT, HEAL, KILL, 
    // COLLECT_INVENTORY, COLLECT_SCORE, EXIT


    if (getInjureTouch() > 0) {
        duke->hit(getInjureTouch());
    }

    if (isCollectable() == true) {
        collect(duke);
        remove();
    }
}

void NonDukeObject::collect(Duke * duke) {
    duke->getProperties()->addScore(getScoreCollect());
}

void NonDukeObject::draw(Canvas *canvas, DukeTextureContainer * textures) {

    static SDL_Rect sourceRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    static SDL_Rect destRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};


    destRect.x = getX(); //getTileX() * 16;
    destRect.y = getY(); //getTileY() * 16;

    SDL_Texture *texture = NULL;

    if (isSimpleObject() == true) {
        int speed = 1;
        switch (getType()) {
            case 0x52:
                speed = 8;
                break;
            default:
                break;
        }
        if (getObjectTextureFile() == object) {
            texture = textureContainer.getTexture(25 + getObjectTextureFileIndex());
        } else if (getObjectTextureFile() == anim) {
            texture = textureContainer.getTexture(3 + getObjectTextureFileIndex());
        }

        if (getType() == 0x24) {
            DukeDrawSupport::drawTile(canvas, texture, 16 * (getIndex() + getViewDirection() + 1), getTileX() * TILE_WIDTH, getTileY() * TILE_HEIGHT);
        } else {
            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + ((getTick() / speed) % getAnimCount()) * getTileWidth() * getTileHeight()),
                    getTileWidth(), getTileHeight(), getX(), getY());
        }


    } else {

        texture = textureContainer.getTexture(3 + 1);
        sourceRect = {0, 16 * (43 + getTick() % 3), 16, 16};

        if (texture != NULL) {
            canvas->draw(texture, &sourceRect, &destRect);
        }
    }


}

void NonDukeObject::update(UpdateContext * updateContext) {

    if (isGrounded()) {
        if (isMovingOnGround()) {
            if (isObstacleAhead(MOVE_SPEED) || isEdgeAhead(/*MOVE_SPEED*/)) {
                turnViewDirection();
            } else {

                setX(getX() + MOVE_SPEED * getViewDirection());
            }
        }
    } else {

        //  if (!isGroundClose()) {
        if (isFalling())
            y += DUKE_FALL_RATE; // TODO: replace by a general fall rate or an object fall rate
        //   } else {
        // y = y - y % TILE_HEIGHT + TILE_HEIGHT; //(int)(y / TILE_HEIGHT) * TILE_HEIGHT + 1;
        //  }
    }
}

void NonDukeObject::standon(Duke * duke) {
    dukeStandsOn = true;
}

void NonDukeObject::clearStandon() {
    dukeStandsOn = false;
}

/**
 * Opens a door
 */
void NonDukeObject::open() {

}

void NonDukeObject::hit(int h) {
    health--;

    if (health <= 0) {
        remove();
    }
}

bool NonDukeObject::canHit() {
    return (getCanHit() && getHealth() > 0);
}

void NonDukeObject::setHealth(int health) {
    this->health = health;
}

int NonDukeObject::getHealth() const {
    return health;
}

NonDukeObject * NonDukeObject::getSuccessorObject() {
    return createSuccessorObject();
}

NonDukeObject * NonDukeObject::createSuccessorObject() {
    int successorType = getSuccessorType();

    if (successorType != 0) {
        return (ObjectFactory::createObject(getTileX(), getTileY(), successorType + 0x3000));
    } else {
        return (NULL);
    }

}

bool NonDukeObject::isSimpleObject() {
    return (ObjectProperties::isSimpleObject(getType()));
}

ObjectTextureFile NonDukeObject::getObjectTextureFile() {
    return (ObjectProperties::getObjectTextureFile(getType()));
}

unsigned short int NonDukeObject::getObjectTextureFileIndex() {
    return (ObjectProperties::getObjectTextureFileIndex(getType()));
}

int NonDukeObject::getIndex() {
    return (ObjectProperties::getIndex(getType()));
}

unsigned short int NonDukeObject::getAnimCount() {
    return (ObjectProperties::getAnimCount(getType()));
}

bool NonDukeObject::isFalling() {
    return (ObjectProperties::isFalling(getType()));
}

bool NonDukeObject::isMovingOnGround() {
    return (ObjectProperties::isMovingOnGround(getType()));
}

bool NonDukeObject::isCollectable() {
    return (ObjectProperties::isCollectable(getType()));
}

int NonDukeObject::getInjureTouch() {
    return (ObjectProperties::getInjureTouch(getType()));
}

int NonDukeObject::getScoreCollect() {
    return (ObjectProperties::getScoreCollect(getType()));
}

bool NonDukeObject::getCanHit() {
    return (ObjectProperties::getCanHit(getType()));
}

int NonDukeObject::getHealth() {
    return (ObjectProperties::getHealth(getType()));
}

int NonDukeObject::getTileWidth() {
    return (ObjectProperties::getTileWidth(getType()));
}

int NonDukeObject::getTileHeight() {
    return (ObjectProperties::getTileHeight(getType()));
}

int NonDukeObject::getSuccessorType() {
    return (ObjectProperties::getSuccessorType(getType()));
}

