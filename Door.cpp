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
 * File:   Door.cpp
 * Author: thomas
 * 
 * Created on 3. Februar 2022, 23:58
 */

#include "Door.h"

Door::Door(int x, int y, int type) : NonDukeObject(x, y, 1, 1, type) {
}

void Door::open() {
    doorState = OPENED;
    openState = 0;
}

void Door::updateSolidMap() {
    if (doorState == CLOSED)
        getMap()->setTempSolid(getTileX(), getTileY());
}

void Door::update(UpdateContext *updateContext) {
    // TODO: open door slowly
    if (doorState == OPENED) {
        openState++;
    }

    if (doorState == OPENED && openState == 16)
        remove();

}