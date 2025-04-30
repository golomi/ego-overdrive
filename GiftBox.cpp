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
 * File:   GiftBox.cpp
 * Author: thomas
 * 
 * Created on 26. April 2022, 22:41
 */

#include "GiftBox.h"

#include "InventoryItem.h"
#include "DebugOutput.h"

//GiftBox::GiftBox(int x, int y) : NonDukeObject(x, y, 1, 1) {
//}

GiftBox::GiftBox(int x, int y, int type) : NonDukeObject(x, y, 1, 1, type) {
    DebugOutput::addLine("init GiftBox");
}

GiftBox::~GiftBox() {
}

void GiftBox::hit(int h) {
    NonDukeObject::hit(h);

}

NonDukeObject* GiftBox::createSuccessorObject() {
    switch (getType()) {
            //case 0x00: break;
        case 0x06: // shoe
            return (new InventoryItem(getTileX(), getTileY(), 0x5a));
            break;
        case 0x08: // claw
            return (new InventoryItem(getTileX(), getTileY(), 0x5b));
            break;
            //        case 0x0F:
            //            break;
            //        case 0x12: break;
            //        case 0x15: break;
            //        case 0x1d:
            //            return (new NonDukeObject(x, y, 0x50));
            //            break;
            //        case 0x1e: break;
            //        case 0x1f: break;
            //        case 0x18: break;
        case 0x20: // glove
            return (new InventoryItem(getTileX(), getTileY(), 0x5c));
            break;
            //        case 0x23: break;
            //        case 0x29: break;
            //        case 0x2d: break;
            //        case 0x2e: break;
            //            //case 0x33: break;
            //        case 0x37: break;
            //        case 0x38: break;
            //        case 0x39: break;
            //        case 0x3a: break;
        default:
            DebugOutput::addLine("The program sequence should actually never pass by here");
            return (NULL);
            break;
    }
}