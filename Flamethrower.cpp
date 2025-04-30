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
 * File:   Flamethrower.cpp
 * Author: thomas
 * 
 * Created on 20. März 2024, 01:21
 */

#include "Flamethrower.h"

#include "DukeDrawSupport.h"

Flamethrower::Flamethrower(int x, int y, int type) : NonDukeObject(x, y, 1, 1, type) {
}

Flamethrower::~Flamethrower() {
}

void Flamethrower::draw(Canvas *canvas, DukeTextureContainer *textures) {

    //        true, object, 0, 24, 5, false, false, false, false, 0, false, 1, 1, 1, 0
    //        true, object, 0, 25, 5, false, false, false, false, 0, false, 1, 1, 1, 0

    SDL_Texture *texture = NULL;

    int flameTick = (getTick()) % STATE_FINAL;

    if (getType() == 0x3009 || getType() == 0x09) {
        texture = textureContainer.getTexture(25 + getObjectTextureFileIndex());
    } else if (getType() == 0x300A || getType() == 0x0A) {
        texture = textureContainer.getTexture(25 + getObjectTextureFileIndex());
    }

    if (flameTick < STATE_SMALL_FLAME) {
        // nothing to draw
    } else if (flameTick < STATE_FULL_FLAME) {

        if ((getTick()) % 2 == 0) {

            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * getIndex(), 1, 1, getX(), getY());


        }
    } else if (flameTick < STATE_FINAL) {
        int flameIndex = getTick() % 2;
        if (getType() == 0x3009 || getType() == 0x09) {
            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 1 + flameIndex),
                    1, 1, getX(), getY());
            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 1 + flameIndex),
                    1, 1, getX() + 1 * TILE_WIDTH, getY());
            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 3 + flameIndex),
                    1, 1, getX() + 2 * TILE_WIDTH, getY());
        } else if (getType() == 0x300A || getType() == 0x0A) {
            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 1 + flameIndex),
                    1, 1, getX(), getY());
            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 1 + flameIndex),
                    1, 1, getX() - 1 * TILE_WIDTH, getY());
            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 3 + flameIndex),
                    1, 1, getX() - 2 * TILE_WIDTH, getY());
        }

    }

}