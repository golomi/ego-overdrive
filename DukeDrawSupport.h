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
 * File:   DukeDrawSupport.h
 * Author: thomas
 *
 * Created on 1. August 2022, 23:06
 */

#ifndef DUKEDRAWSUPPORT_H
#define DUKEDRAWSUPPORT_H

#include <SDL2/SDL.h>

#include "Canvas.h"

class DukeDrawSupport {
private:
public:
    DukeDrawSupport();

    static void drawTile(Canvas *canvas, SDL_Texture *tileTexure, int tile, int destX, int destY);
    static void drawMultiTile(Canvas *canvas, SDL_Texture *tileTexure, int tile, int tileWidth, int tileHeight, int destX, int destY);
    static void drawHalfTile(Canvas *canvas, SDL_Texture *tileTexure, int tile, int destX, int destY);
};

#endif /* DUKEDRAWSUPPORT_H */

