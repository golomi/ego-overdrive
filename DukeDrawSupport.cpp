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
 * File:   DukeDrawSupport.cpp
 * Author: thomas
 * 
 * Created on 1. August 2022, 23:06
 */

#include "DukeDrawSupport.h"

#include "DukeDefinitions.h"

DukeDrawSupport::DukeDrawSupport() {
}

void DukeDrawSupport::drawTile(Canvas *canvas, SDL_Texture *tileTexure, int tile, int destX, int destY) {

    static SDL_Rect sourceRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    static SDL_Rect destRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};


    sourceRect.y = tile;

    destRect.x = destX;
    destRect.y = destY;

    canvas->draw(tileTexure, &sourceRect, &destRect);

}

void DukeDrawSupport::drawMultiTile(Canvas *canvas, SDL_Texture *tileTexure, int tile, int tileWidth, int tileHeight, int destX, int destY) {
    static SDL_Rect sourceRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    static SDL_Rect destRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};

    for (int y = 0; y < tileHeight; y++)
        for (int x = 0; x < tileWidth; x++) {
            sourceRect.y = tile + (x + y * tileWidth) * TILE_HEIGHT;

            destRect.x = destX + x*TILE_WIDTH;
            destRect.y = destY + y*TILE_HEIGHT;

            canvas->draw(tileTexure, &sourceRect, &destRect);
        }
}

void DukeDrawSupport::drawHalfTile(Canvas *canvas, SDL_Texture *tileTexure, int tile, int destX, int destY) {
    static SDL_Rect sourceRect = {0, 0, TILE_WIDTH / 2, TILE_HEIGHT};
    static SDL_Rect destRect = {0, 0, TILE_WIDTH / 2 /**RESIZE_FACTOR_X*/, TILE_HEIGHT /**RESIZE_FACTOR_Y*/};


    sourceRect.y = tile;

    destRect.x = destX /* * RESIZE_FACTOR_X*/;
    destRect.y = destY /* * RESIZE_FACTOR_Y*/;

    canvas->draw(tileTexure, &sourceRect, &destRect);

}
