/*
 * Copyright (C) 2021 thomas
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
 * File:   MapObject.h
 * Author: thomas
 *
 * Created on 30. September 2021, 23:59
 */

#ifndef MAPOBJECT_H
#define MAPOBJECT_H


#include <list>

#include "Map.h"
#include "DukeViewPort.h"
#include "DukeGameObject.h"
#include "DukeTextureContainer.h"
#include "UpdateContext.h"


class Duke;

const int DIRECTION_RIGHT = 1;
const int DIRECTION_LEFT = -1;
const int DIRECTION_UP = -1;
const int DIRECTION_DOWN = 1;

class MapObject;

enum Action {
    FinishedWorld, DukeDied
};

enum Request {
    AllowRedDoorOpen, AllowGreenDoorOpen, AllowBlueDoorOpen, AllowPurpleDoorOpen
};

class MapObjectNotifier {
public:
    virtual void action(MapObject *object, Action action, void *parameter) = 0;
    virtual bool request(MapObject *object, Request request, void *parameter) = 0;
};

class MapObject : public DukeGameObject {
private:
    int type = 0;

    static Map *map;

    bool toBeRemoved = false;
    int viewDirection = DIRECTION_RIGHT;

    int tileWidth, tileHeight;

protected:
    void remove();
    int x, y;


public:
    MapObject();
    MapObject(int x, int y, int w, int h, int type);

    /**
     * Constructor which clones the basic paramters from orig
     * @param orig
     */
    MapObject(MapObject *orig);
    virtual ~MapObject();


    /**
     * Set x position by tile position
     * @return 
     */
    void setTileX(int x);

    /**
     * Determines the x position in the grid of the tile size, 
     * i.e. actual position divided by tile size
     * @return the x position (in the grid of the tile size)
     */
    int getTileX() const;

    /**
     * Set y position by tile position
     * @param y
     */
    void setTileY(int y);

    /**
     * Determines the y position in the grid of the tile size, 
     * i.e. actual position divided by tile size
     * @return the y position (in the grid of the tile size)
     */
    int getTileY() const;



    void setY(int y);
    int getY() const;
    void setX(int x);
    int getX() const;

    void addX(int dx) {
        this->x += dx;
    }

    void addY(int dy) {
        this->y += dy;
    }


    void setTileWidth(int w);
    virtual int getTileWidth();

    void setTileHeight(int h);
    virtual int getTileHeight();
    
    int getWidth();
    int getHeight();

    static void setMap(Map *map);
    Map *getMap();

    /**
     * Called if dukes touches the object
     * @param duke
     */
    //virtual void touch(MapObject *duke);
    virtual void touch(Duke *duke, std::list<MapObject*> &objectVector);

    /**
     * Can Duke or another object stand on it?
     * @return true if the object is solit, false if not
     */
    virtual bool isSolid();

    /**
     * hit by the beam/projectile of the weapon
     * @param h for future use
     */
    virtual void hit(int h);

    /**
     * Determines if an object can be hit by a projectile 
     * @return true if the object can be hit, false if it is transparent for
     * projectiles
     */
    virtual bool canHit();

    /**
     * checkes if the object is destroyed, so it can be removed
     * @return 
     */
    virtual bool shouldBeRemoved();

    /**
     * is ground closer than one tile, i.e. < 16 pixels
     * @return true if the ground ist close, false if not
     */
    virtual bool isGroundClose();

    /**
     * does the object touches the ground
     * @return 
     */
    virtual bool isGrounded();

    /**
     * is something near in view direction, the object will touch, if it moves 
     * foreward
     * @param speed The speed of the object in pixels/cycle
     * @return 
     */
    virtual bool isObstacleAhead(int speed);

    /**
     * is something near in view direction, the object will touch, if it moves 
     * foreward with a standard speed of 8;
     * @return 
     */
    virtual bool isObstacleAhead();

    /**
     * does the current way end close in move direction
     * @param speed the speed of the object in pixels/cycle
     * @return 
     */
    virtual bool isEdgeAhead(int speed);

    /**
     * does the current way end close in move direction
     * @return 
     */
    virtual bool isEdgeAhead();

    /**
     * get the view direction 
     * @return return the view direction: DIRECTION_LEFT or DIRECTION_RIGHT
     */
    int getViewDirection();

    /**
     * sets the view direction
     * @param viewDirection the view direction: DIRECTION_LEFT or DIRECTION_RIGHT
     */
    void setViewDirection(int viewDirection);

    /**
     * turns the view direction, i.e. DIRECTION_LEFT->DIRECTION_RIGHT and vice versa
     */
    virtual void turnViewDirection();

    /**
     * Checkes of the object is in the players view. This is relevant,
     * as in original DN, some objects are only moving if they are inside the 
     * view +/- one tile left/right and above/below
     * @param viewPort
     * @return true, if the object is inside the view of the player
     */
    virtual bool isInView(DukeViewPort *viewPort);

    /**
     * Updates the object, which means the object is doing anything it has to
     * do since the last frame
     */
    virtual void update(UpdateContext *updateContext) = 0;

    virtual void updateSolidMap();


    virtual void action(Duke *duke, std::list<MapObject*> &objectVector, MapObjectNotifier *notifier);

    /**
     * Performs action, e.g. use teleporter, key, ...
     * @param duke list with dukes
     * @param type
     * @param objectVector
     * @param notifier
     */
    virtual void action(Duke *duke, int type, std::list<MapObject*> &objectVector, MapObjectNotifier *notifier);



    virtual void standon(Duke *duke);

    inline int getType() const {
        return type;
    }
};

#endif /* MAPOBJECT_H */

