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
 * File:   DissolvingGround.cpp
 * Author: thomas
 * 
 * Created on 12. März 2023, 13:15
 */

#include "DissolvingGround.h"

#include "DukeDrawSupport.h"

DissolvingGround::DissolvingGround(int x, int y, int type) : NonDukeObject(x, y, 1, 1, type) {

}

DissolvingGround::~DissolvingGround() {
}

void DissolvingGround::updateSolidMap() {
    for (int i = 0; i < 4; i++) {
        getMap()->setTempSolid(getTileX() + i, getTileY());
    }
}

void DissolvingGround::standon(Duke *duke) {
    dukeStandon = true;
}

void DissolvingGround::clearStandon() {
    dukeStandon = false;
}

void DissolvingGround::update(UpdateContext * updateContext) {
    switch (state) {
        case initial:
            if (dukeStandon == true) {
                state = firstTouch;
            }
            break;
        case firstTouch:
            if (dukeStandon == false) {
                state = firstUntouch;
            }
            break;
        case firstUntouch:
            if (dukeStandon == true) {
                state = secondTouch;
            }
            break;
        case secondTouch:
            remove();
            break;
    }
}

void DissolvingGround::draw(Canvas *canvas, DukeTextureContainer *textures) {
    SDL_Texture *texture = NULL;

    if (getObjectTextureFile() == object) {
        // texture = textureContainer.objectTexture[getObjectTextureFileIndex()];
        texture = textureContainer.getTexture(25 + getObjectTextureFileIndex());

    } else if (getObjectTextureFile() == anim) {
        //        texture = textureContainer.animTexture[getObjectTextureFileIndex()];
        texture = textureContainer.getTexture(3 + getObjectTextureFileIndex());
    }


    DukeDrawSupport::drawTile(canvas, texture, TILE_HEIGHT * (0), (getTileX() + 0) * TILE_WIDTH, getTileY() * TILE_HEIGHT);
    DukeDrawSupport::drawTile(canvas, texture, TILE_HEIGHT * (1), (getTileX() + 1) * TILE_WIDTH, getTileY() * TILE_HEIGHT);
    DukeDrawSupport::drawTile(canvas, texture, TILE_HEIGHT * (0), (getTileX() + 2) * TILE_WIDTH, getTileY() * TILE_HEIGHT);
    DukeDrawSupport::drawTile(canvas, texture, TILE_HEIGHT * (1), (getTileX() + 3) * TILE_WIDTH, getTileY() * TILE_HEIGHT);

}
