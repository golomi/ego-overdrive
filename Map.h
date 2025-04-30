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
 * File:   Map.h
 * Author: thomas
 *
 * Created on 12. September 2021, 22:34
 */

#ifndef MAP_H
#define MAP_H


#include <SDL2/SDL.h>

#include "DukeDefinitions.h"

/**
 * Encapsulates a level, called in Duke Nukum world, according to the file
 * names. 
 */
class Map {
private:
    //    static const int MAP_WIDTH = 128;
    //    static const int MAP_HEIGHT = 90;
    //    static const int MAP_TILE_BYTE_SIZE = 2;
    //    static const int MAP_BYTE_SIZE = MAP_WIDTH * MAP_HEIGHT * MAP_TILE_BYTE_SIZE;

    unsigned short int rawMap[MAP_WIDTH*MAP_HEIGHT];
    unsigned short int *map;
    unsigned char tempSolidMap[MAP_WIDTH*MAP_HEIGHT];

    //    int mapShiftX = 10 * TILE_WIDTH;
    //    int mapShiftY = 22 * TILE_HEIGHT;

    int frameCounter = 0;
    int tick = 0, oldTick = 0;
    bool isNewTick = true;
public:

    Map();
    Map(const Map& orig);
    virtual ~Map();

    bool isTileSolid(int x, int y);
    void draw(SDL_Renderer* renderer, int x, int y, int width, int height, int shiftX, int shiftY);

    unsigned short int *getMap();

    void setMap(unsigned short int *map);

    unsigned short int getTile(int x, int y);

    void flushTempSolid();

    void setTempSolid(int x, int y);

};

#endif /* MAP_H */

