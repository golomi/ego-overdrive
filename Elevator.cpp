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
 * File:   Elevator.cpp
 * Author: thomas
 * 
 * Created on 22. November 2022, 21:14
 */

#include <regex>

#include "Elevator.h"
#include "DebugOutput.h"

Elevator::Elevator(int x, int y, int w, int h, int type) : NonDukeObject(x, y, w, h, type) {
}

Elevator::~Elevator() {
}

void Elevator::draw(Canvas *canvas, DukeTextureContainer *textures) {
    SDL_Rect sourceRect = {0, TILE_HEIGHT * 5, TILE_WIDTH, TILE_HEIGHT};
    SDL_Rect destRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};

    destRect.x = getTileX() * TILE_WIDTH;
    destRect.y = (getTileY() - extended) * TILE_HEIGHT;
    canvas->draw(textureContainer.getTexture(25), &sourceRect, &destRect);


    sourceRect = {0, TILE_HEIGHT * 6 - 1, TILE_WIDTH, 1};
    destRect = {0, 0, TILE_WIDTH, 1};

    for (int i = 0; i < extended * TILE_HEIGHT; i++) {
        destRect.x = getTileX() * TILE_WIDTH;
        destRect.y = (getTileY() - extended + 1) * TILE_HEIGHT + i;
        canvas->draw(textureContainer.getTexture(25), &sourceRect, &destRect);
    }

}

void Elevator::updateSolidMap() {
    for (int i = 0; i <= extended; i++) {
        getMap()->setTempSolid(getTileX(), getTileY() - i);
    }
}

void Elevator::action(Duke *duke, int type, std::list<MapObject*> &objectVector, MapObjectNotifier *listener) {

    switch (state) {
        case standing:
            if (type == 1) {
                if (duke != NULL) {
                    state = rising;
                }
            } else if (type == 0) {
            }
            break;
        case rising:

            /* if (type == 1 ) {
              
             } else*/if (type == 0) {
                state = standing;
            }
            break;
        case falling:
            // do nothing
            break;
        default:
            // TODO: error message
            break;
    }


    //    if (state == rising) {
    //        // check for space above (elevator position + extended - DUKE_HEIGHT)
    //        extended++;
    //        duke->setTileY(duke->getTileY() - 1);
    //    } else if (state == falling) {
    //        // when elevator ist falling, do nothing
    //    } else {
    //        // TODO: error message
    //    }
}

int Elevator::getTileHeight() {
    return (1 + extended);
}

void Elevator::update(UpdateContext *updateContext) {
    switch (state) {
            // TODO: add state grounded in order to avoid checking if extended > 0 every cycle
        case standing:
            if (extended > 0 && duke == NULL)
                state = falling;
            break;
        case rising:
            if (isCeilingClose()) {
                state = standing;
            } else {
                extended++;

                // TODO: check if (at least one) duke is standing on the elevator
                if (duke != NULL) {
                    duke->setTileY(duke->getTileY() - 1);
                } else {
                    DebugOutput::addLine("Error: Elevator rising, but no duke standing on the elevator");
                }
            }
            break;
        case falling:
            if (extended > 0) {
                extended--;
            }

            if (extended == 0) {
                state = standing;
            }

            // do nothing
            break;
        default:
            // TODO: error message
            break;
    }
}

void Elevator::standon(Duke *duke) {
    this->duke = duke;
}

void Elevator::clearStandon() {
    this->duke = NULL;
}

bool Elevator::isCeilingClose() {

    return (getMap()->isTileSolid(getTileX(), getTileY() - extended - 3));
}