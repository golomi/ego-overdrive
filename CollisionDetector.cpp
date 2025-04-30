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
 * File:   CollisionDetector.cpp
 * Author: thomas
 * 
 * Created on 8. November 2021, 21:35
 */
#include <math.h>

#include "CollisionDetector.h"
#include "NonDukeObject.h"
#include "Duke.h"

CollisionDetector::CollisionDetector() {
}

CollisionDetector::CollisionDetector(const CollisionDetector& orig) {
}

CollisionDetector::~CollisionDetector() {
}

bool CollisionDetector::executeTouch(Duke *duke, std::list<MapObject*> &objectVector) {
    SDL_Rect r1, r2;
    for (std::list<MapObject*>::iterator it = objectVector.begin(); it != objectVector.end(); ++it) {
        MapObject *object = *it;


        r1.x = object->getX();
        r1.y = object->getY();
        r1.w = object->getTileWidth() * TILE_WIDTH;
        r1.h = object->getTileHeight() * TILE_HEIGHT;

        r2.x = duke->getX();
        r2.y = duke->getY() - TILE_HEIGHT;
        r2.w = TILE_WIDTH;
        r2.h = TILE_HEIGHT * 2;

        if (SDL_HasIntersection(&r1, &r2)) {
            object->touch(duke, objectVector);
        }

    }
    return (false);
}

bool CollisionDetector::executeAction(Duke *duke, int type, std::list<MapObject*> &objectVector, MapObjectNotifier *listener) {

    SDL_Rect r1, r2;

    for (std::list<MapObject*>::iterator it = objectVector.begin(); it != objectVector.end(); ++it) {
        MapObject *object = *it;

        r1.x = object->getX();
        r1.y = object->getY() - (object->getTileHeight() - 1) * TILE_HEIGHT;
        r1.w = object->getTileWidth() * TILE_WIDTH;
        r1.h = object->getTileHeight() * TILE_HEIGHT;

        r2.x = duke->getX();
        r2.y = duke->getY() - TILE_HEIGHT;
        r2.w = TILE_WIDTH;
        r2.h = TILE_HEIGHT * 3;

        if (SDL_HasIntersection(&r1, &r2)) {
            object->action(duke, type, objectVector, listener);
        }

    }
    return (false);
}

bool CollisionDetector::executeHit(Bullet *bullet, std::list<MapObject*> &objectVector) {

    for (std::list<MapObject*>::iterator it = objectVector.begin(); it != objectVector.end(); ++it) {
        MapObject *object = *it;

        // TODO: consider object size
        int ox = object->getTileX();
        int dx = bullet->getX();
        int oy = object->getTileY();
        int dy = bullet->getY();

        int distX = dx - ox * 16;
        int distY = dy - oy * 16;

        // TODO: maybe it's necessary to do some fine tuning on the distances
        if (distX > -16 && distX < 16 && distY > -16 && distY < 4) {
            if (object->canHit() == true) {
                object->hit(0);
                bullet->hit(0);
                return(true);
            }
        }
    }
    return (false);
}

bool hasIntersection(int x1, int l1, int x2, int l2) {
    // TODO: move method e.g. to DrawSupport 

    if ((x2 >= x1 && x2 < x1 + l1) ||(x2 + l2 > x1 && x2 + l2 <= x1 + l1 )|| (x2 <= x1 && x2 + l2 >= x1 + l1)) {
        return (true);
    } else {
        return (false);
    }
}

bool CollisionDetector::executeStandon(Duke *duke, std::list<MapObject*> &objectVector) {

    SDL_Rect objectPos, dukePos;

    for (std::list<MapObject*>::iterator it = objectVector.begin(); it != objectVector.end(); ++it) {
        MapObject *object = *it;

        objectPos.x = object->getX();
        objectPos.y = object->getY() - (object->getTileHeight() - 1) * TILE_HEIGHT;
        objectPos.w = object->getTileWidth() * TILE_WIDTH;
        objectPos.h = object->getTileHeight() * TILE_HEIGHT;

        dukePos.x = duke->getX();
        dukePos.y = duke->getY() - TILE_HEIGHT;
        dukePos.w = TILE_WIDTH;
        dukePos.h = TILE_HEIGHT * 2;



        if (dukePos.y + dukePos.h == objectPos.y && hasIntersection(objectPos.x, objectPos.w, dukePos.x, dukePos.w)) {
            object->standon(duke);
        }

    }
    return (false);
}