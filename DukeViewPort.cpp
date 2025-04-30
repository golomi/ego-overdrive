/*
 * Copyright (C) 2022 thomas
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
 * File:   ViewPort.cpp
 * Author: thomas
 * 
 * Created on 23. Januar 2022, 10:57
 */

#include "DukeViewPort.h"

DukeViewPort::DukeViewPort(/*int shiftX, int shiftY*/) {
    setShiftX(10 * TILE_WIDTH);
    setShiftY(22 * TILE_HEIGHT);
}

int DukeViewPort::getShiftX() {
    return shiftX;
}

void DukeViewPort::setShiftX(int shiftX) {
    if (shiftX < 0) {
        this->shiftX = 0;
    } else if (shiftX > MAX_SHIFT_X) {
        this->shiftX = MAX_SHIFT_X;
    } else {
        this->shiftX = shiftX;
    }
}

void DukeViewPort::addShiftX(int deltaX) {
    setShiftX(getShiftX() + deltaX);
}

int DukeViewPort::getShiftY() {
    return shiftY;
}

void DukeViewPort::setShiftY(int shiftY) {
    if (shiftY < 0) {
        this->shiftY = 0;
    } else if (shiftY > MAX_SHIFT_Y) {
        this->shiftY = MAX_SHIFT_Y;
    } else {
        this->shiftY = shiftY;
    }
}

void DukeViewPort::addShiftY(int deltaY) {
    setShiftY(getShiftY() + deltaY);
}