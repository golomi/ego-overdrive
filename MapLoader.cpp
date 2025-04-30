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
 * File:   MapLoader.cpp
 * Author: thomas
 * 
 * Created on 8. November 2021, 21:13
 */

#include "MapLoader.h"

#include "ObjectFactory.h"

MapLoader::MapLoader() {
}

MapLoader::MapLoader(const MapLoader& orig) {
}

MapLoader::~MapLoader() {
}

void MapLoader::load(std::string fileName, Map *map, Duke *duke, std::list<MapObject*> &objectVector, unsigned short int *rawMap) {

    FILE *file = fopen((const char*) fileName.c_str(), "rb");

    objectVector.clear();


    ConsistencyCounters consistency;

    if (file == NULL) {
        throw new MapNotFoundException();
        // TODO: remove printf
        printf("Error opening the map file");
        return;
    }

    // TODO: check for file size 
    unsigned short int *mapData = new unsigned short int[MAP_WIDTH * MAP_HEIGHT];
    map->setMap(mapData);

    if (fread(mapData, MAP_BYTE_SIZE, 1, file) != 1) {
        throw new MapCorruptException();
        // TODO: remove printf
        printf("Error while reading the map file");
        return;
    }

    memcpy(rawMap, mapData, MAP_WIDTH * MAP_HEIGHT * sizeof (unsigned short int));

    // TODO: check if map is consistent: 
    // 1 start position
    // 0-1 key of every color
    // 0-1 lock per key
    // 0 or 2 transporter stations
    // Enough space for oversize objects (objects with more than one tile size: exit door, big robot, helicopter)
    // ...

    // TODO: substitude fixed values by constants

    // Substitute objects with background
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            unsigned short int tile = mapData[x + y * MAP_WIDTH];

            if (tile == 0x1800) {
                // destroyable wall
                mapData[x + y * MAP_WIDTH] = 0x1800 - 0x20;
                NonDukeObject *object = ObjectFactory::createObject(x, y, tile);

                if (object != NULL) {
                    objectVector.push_back(object);
                }

            } else if (tile < 0x2fff) {

                // normal tile, nothing to substitude
            } else if (tile > 0x2fff && tile < 0x30ff) { //TODO: substitude 0x30ff by constante with real max value


                NonDukeObject *object = ObjectFactory::createObject(x, y, tile);
                // TODO: move actual object creation and handling of object vector to virtual method or listener class
                if (object != NULL) {
                    objectVector.push_back(object);
                }




                mapData[x + y * MAP_WIDTH] = findSubstitutePart(x, y, mapData);


                if (tile == MAP_OBJECT_DUKE_START) {
                    int dukePositionX = x*TILE_WIDTH;
                    int dukePositionY = y*TILE_HEIGHT;
                    duke->setX(dukePositionX);
                    duke->setY(dukePositionY);

                }
            } else {
                throw new MapUnknownTileException();
                // TODO: remove print
                printf("Unknown tile %X at %i, %i \n", tile, x, y);
            }
        }
    }
    fclose(file);
}

unsigned short int MapLoader::findSubstitutePart(int x, int y, unsigned short int *mapData) {
    unsigned short int tile = mapData[x + y * MAP_WIDTH];
    unsigned short int substitudeTile = 0xffff;

    SUBSTITUDE_TILE_DIRECTIONS searchDirection = ABOVE;
    if (tile - 0x3000 <= MAP_OBJECT_MAX) {
        searchDirection = substitudeTileDirection[tile - 0x3000];
    } else {
        // TODO: Throw exception
        printf("No substitude tile > %i + 0x3000: %i\n", MAP_OBJECT_MAX, tile - 0x3000);
    }

    if (searchDirection == NONE) {
        substitudeTile = 0;
    } else {

        if (searchDirection == ABOVE) {
            // search above
            for (int i = y - 1; i >= 0 && substitudeTile >= 0x2fff; i--) {
                substitudeTile = mapData[x + i * MAP_WIDTH];
            }

        } else if (searchDirection == RIGHT) {
            // substitution direction right does not seem to be relevant, except for doors
            for (int i = x + 1; i < MAP_WIDTH && substitudeTile >= 0x2fff; i++) {
                substitudeTile = (mapData[i + y * MAP_WIDTH]);
            }
        } else if (searchDirection == BELOW) {
            // search below
            for (int i = y + 1; i < MAP_HEIGHT && substitudeTile >= 0x2fff; i++) {
                substitudeTile = (mapData[x + i * MAP_WIDTH]);
            }
        } else if (searchDirection == LEFT) {
            // search left
            for (int i = x - 1; i >= 0 && substitudeTile >= 0x2fff; i--) {
                substitudeTile = (mapData[i + y * MAP_WIDTH]);
            }
        } else {
            // TODO: throw exception
            printf("There is no direction > 3\n");
            return (0xffff);
        }

        if (substitudeTile < 0x2fff) {
            return (substitudeTile);
        } else {
            printf("No substitude tile found (x,y, tile, diection) %i, %i, %X, %i\n", x, y, tile, searchDirection);
            return (0);
        }
    }
    return (substitudeTile);
}
