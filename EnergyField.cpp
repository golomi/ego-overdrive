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
 * File:   EnergieField.cpp
 * Author: thomas
 * 
 * Created on 1. Mai 2022, 00:27
 */

#include "EnergyField.h"
#include "DukeDefinitions.h"

EnergyField::EnergyField(int x, int y, int type) : NonDukeObject(x, y, 1, 1, type) {

}

EnergyField::~EnergyField() {
}

void EnergyField::draw(Canvas *canvas, DukeTextureContainer *textures) {
    static SDL_Rect sourceRect = {0, TILE_HEIGHT * 40, TILE_WIDTH, TILE_HEIGHT};
    static SDL_Rect destRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};


    destRect.x = getTileX() * TILE_WIDTH;
    destRect.y = getTileY() * TILE_HEIGHT;



    for (int i = 0; i < 3; i++) {
        sourceRect.y = 16 * (40 + getTick() % 5);
        destRect.y = (getTileY() - i) * TILE_HEIGHT;
        canvas->draw(textureContainer.getTexture(26), &sourceRect, &destRect);
    }
}

