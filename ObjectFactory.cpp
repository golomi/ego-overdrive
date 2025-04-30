/*
 * Copyright (C) 2024 thomas
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
 * File:   ObjectFactory.cpp
 * Author: thomas
 * 
 * Created on 17. Februar 2024, 00:59
 */

#include "ObjectFactory.h"


#include "Camera.h"
#include "InventoryItem.h"
#include "Lock.h"
#include "Door.h"
#include "ExitDoor.h"
#include "Powerup.h"
#include "GreenAlien.h"
#include "EnergyField.h"
#include "Elevator.h"
#include "DissolvingGround.h"
#include "DestroyableWall.h"
#include "GiftBox.h"
#include "Flamethrower.h"
#include "BouncingBall.h"
#include "AcmeSign.h"
#include "Dynamite.h"
#include "DebugOutput.h"

NonDukeObject* ObjectFactory::createObject(int x, int y, int tile) {

    
    printf("Add Object %x at %i, %i\n",tile, x, y);
    
    // TODO: generate objects
    switch (tile) {
        case 0x1800:
            return (new DestroyableWall(x, y, 0x1800));
            break;

            //        case 0x3000: // grey box with confetti
            //            break;

            //        case 0x3000:

            //        case 0x300F:

        case 0x3012:
            return (new Dynamite(x, y, 1, 1, tile - 0x3000));
            
            
            //return(NULL);
            break;

            //        case 0x3015:
            //        case 0x3018:
            //        case 0x301D:
            //        case 0x301E:
            //        case 0x301F:
        case 0x3006:
        case 0x3008:
        case 0x3020:
            //        case 0x3023:
            //        case 0x3029:
            //        case 0x302D:
            //        case 0x302E:
            //        case 0x3037:
            //        case 0x3038:
            //        case 0x3039:
            //        case 0x303A:
            return (new GiftBox(x, y, tile - 0x3000));
            break;

        case 0x3001: // elevator
            return (new Elevator(x, y, 1, 1, tile - 0x3000));
            break;
        case 0x3009: // flame thrower right
            return (new Flamethrower(x, y, tile - 0x3000));
            break;
        case 0x300A: // flame thrower left
            return (new Flamethrower(x, y, tile - 0x3000));
            break;
            //        case 0x300B: // flying robot
            //            break;
            //        case 0x300C: // big jumping robot
            //            break;
            //        case 0x300D: // moving canon
            //            break;
            //        case 0x300E: // fire wheel
            //            break;
            //        case 0x300F: 
            //            break;
        case 0x3011: // exit door
            return (new ExitDoor(x, y, tile - 0x3000));
            break;
        case 0x3016:
        case 0x3017:
            return (new GreenAlien(x, y, tile - 0x3000));
            break;
        case 0x3019:
            return (new DissolvingGround(x, y, tile - 0x3000));
            break;

        case 0x3024:
            return (new Camera(x, y, 0x24));
            break;
        case 0x302B:
            return (new EnergyField(x, y, tile - 0x3000));
            break;
        case 0x302A:
            return (new AcmeSign(x, y, 1, 1, tile - 0x3000));
            break;
        case 0x3031:
            return (new BouncingBall(x, y, 1, 1, tile - 0x3000));
            break;
        case 0x3032:
            // Duke start position
            return (NULL);
            break;
        case 0x3044:
        case 0x3045:
        case 0x3046:
        case 0x3047:
            return (new InventoryItem(x, y, tile - 0x3000));
            break;
        case 0x3048:
        case 0x3049:
        case 0x304A:
        case 0x304B:
            return (new Lock(x, y, tile - 0x3000));
            break;
        case 0x304C:
        case 0x304D:
        case 0x304E:
        case 0x304F:
            return (new Door(x, y, tile - 0x3000));
            break;
        case 0x3051:
        case 0x3052:
        case 0x3062:
        case 0x3067:
            return (new Powerup(x, y, 1, 1, tile - 0x3000));
            break;



        default:
            return (new NonDukeObject(x, y, 1, 1, tile - 0x3000));
            break;
    }
}
