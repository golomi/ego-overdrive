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

/* 
 * File:   DukeTexture.cpp
 * Author: Thomas Lenck
 * 
 * Created on 5. Februar 2021, 23:42
 */

#include "DukeTexture.h"

/** 
 * @class DukeTexture Loads Duke images using class DukeImage and converts 
 * them to SDL_Texture
 */


DukeTexture::DukeTexture() {
}

SDL_Surface *DukeTexture::preprocessSurface(SDL_Renderer * renderer, int width, int height, int depth) {
    Uint32 rmask, gmask, bmask, amask;
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    if (depth == 32) {
        amask = 0xff000000;
    } else {
        amask = 0;
    }

    SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, depth, rmask, gmask, bmask, amask);
    if (surface == NULL) {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        return (NULL);
    }

    SDL_LockSurface(surface);

    return (surface);
}

SDL_Texture *DukeTexture::postprocessSurface(SDL_Renderer * renderer, SDL_Surface *surface, Uint32 pixelFormat) {

    SDL_UnlockSurface(surface);

    //Convert surface to display format
    SDL_Surface* convertedSurface = SDL_ConvertSurfaceFormat(surface, pixelFormat, 0);
    if (convertedSurface == NULL) {
        printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, convertedSurface);
    if (texture == NULL) {
        printf("SDL_CreateTextureFromSurface() failed: %s\n", SDL_GetError());
        return (NULL);
    }

    SDL_FreeSurface(convertedSurface);
    SDL_FreeSurface(surface);

    return (texture);
}

SDL_Texture *DukeTexture::postprocessSurface(SDL_Renderer * renderer, SDL_Surface *surface, SDL_PixelFormat *format) {

    SDL_UnlockSurface(surface);

    //Convert surface to display format
    SDL_Surface* convertedSurface = SDL_ConvertSurface(surface, format, 0);
    if (convertedSurface == NULL) {
        printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, convertedSurface);
    if (texture == NULL) {
        printf("SDL_CreateTextureFromSurface() failed: %s\n", SDL_GetError());
        return (NULL);
    }

    SDL_FreeSurface(convertedSurface);
    SDL_FreeSurface(surface);

    return (texture);
}

SDL_Texture *DukeTexture::loadTiles(std::string fileName, SDL_Renderer* renderer, SDL_PixelFormat *format) {
    SDL_Surface *surface = preprocessSurface(renderer, dukeImage.TILE_WIDTH, dukeImage.TILE_HEIGHT * dukeImage.TILES_PER_FILE, dukeImage.TILE_DEPTH * 8);

    dukeImage.loadTiles(fileName, (unsigned char*) surface->pixels, surface->pitch, dukeImage.TILE_DEPTH);

    return (postprocessSurface(renderer, surface, format));
}

SDL_Texture *DukeTexture::loadFullScreenImage(std::string fileName, SDL_Renderer* renderer, SDL_PixelFormat *format) {
    SDL_Surface *surface = preprocessSurface(renderer, dukeImage.FULLSCREEN_WIDTH, dukeImage.FULLSCREEN_HEIGHT, dukeImage.FULLSCREEN_DEPTH * 8);

    dukeImage.loadFullScreenImage(fileName, (unsigned char*) surface->pixels, surface->pitch, dukeImage.FULLSCREEN_DEPTH);

    return (postprocessSurface(renderer, surface, format));
}

SDL_Texture *DukeTexture::loadDrop(std::string fileName, SDL_Renderer* renderer, SDL_PixelFormat *format) {
    SDL_Surface *surface = preprocessSurface(renderer, dukeImage.DROP_WIDTH, dukeImage.DROP_HEIGHT, dukeImage.DROP_DEPTH * 8);

    dukeImage.loadDrop(fileName, (unsigned char*) surface->pixels, surface->pitch, dukeImage.DROP_DEPTH);

    return (postprocessSurface(renderer, surface, format));
}

SDL_Texture *DukeTexture::loadMan(std::string fileName, SDL_Renderer* renderer, SDL_PixelFormat *format) {
    SDL_Surface *surface = preprocessSurface(renderer, dukeImage.MAN_TILES_WIDTH, dukeImage.MAN_TILES_HEIGHT * dukeImage.MAN_TILES_PER_FILE, dukeImage.MAN_TILES_DEPTH * 8);

    dukeImage.loadMan(fileName, (unsigned char*) surface->pixels, surface->pitch, dukeImage.MAN_TILES_DEPTH);

    return (postprocessSurface(renderer, surface, format));
}

SDL_Texture *DukeTexture::loadFont(std::string fileName, SDL_Renderer* renderer, SDL_PixelFormat *format) {
    SDL_Surface *surface = preprocessSurface(renderer, dukeImage.FONT_WIDTH, dukeImage.FONT_HEIGHT * dukeImage.FONT_PER_FILE, dukeImage.FONT_DEPTH * 8);

    dukeImage.loadFont(fileName, (unsigned char*) surface->pixels, surface->pitch, dukeImage.FONT_DEPTH);

    return (postprocessSurface(renderer, surface, format));
}

SDL_Texture *DukeTexture::createEmptyDrop(SDL_Renderer* renderer, SDL_PixelFormat *format) {
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, dukeImage.DROP_WIDTH, dukeImage.DROP_HEIGHT);

    SDL_SetRenderTarget(renderer, texture);

    SDL_RenderClear(renderer);
    
    return (texture);
}
