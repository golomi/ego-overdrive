/*
 * Copyright (C) 2025 thomas
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
 * File:   Dynamite.cpp
 * Author: thomas
 * 
 * Created on 8. März 2025, 09:47
 */

#include "Dynamite.h"
#include "DukeDrawSupport.h"

Dynamite::Dynamite(int x, int y, int w, int h, int type) : NonDukeObject(x, y, w, h, type) {

}

Dynamite::~Dynamite() {
}

void Dynamite::hit(int h) {
    state = explode;
}

void Dynamite::update(UpdateContext *updateContext) {
    switch (state) {
        case hold:
            break;
        case explode:
            if (counter <= counterMax) {
                counter++;
            } else {
                remove();
            }
            break;
        default:
              DebugOutput::addLine("Error Dynamite::update\n");
            break;
    }
}

void Dynamite::draw(Canvas *canvas, DukeTextureContainer *textures) {

    SDL_Texture *texture = NULL;

    switch (state) {
        case hold:
            texture = textureContainer.getTexture(25 + getObjectTextureFileIndex());
            DukeDrawSupport::drawTile(canvas, texture, 16 * getIndex(), getX(), getY());
            break;
        case explode:
            if (counter < 10) {
                texture = textureContainer.getTexture(3 + getObjectTextureFileIndex() + 2);
                int c = counter % 2;
                DukeDrawSupport::drawTile(canvas, texture, 16 * (16 + c), getX(), getY());
            } else if (counter < 12) {

            } else {
                texture = textureContainer.getTexture(3 + getObjectTextureFileIndex() + 1);
                DukeDrawSupport::drawTile(canvas, texture, 16 * (42 + counter - 12), getX(), getY());
                //TODO: extend to 5 flames each side
            }
            break;
        default:
            break;
    }
}
