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
 * File:   MapLoader.h
 * Author: thomas
 *
 * Created on 8. November 2021, 21:13
 */

#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <vector>
#include <list>

#include "Map.h"
#include "Duke.h"
#include "NonDukeObject.h"
#include "DukeDefinitions.h"

struct ConsistencyCounters {
    int startPosition = 0;
    int teleporter = 0;
    int exitDoor = 0;
    int redKey = 0;
    int greenKey = 0;
    int blueKey = 0;
    int purpleKey = 0;
    int redLock = 0;
    int greenLock = 0;
    int blueLock = 0;
    int purpleLock = 0;
    int redDoor = 0;
    int greenDoor = 0;
    int blueDoor = 0;
    int purpleDoor = 0;
};

class MapLoadException {
};

class MapNotFoundException : public MapLoadException {
};

class MapCorruptException : public MapLoadException {
};

class MapInconsistendException : public MapLoadException {
};

class MapUnknownTileException : public MapLoadException {
};

class MapLoader {
private:
//    static NonDukeObject* createObject(int x, int y, int tile);
    static unsigned short int findSubstitutePart(int x, int y, unsigned short int *mapData);
public:
    MapLoader();
    MapLoader(const MapLoader& orig);
    virtual ~MapLoader();
    static void load(std::string fileName, Map *map, Duke *duke, std::list<MapObject*> &objectVector, unsigned short int *rawMap);
};

#endif /* MAPLOADER_H */

