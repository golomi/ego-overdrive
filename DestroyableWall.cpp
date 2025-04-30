/*
 * Copyright (C) 2023 thomas
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
 * File:   DestroyableWall.cpp
 * Author: thomas
 * 
 * Created on 18. März 2023, 22:18
 */

#include "DestroyableWall.h"

DestroyableWall::DestroyableWall(int x, int y, int type) : NonDukeObject(x, y, 1, 1, type) {
}

DestroyableWall::~DestroyableWall() {
}

void DestroyableWall::updateSolidMap() {
    getMap()->setTempSolid(getTileX(), getTileY());
}

void DestroyableWall::draw(Canvas *canvas, DukeTextureContainer *textures) {
    SDL_Rect sourceRect = {0,0, TILE_WIDTH, TILE_HEIGHT};
    SDL_Rect destRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};


    destRect.x = getTileX() * TILE_WIDTH;
    destRect.y = getTileY() * TILE_HEIGHT;
    canvas->draw(textureContainer.getTexture(BACK_SOLID_TEXTURE+4), &sourceRect, &destRect);
}