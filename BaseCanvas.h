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
 * File:   MainCanvas.h
 * Author: thomas
 *
 * Created on 28. Mai 2022, 00:20
 */

#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include <SDL2/SDL.h>

#include "Canvas.h"


class BaseCanvas : public Canvas {
private:
    SDL_Renderer* renderer;
    const int RESIZE_FACTOR_X = 2;
    const int RESIZE_FACTOR_Y = 2;
public:
    BaseCanvas(SDL_Renderer *renderer);
    virtual ~BaseCanvas();

    void draw(SDL_Texture *texture, SDL_Rect *sourceRect, SDL_Rect * destRect);

    void renderClear() {
        SDL_RenderClear(renderer);
    }

    virtual SDL_Renderer* getRenderer();
    
    
};

#endif /* MAINCANVAS_H */

