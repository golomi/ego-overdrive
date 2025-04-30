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
 * File:   MainCanvas.cpp
 * Author: thomas
 * 
 * Created on 28. Mai 2022, 00:20
 */

#include "BaseCanvas.h"

BaseCanvas::BaseCanvas(SDL_Renderer *renderer) {
    this->renderer = renderer;
}

BaseCanvas::~BaseCanvas() {
}

void BaseCanvas::draw(SDL_Texture *texture, SDL_Rect *sourceRect, SDL_Rect *destRect) {
    SDL_Rect newDestRect;

    if (destRect != NULL) {
        newDestRect.x = destRect->x * RESIZE_FACTOR_X;
        newDestRect.y = destRect->y * RESIZE_FACTOR_Y;
        newDestRect.w = destRect->w * RESIZE_FACTOR_X;
        newDestRect.h = destRect->h * RESIZE_FACTOR_Y;
    }

    SDL_RenderCopy(renderer, texture, sourceRect, &newDestRect);
}

SDL_Renderer* BaseCanvas::getRenderer() {
    return renderer;
}