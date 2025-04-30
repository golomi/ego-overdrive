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
 * File:   ExitDoor.cpp
 * Author: thomas
 * 
 * Created on 25. April 2022, 23:13
 */

#include "ExitDoor.h"
#include "DukeDrawSupport.h"

ExitDoor::ExitDoor(int x, int y, int type) : NonDukeObject(x, y, 2,2,type) {
}

void ExitDoor::action(Duke *duke, std::list<MapObject*> &objectVector, MapObjectNotifier *listener) {

    doorOpened = true;

    listener->action(this, FinishedWorld, nullptr);
}

void ExitDoor::draw(Canvas *canvas, DukeTextureContainer *textures) {
    //static SDL_Rect sourceRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
//    static SDL_Rect destRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};


//    SDL_Texture *texture = textures->getTexture(3+2);


//    destRect.x = getTileX() * TILE_WIDTH;
//    destRect.y = (getTileY()-1) * TILE_HEIGHT;


    DukeDrawSupport::drawMultiTile(canvas,textures->getTexture(3+2),doorOpenCounter / 2 * TILE_HEIGHT * 4,2,2,getTileX() * TILE_WIDTH,(getTileY()-1) * TILE_HEIGHT);


}

void ExitDoor::update(UpdateContext *updateContext) {
    if (doorOpened) {
        if (doorOpenCounter < 2 * 4) {
            doorOpenCounter++;
        } else {
            doorOpenCounter = 0;
            doorOpened = 0;
            // TODO: Map finished
        }
    }

}