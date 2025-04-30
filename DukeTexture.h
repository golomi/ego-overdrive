/*
 * Copyright (C) 2021 Thomas Lenck
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

/*! 
 * File:   DukeTexture.h
 * Author: Thomas Lenck
 *
 * Created on 5. Februar 2021, 23:42
 */

#ifndef DUKETEXTURE_H
#define DUKETEXTURE_H

#include "DukeImage.h"

#include <iostream>

#include <SDL2/SDL.h>

/*!
 * Loads images with DukeImage and converts them SDL_Texture 
 */
class DukeTexture {
private:
    DukeImage dukeImage;

    SDL_Surface *preprocessSurface(SDL_Renderer * renderer, int width, int height, int depth);
    SDL_Texture *postprocessSurface(SDL_Renderer * renderer, SDL_Surface *surface, Uint32 pixelFormat);
    SDL_Texture *postprocessSurface(SDL_Renderer * renderer, SDL_Surface *surface, SDL_PixelFormat *format);

public:
    DukeTexture();
    SDL_Texture *loadTiles(std::string fileName, SDL_Renderer* renderer, SDL_PixelFormat *format);
    SDL_Texture *loadFullScreenImage(std::string fileName, SDL_Renderer* renderer, SDL_PixelFormat *format);
    SDL_Texture *loadDrop(std::string fileName, SDL_Renderer* renderer, SDL_PixelFormat *format);
    SDL_Texture *loadMan(std::string fileName, SDL_Renderer* renderer, SDL_PixelFormat *format);
    SDL_Texture *loadFont(std::string fileName, SDL_Renderer* renderer, SDL_PixelFormat *format);
    SDL_Texture *createEmptyDrop(SDL_Renderer* renderer, SDL_PixelFormat *format);
};

#endif /* DUKETEXTURE_H */

