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
 * File:   GameCanvas.h
 * Author: thomas
 *
 * Created on 27. Mai 2022, 07:57
 */

#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include <SDL2/SDL.h>

#include "Canvas.h"
#include "DukeViewPort.h"

class GameCanvas : public Canvas {
private:
    SDL_Renderer* renderer;
    const int RESIZE_FACTOR_X = 2;
    const int RESIZE_FACTOR_Y = 2;

    DukeViewPort *viewPort;
public:
    GameCanvas(SDL_Renderer *renderer, DukeViewPort *viewPort);
    virtual ~GameCanvas();
    void draw(SDL_Texture *texture, SDL_Rect *sourceRect, SDL_Rect * destRect)  override;

    inline void draw(SDL_Texture *texture, SDL_Rect *sourceRect, int destX, int destY) {
        static SDL_Rect destRect = {destX, destY, sourceRect->w, sourceRect->h};
        draw(texture, sourceRect, &destRect);
    }

    void drawHalfTile(SDL_Texture *tileTexure, int tile, int destX, int destY);

    void renderClear()  override {
        SDL_RenderClear(renderer);
    }
  SDL_Renderer* getRenderer()  override;
};

#endif /* GAMECANVAS_H */

