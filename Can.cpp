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
 * File:   Can.cpp
 * Author: thomas
 * 
 * Created on 20. Februar 2021, 23:07
 */

#include "Can.h"

Can::Can(int x, int y, int w, int h, int type) : NonDukeObject(x, y, 1, 1, type) {
}

Can::~Can() {
}

//void Can::draw(GameCanvas *canvas, TextureContainer * textures) {
//    //    static SDL_Rect sourceRect = {0, TILE_HEIGHT * 32, TILE_WIDTH, TILE_HEIGHT};
//    //    static SDL_Rect destRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
//    //
//    //
//    //    destRect.x = getTileX() * 16;
//    //    destRect.y = getTileY() *16;
//    //
//    //    canvas->draw(textureContainer.animTexture[2], &sourceRect, &destRect);
//}

void Can::collect(Duke *duke) {
    duke->getProperties()->addHealth(1);
}