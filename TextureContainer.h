/*
 * Copyright (C) 2021 thomas
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
 * File:   TextureContainer.h
 * Author: thomas
 *
 * Created on 20. Februar 2021, 22:24
 */

#ifndef TEXTURECONTAINER_H
#define TEXTURECONTAINER_H

#include <SDL2/SDL.h>

#include "DukeTexture.h"

const int MENU_BACKGROUND_TEXTURE = 0;
const int DN_TEXTURE = 1;
const int BAD_GUY_TEXTURE = 2;
const int ANIM_TEXTURE = 3;
const int BACK_SOLID_TEXTURE = 9;
const int DROP_TEXTURE = 17;
const int FONT_TEXTURE = 18;
const int MAN_TEXTURE = 20;
const int OBJECT_TEXTURE = 25;
const int NUMBER_TEXTURE = 28;
const int BORDER_TEXTURE = 33;
const int DROP2_TEXTURE = 34;

class TextureContainer {
private:
    DukeTexture dukeTexture;
public:
    static SDL_Texture* menuBackgroundTexture;
    static SDL_Texture* dnTexture;
    static SDL_Texture* badGuyTexture;
    static SDL_Texture* dukeFaceTexture;
    static SDL_Texture* animTexture[6];
    static SDL_Texture* backSolidTexture[8];
    static SDL_Texture* dropTexture;
    static SDL_Texture* fontTexture[2];
    static SDL_Texture* manTexture[5];
    static SDL_Texture* objectTexture[3];
    static SDL_Texture* numbersTexture[5];
    static SDL_Texture* borderTexture;
 //   static SDL_Texture* lobbyBackground;
    static SDL_Texture* dropTexture2;
    
    TextureContainer();
    virtual ~TextureContainer();

    void loadCommon(SDL_Renderer* renderer);
    void loadDrops(SDL_Renderer* renderer, std::string mainDrop, std::string secondDrop);
    SDL_Texture *getTexture(int n);
    void freeAll();

};

#endif /* TEXTURECONTAINER_H */

