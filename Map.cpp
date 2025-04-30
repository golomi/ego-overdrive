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
 * File:   Map.cpp
 * Author: thomas
 * 
 * Created on 12. September 2021, 22:34
 */

#include "Map.h"

Map::Map() {

    map = new unsigned short int[MAP_WIDTH * MAP_HEIGHT];
}

Map::Map(const Map& orig) {
}

Map::~Map() {
}

bool Map::isTileSolid(int x, int y) {
    unsigned short int tile = 0;
    bool tempSolid = false;
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        tile = map[x + y * MAP_WIDTH];
        tempSolid = tempSolidMap[x + y * MAP_WIDTH] > 0;
    }

    // TODO: temp. solution, as 0x1800 is the destryable stone
    if (tile == 0x1800) {
        return (false);
    }

    return ((tile >= 0x1800 && tile <= 0x2fff )|| tempSolid == true);
}

unsigned short int *Map::getMap() {
    return map;
}

void Map::setMap(unsigned short int *map) {
    if (this->map != nullptr) {
        delete this->map;
    }
    this->map = map;
}

unsigned short int Map::getTile(int x, int y) {
    return (map[x + y * MAP_WIDTH]);
}

void Map::flushTempSolid() {
    memset(tempSolidMap, 0, sizeof (tempSolidMap));
}

void Map::setTempSolid(int x, int y) {
    tempSolidMap[y * MAP_WIDTH + x] = 1;
}