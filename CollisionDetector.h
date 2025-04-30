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
 * File:   CollisionDetector.h
 * Author: thomas
 *
 * Created on 8. November 2021, 21:35
 */

#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include <vector>
#include <list>

#include "Duke.h"
#include "NonDukeObject.h"
#include "Bullet.h"

class CollisionDetector {
public:
    CollisionDetector();
    CollisionDetector(const CollisionDetector& orig);
    virtual ~CollisionDetector();
    static bool executeTouch(Duke *duke, std::list<MapObject*> &objectVector);
    static bool executeAction(Duke *duke, int type, std::list<MapObject*> &objectVector, MapObjectNotifier *listener);
    static bool executeHit(Bullet *bullet, std::list<MapObject*> &objectVector);
    static bool executeStandon(Duke *duke, std::list<MapObject*> &objectVector);
private:

};

#endif /* COLLISIONDETECTOR_H */

