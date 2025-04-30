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
 * File:   Key.cpp
 * Author: thomas
 * 
 * Created on 1. Februar 2022, 23:14
 */

#include "InventoryItem.h"

#include "DebugOutput.h"

InventoryItem::InventoryItem(int x, int y, int type) : NonDukeObject(x, y, 1, 1, type) {
    DebugOutput::addLine("init InventoryItem\n");
}

InventoryItem::~InventoryItem() {
}

void InventoryItem::touch(Duke *duke, std::list<MapObject*> &objectVector) {
    switch (getType()) {
        case 0x44:
            duke->getProperties()->addInventory(INVENTORY_RED_KEY);
            break;
        case 0x45:
            duke->getProperties()->addInventory(INVENTORY_GREEN_KEY);
            break;
        case 0x46:
            duke->getProperties()->addInventory(INVENTORY_BLUE_KEY);
            break;
        case 0x47:
            duke->getProperties()->addInventory(INVENTORY_PURPLE_KEY);
            break;
        case 0x5a:
            duke->getProperties()->addInventory(INVENTORY_SHOE);
            break;
        case 0x5b:
            duke->getProperties()->addInventory(INVENTORY_CLAW);
            break;
        case 0x5c:
            duke->getProperties()->addInventory(INVENTORY_GLOVE);
            break;
        case 0x5d:
            duke->getProperties()->addInventory(INVENTORY_BOARD);
            break;

    }

    remove();
}
