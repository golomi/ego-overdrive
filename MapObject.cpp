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
 * File:   MapObject.cpp
 * Author: thomas
 * 
 * Created on 30. September 2021, 23:59
 */

#include "MapObject.h"

Map *MapObject::map = NULL;

MapObject::MapObject() {
}

MapObject::MapObject(int x, int y, int w, int h, int type) : type(type) /*x(x), y(y) */ {
    setTileX(x);
    setTileY(y);
    setTileWidth(w);
    setTileHeight(h);
}

// TODO: Copy constructor? Seems to be incomplete

MapObject::MapObject(MapObject *orig) {
    setTileX(orig->getTileX());
    setTileY(orig->getTileY());
}

MapObject::~MapObject() {
}

void MapObject::setTileY(int y) {
    setY(y * TILE_HEIGHT);
}

int MapObject::getTileY() const {
    return (getY() / TILE_HEIGHT);
}

void MapObject::setTileX(int x) {
    setX(x * TILE_WIDTH);

}

int MapObject::getTileX() const {
    return (getX() / TILE_WIDTH);
}

void MapObject::setY(int y) {
    this->y = y;
}

int MapObject::getY() const {
    return y;
}

void MapObject::setX(int x) {
    this->x = x;
}

int MapObject::getX() const {
    return x;
}

void MapObject::setTileWidth(int w) {
    tileWidth = w;
}

int MapObject::getTileWidth() {
    return (tileWidth);
}

void MapObject::setTileHeight(int h) {
    tileHeight = h;
}

int MapObject::getTileHeight() {
    return (tileHeight);
}

int MapObject::getWidth() {
    return (getTileWidth() * TILE_WIDTH);
}

int MapObject::getHeight() {
    return (getTileHeight() * TILE_HEIGHT);
}

void MapObject::setMap(Map *map) {
    MapObject::map = map;
}

Map *MapObject::getMap() {
    return (map);
}

void MapObject::remove() {

    toBeRemoved = true;
}

bool MapObject::shouldBeRemoved() {
    return toBeRemoved;
}

//void MapObject::touch(MapObject *duke) 

void MapObject::touch(Duke *duke, std::list<MapObject*> &objectVector) {

}

bool MapObject::isSolid() {
    return (false);
}

void MapObject::hit(int h) {

}

bool MapObject::canHit() {
    return (false);

}

bool MapObject::isGroundClose() {
    // TODO: replace by a general fall rate or an object fall rate F
    return (getMap()->isTileSolid(getTileX(), (getTileY() + DUKE_FALL_RATE) + 1));
}

bool MapObject::isGrounded() {

    return (getMap()->isTileSolid(getTileX(), getTileY() + 1));
}

bool MapObject::isObstacleAhead(int speed) {
    // TODO: currently detection of obstacles is designed for size of duke and not for other objects
    if (viewDirection == DIRECTION_RIGHT) {
        return (getMap()->isTileSolid((x + 8 + speed) / TILE_WIDTH, y / TILE_HEIGHT) ||
                getMap()->isTileSolid((x + 8 + speed) / TILE_WIDTH, y / TILE_HEIGHT - 1) ||
                getMap()->isTileSolid((x + 8 + speed) / TILE_WIDTH, (y + TILE_HEIGHT - 4) / TILE_HEIGHT));
    } else if (viewDirection == DIRECTION_LEFT) {
        return (getMap()->isTileSolid((x - 8 - speed) / TILE_WIDTH, y / TILE_HEIGHT) ||
                getMap()->isTileSolid((x - 8 - speed) / TILE_WIDTH, y / TILE_HEIGHT - 1) ||
                getMap()->isTileSolid((x - 8 - speed) / TILE_WIDTH, (y + TILE_HEIGHT - 4) / TILE_HEIGHT));
    }

    return (false);
}

bool MapObject::isObstacleAhead() {
    return (isObstacleAhead(8));
}

bool MapObject::isEdgeAhead(int speed) {
    if (viewDirection == DIRECTION_RIGHT) {
        return (!getMap()->isTileSolid((getX() + speed) / TILE_WIDTH, getTileY() + 1));
        //return (!getMap()->isTileSolid(getTileX() + 1, getTileY() + 1));
    } else if (viewDirection == DIRECTION_LEFT) {
        return (!getMap()->isTileSolid((getX() - speed) / TILE_WIDTH, getTileY() + 1));
        //return (!getMap()->isTileSolid(getTileX() - 1, getTileY() + 1));
    }
    return (false);
}

bool MapObject::isEdgeAhead() {
    return (isEdgeAhead(8));
}

int MapObject::getViewDirection() {
    return (viewDirection);
}

void MapObject::setViewDirection(int viewDirection) {
    this->viewDirection = viewDirection;
}

/**
 * Checks if object is in viewport or directly bordering
 * @param viewPort
 * @return true, if object is in viewport or directly bordering
 */
bool MapObject::isInView(DukeViewPort *viewPort) {
    //TODO: check if object is in viewport or directly bordering
    return (true);
}

void MapObject::turnViewDirection() {
    viewDirection *= -1;
}

void MapObject::updateSolidMap() {
    //intentionally blank, as this is the default behavior
}

void MapObject::action(Duke *duke, std::list<MapObject*> &objectVector, MapObjectNotifier *notifier) {
    //intentionally blank, as this is the default behavior
}

void MapObject::action(Duke *duke, int type, std::list<MapObject*> &objectVector, MapObjectNotifier *notifier) {
    // TODO: dirty hack to keep compatibility with old 3 argument method
    if (type == 1) {
        action(duke, objectVector, notifier);
    }
}

void MapObject::standon(Duke *duke) {
    //intentionally blank, as this is the default behavior
}