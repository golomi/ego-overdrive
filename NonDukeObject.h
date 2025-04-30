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

/*! 
 * File:   Object.h
 * Author: Thomas Lenck
 *
 * Created on 16. Februar 2021, 00:09
 */

#ifndef OBJECT_H
#define OBJECT_H


#include <list>

#include <SDL2/SDL.h>

#include "MapObject.h"
#include "DukeTextureContainer.h"
#include "Duke.h"
#include "DukeDefinitions.h"
#include "DebugOutput.h"

enum ObjectTextureFile {
    anim, object
};

struct ObjectTableType {
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
    //    int scoreHit;
    //    unsigned short int speed;
};

class ObjectProperties {
private:

    static ObjectTableType destroyableWall;
    static ObjectTableType objectTableTypeDummy;
    static const int OBJECT_MAX;
    static ObjectTableType objectTable[];

public:

    static ObjectTableType *getEntry(int type) {
        if (type == 0x1800) {
            return (&destroyableWall);
        } else if (type <= OBJECT_MAX) {
            return (&objectTable[type]);
        } else if (type >= 0x3000 && type <= OBJECT_MAX) {
            return (&objectTable[type - 0x3000]);
        } else {
            DebugOutput::addLine("Error: unknown Tile");
            return (&objectTableTypeDummy);
        }
    }

    static bool isSimpleObject(int type) {
        return (getEntry(type)->simpleObject);
    }

    static ObjectTextureFile getObjectTextureFile(int type) {
        return (getEntry(type)->objectTextureFile);
    }

    static unsigned short int getObjectTextureFileIndex(int type) {
        return (getEntry(type)->objectTextureFileIndex);
    }

    static int getIndex(int type) {
        return (getEntry(type)->index);
    }

    static unsigned short int getAnimCount(int type) {
        return (getEntry(type)->animCount);
    }

    static bool isFalling(int type) {
        return (getEntry(type)->falling);
    }

    static bool isMovingOnGround(int type) {
        return (getEntry(type)->movingOnGround);
    }

    static bool isCollectable(int type) {
        return (getEntry(type)->collectable);
    }

    static int getInjureTouch(int type) {
        return (getEntry(type)->injureTouch);
    }

    static int getScoreCollect(int type) {
        return (getEntry(type)->scoreCollect);
    }

    static bool getCanHit(int type) {
        return (getEntry(type)->canHit);
    }

    static int getHealth(int type) {
        return (getEntry(type)->health);
    }

    static int getTileWidth(int type) {
        return (getEntry(type)->tileWidth);
    }

    static int getTileHeight(int type) {
        return (getEntry(type)->tileHeight);
    }

    static int getSuccessorType(int type) {
        return (getEntry(type)->successorType);
    }
};

class NonDukeObject : public MapObject {
private:

    static int *tick;
    bool dukeStandsOn = false;
    int health;

public:
    static DukeTextureContainer textureContainer;

    static void setTick(int *tick) {
        NonDukeObject::tick = tick;
    }

    inline int getTick() {
        return (*tick);
    }

//    NonDukeObject(int x, int y, int type);
    NonDukeObject(int x, int y, int w, int h, int type);
//    virtual ~NonDukeObject();
    virtual void draw(Canvas *canvas, DukeTextureContainer *textures)  override;
    virtual void update(UpdateContext *updateContext)  override;

    virtual void touch(Duke *duke, std::list<MapObject*> &objectVector) override;


    virtual void standon(Duke *duke) override;
    virtual void clearStandon();

    virtual void open();

    void hit(int h) override;
    virtual void collect(Duke *duke);
    bool canHit() override;
    void setHealth(int health);
    int getHealth() const;


    virtual NonDukeObject* getSuccessorObject();
    virtual NonDukeObject* createSuccessorObject();


    bool isSimpleObject();
    ObjectTextureFile getObjectTextureFile();
    unsigned short int getObjectTextureFileIndex();
    int getIndex();
    unsigned short int getAnimCount();
    bool isFalling();
    bool isMovingOnGround();
    bool isCollectable();
    int getInjureTouch();
    int getScoreCollect();
    bool getCanHit();
    int getHealth();
    virtual int getTileWidth() override;
    virtual int getTileHeight() override;
    int getSuccessorType();
};


#endif /* OBJECT_H */

