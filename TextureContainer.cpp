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
 * File:   TextureContainer.cpp
 * Author: thomas
 * 
 * Created on 20. Februar 2021, 22:24
 */

#include "TextureContainer.h"

#include <cstdlib>



SDL_Texture* TextureContainer::menuBackgroundTexture = nullptr;
SDL_Texture* TextureContainer::dnTexture = nullptr;
SDL_Texture* TextureContainer::badGuyTexture = nullptr;
SDL_Texture* TextureContainer::dukeFaceTexture = nullptr;
SDL_Texture* TextureContainer::animTexture[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
SDL_Texture* TextureContainer::backSolidTexture[8] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
SDL_Texture* TextureContainer::dropTexture = nullptr;
SDL_Texture* TextureContainer::dropTexture2 = nullptr;
SDL_Texture* TextureContainer::fontTexture[2];
SDL_Texture* TextureContainer::manTexture[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
SDL_Texture* TextureContainer::objectTexture[3] = {nullptr, nullptr, nullptr};
SDL_Texture* TextureContainer::numbersTexture[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
SDL_Texture* TextureContainer::borderTexture = nullptr;
//SDL_Texture* TextureContainer::lobbyBackground = nullptr;

TextureContainer::TextureContainer() {
}

TextureContainer::~TextureContainer() {
}

void TextureContainer::loadDrops(SDL_Renderer* renderer, std::string mainDrop, std::string secondDrop) {
    if (dropTexture != nullptr) {
        SDL_DestroyTexture(dropTexture);
        dropTexture = nullptr;
    }

    if (dropTexture2 != nullptr) {
        SDL_DestroyTexture(dropTexture2);
        dropTexture2 = nullptr;
    }

    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    if (mainDrop.empty() == false) {
        dropTexture = dukeTexture.loadDrop(mainDrop.c_str(), renderer, format);
    } else {
        dropTexture = dukeTexture.createEmptyDrop(renderer, format);
    }
    if (mainDrop.empty() == false) {
        dropTexture2 = dukeTexture.loadDrop(secondDrop.c_str(), renderer, format);
    } else {
        dropTexture2 = dukeTexture.createEmptyDrop(renderer, format);
    }
    SDL_FreeFormat(format);
}

void TextureContainer::loadCommon(SDL_Renderer * renderer) {
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_PixelFormat *format2 = SDL_AllocFormat(SDL_PIXELFORMAT_RGB24);

    //    dropTexture = dukeTexture.loadDrop("dukedata/DROP0.DN3", renderer, format);
    //    dropTexture2 = dukeTexture.loadDrop("dukedata/DROP9.DN1", renderer, format);

    //loadDrops(renderer, "dukedata/DROP0.DN3", "dukedata/DROP9.DN1");
    loadDrops(renderer, "", "");
    dnTexture = dukeTexture.loadFullScreenImage("dukedata/DN.DN1", renderer, format);

    backSolidTexture[0] = dukeTexture.loadTiles("dukedata/BACK0.DN1", renderer, format2);
    backSolidTexture[1] = dukeTexture.loadTiles("dukedata/BACK1.DN1", renderer, format2);
    backSolidTexture[2] = dukeTexture.loadTiles("dukedata/BACK2.DN3", renderer, format);
    backSolidTexture[3] = dukeTexture.loadTiles("dukedata/BACK3.DN1", renderer, format2);
    backSolidTexture[4] = dukeTexture.loadTiles("dukedata/SOLID0.DN1", renderer, format2);
    backSolidTexture[5] = dukeTexture.loadTiles("dukedata/SOLID1.DN1", renderer, format2);
    backSolidTexture[6] = dukeTexture.loadTiles("dukedata/SOLID2.DN1", renderer, format2);
    backSolidTexture[7] = dukeTexture.loadTiles("dukedata/SOLID3.DN1", renderer, format2);

    objectTexture[0] = dukeTexture.loadTiles("dukedata/OBJECT0.DN1", renderer, format);
    objectTexture[1] = dukeTexture.loadTiles("dukedata/OBJECT1.DN1", renderer, format);
    objectTexture[2] = dukeTexture.loadTiles("dukedata/OBJECT2.DN1", renderer, format);


    animTexture[0] = dukeTexture.loadTiles("dukedata/ANIM0.DN1", renderer, format);
    animTexture[1] = dukeTexture.loadTiles("dukedata/ANIM1.DN1", renderer, format);
    animTexture[2] = dukeTexture.loadTiles("dukedata/ANIM2.DN1", renderer, format);
    animTexture[3] = dukeTexture.loadTiles("dukedata/ANIM3.DN1", renderer, format);
    animTexture[4] = dukeTexture.loadTiles("dukedata/ANIM4.DN1", renderer, format);
    animTexture[5] = dukeTexture.loadTiles("dukedata/ANIM5.DN1", renderer, format);

    fontTexture[0] = dukeTexture.loadFont("dukedata/FONT1.DN1", renderer, format);
    fontTexture[1] = dukeTexture.loadFont("dukedata/FONT2.DN1", renderer, format);

    manTexture[0] = dukeTexture.loadMan("dukedata/MAN0.DN1", renderer, format);
    manTexture[1] = dukeTexture.loadMan("dukedata/MAN1.DN1", renderer, format);
    manTexture[2] = dukeTexture.loadMan("dukedata/MAN2.DN1", renderer, format);
    manTexture[3] = dukeTexture.loadMan("dukedata/MAN3.DN1", renderer, format);
    manTexture[4] = dukeTexture.loadMan("dukedata/MAN4.DN1", renderer, format);

    borderTexture = dukeTexture.loadTiles("dukedata/BORDER.DN1", renderer, format);

    SDL_FreeFormat(format);
    SDL_FreeFormat(format2);
}

void TextureContainer::freeAll() {

    SDL_DestroyTexture(dropTexture);
    dropTexture = nullptr;
    SDL_DestroyTexture(dropTexture2);
    dropTexture2 = nullptr;
    SDL_DestroyTexture(dnTexture);
    dnTexture = nullptr;

    for (int i = 0; i <= 7; i++) {
        SDL_DestroyTexture(backSolidTexture[i]);
        backSolidTexture[i] = nullptr;
    }

    for (int i = 0; i <= 2; i++) {
        SDL_DestroyTexture(objectTexture[i]);
        objectTexture[i] = nullptr;
    }

    for (int i = 0; i <= 5; i++) {
        SDL_DestroyTexture(animTexture[i]);
        animTexture[i] = nullptr;
    }

    for (int i = 0; i <= 1; i++) {
        SDL_DestroyTexture(fontTexture[i]);
        fontTexture[i] = nullptr;
    }

    for (int i = 0; i <= 4; i++) {
        SDL_DestroyTexture(manTexture[i]);
        manTexture[i] = nullptr;
    }


    SDL_DestroyTexture(borderTexture);
    borderTexture = nullptr;


}

SDL_Texture * TextureContainer::getTexture(int n) {
    switch (n) {
        case 0:
            return (menuBackgroundTexture);
            break;
        case 1:
            return (dnTexture);
            break;
        case 2:

            return (badGuyTexture);
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            return (animTexture[n - 3]);
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            return (backSolidTexture[n - 9]);
            break;
        case 17:
            return (dropTexture);
            break;
        case 18:
        case 19:
            return (fontTexture[n - 18]);
            break;
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            return (manTexture[n - 20]);
            break;
        case 25:
        case 26:
        case 27:
            return (objectTexture[n - 25]);
            break;
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
            return (numbersTexture[n - 28]);
            break;
        case 33:
            return (borderTexture);
            break;
        case DROP2_TEXTURE:
            return (dropTexture2);
            break;
        default:
            return (NULL);
            break;
    }

}