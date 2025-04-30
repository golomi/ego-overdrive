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
 * File:   GameCanvas.cpp
 * Author: thomas
 * 
 * Created on 27. Mai 2022, 07:57
 */

#include "GameCanvas.h"

GameCanvas::GameCanvas(SDL_Renderer *renderer, DukeViewPort *viewPort) {
    this->renderer = renderer;
    this->viewPort = viewPort;
}

SDL_Renderer* GameCanvas::getRenderer() {
    return renderer;
}

GameCanvas::~GameCanvas() {
}

void GameCanvas::draw(SDL_Texture *texture, SDL_Rect *sourceRect, SDL_Rect *destRect) {
    SDL_Rect newDestRect;

    newDestRect.x = (destRect->x - viewPort->getShiftX()) * RESIZE_FACTOR_X;
    newDestRect.y = (destRect->y - viewPort->getShiftY()) * RESIZE_FACTOR_Y;
    newDestRect.w = destRect->w*RESIZE_FACTOR_X;
    newDestRect.h = destRect->h*RESIZE_FACTOR_Y;

    SDL_RenderCopy(renderer, texture, sourceRect, &newDestRect);
}

void GameCanvas::drawHalfTile(SDL_Texture *tileTexure, int tile, int destX, int destY) {
    // TODO: Auxiliary method, should be moved to separate class (e.g. DukeDrawSupport)
    static SDL_Rect sourceRect = {0, 0, TILE_WIDTH / 2, TILE_HEIGHT};
    static SDL_Rect destRect = {0, 0, TILE_WIDTH / 2 * RESIZE_FACTOR_X, TILE_HEIGHT * RESIZE_FACTOR_Y};


    sourceRect.y = tile;

    destRect.x = destX * RESIZE_FACTOR_X;
    destRect.y = destY * RESIZE_FACTOR_Y;

    SDL_RenderCopy(renderer, tileTexure, &sourceRect, &destRect);

}