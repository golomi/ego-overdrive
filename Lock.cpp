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
 * File:   Lock.cpp
 * Author: thomas
 * 
 * Created on 3. Februar 2022, 23:38
 */

#include "Lock.h"
#include "Door.h"

Lock::Lock(int x, int y, int type) : NonDukeObject(x, y, 1, 1, type) {
}

void Lock::openDoor(int key, std::list<MapObject*> &objectVector) {
    // TODO: workaround method
    int door;

    switch (key) {
        case INVENTORY_RED_KEY:
            door = 0x4C;
            break;
        case INVENTORY_GREEN_KEY:
            door = 0x4D;
            break;
        case INVENTORY_BLUE_KEY:
            door = 0x4E;
            break;
        case INVENTORY_PURPLE_KEY:
            door = 0x4F;
            break;
        default:
            // no key
            return;
    }

    for (std::list<MapObject*>::iterator it = objectVector.begin(); it != objectVector.end(); ++it) {
        MapObject *object = *it;
        if (object->getType() == door) {
            ((Door*)object)->open();
        }
    }
}

void Lock::action(Duke *duke, std::list<MapObject*> &objectVector, MapObjectNotifier *notifier) {
    switch (getType()) {
        case 0x48:
            if (notifier->request(this, AllowRedDoorOpen, nullptr) /*duke->getProperties()->getInventory() & INVENTORY_RED_KEY*/) {
                openDoor(INVENTORY_RED_KEY, objectVector);
            }
            break;
        case 0x49:
            if (notifier->request(this, AllowGreenDoorOpen, nullptr) /*duke->getProperties()->getInventory() & INVENTORY_GREEN_KEY*/) {
                openDoor(INVENTORY_GREEN_KEY, objectVector);
            }
            break;
        case 0x4A:
            if (notifier->request(this, AllowBlueDoorOpen, nullptr) /*duke->getProperties()->getInventory() & INVENTORY_BLUE_KEY*/) {
                openDoor(INVENTORY_BLUE_KEY, objectVector);
            }
            break;
        case 0x4B:
            if (notifier->request(this, AllowPurpleDoorOpen, nullptr) /*duke->getProperties()->getInventory() & INVENTORY_PURPLE_KEY*/) {
                openDoor(INVENTORY_PURPLE_KEY, objectVector);
            }
            break;
    }
}