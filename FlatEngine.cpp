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
 * File:   FlatEngine.cpp
 * Author: thomas
 * 
 * Created on 4. Februar 2021, 14:25
 */

#include "FlatEngine.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#include "BaseCanvas.h"
#include "ListDrawLayer.h"

FlatEngine::FlatEngine() {
    drawLayers.push_back(new ListDrawLayer());
}

FlatEngine::FlatEngine(const FlatEngine& orig) {
}

FlatEngine::~FlatEngine() {
}

// TODO: move to a class with FlatEngine tools or create a class for texture loaders

SDL_Texture* FlatEngine::loadTexture(std::string path) {
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void FlatEngine::init(int argc, char** argv) {
    preInit(argc, argv);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL konnte nicht initialisiert werden:  %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

    setVideoMode(screenWidth, screenHeight, 0, 0); // die letzten beiden Argumente werden nicht mehr genutzt

    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE); // Mousebewegungsereignisse ignorieren, da die Mousposition bei Bedarf direkt abgefragt wird

    SDL_ShowCursor(0); // Mauszeiger verstecken


    // TODO: remove cursor texture from FlatEngine
    cursorTexture = loadTexture("data/cursor.png");
    cursorClickedTexture = loadTexture("data/cursor_clicked.png");

    controller = initController();

    postInit(renderer);
}

void FlatEngine::setVideoMode(int width, int height, int bpp, int flags) {

    window = SDL_CreateWindow("Dux", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    } else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL) {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        } else {

            //SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);


            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            }
        }
        //Get window surface
        //   screenSurface = SDL_GetWindowSurface(window);

        // SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    }

    canvas = new BaseCanvas(renderer);


}

void FlatEngine::processEvent(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        exitSignal = true;
    }
}

void FlatEngine::loop() {


    while (!exitSignal) {
        controller->update();

        int x, y;

        unsigned int buttonState = getMouseState(&x, &y);

        update();

        draw(canvas);

        // TODO: move to separate method drawLayers or similar
//        {
//            for (DrawLayerInterface*& layer : drawLayers) {
//                layer->draw(canvas);
//            }
//
//        }


        SDL_Rect rect;

        rect.w = 16;
        rect.h = 16;
        rect.x = x;
        rect.y = y;

        SDL_Texture *currentCursorTexture;


        // TODO: remove workaround
        if (buttonState & 1) {
            currentCursorTexture = cursorClickedTexture;
        } else {
            currentCursorTexture = cursorTexture;
        }

        //Render cursor texture to screen
        if (mouseCursorVisible)
            SDL_RenderCopy(renderer, currentCursorTexture, NULL, &rect);

        // Update screen
        SDL_RenderPresent(renderer);


        //  SDL_UpdateWindowSurface(window);
        //  SDL_Delay(100);
    }
}

void FlatEngine::cleanup() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
}

void FlatEngine::draw(Canvas* renderer) {

}

void FlatEngine::postInit(SDL_Renderer * renderer) {

}

void FlatEngine::preInit(int argc, char** argv) {

}

void FlatEngine::setRenderer(SDL_Renderer * renderer) {
    this->renderer = renderer;
}

SDL_Renderer * FlatEngine::getRenderer() const {
    return renderer;
}

void FlatEngine::setWindow(SDL_Window * window) {
    this->window = window;
}

SDL_Window * FlatEngine::getWindow() const {
    return window;
}

void FlatEngine::toggleFullscreen() {
    Uint32 flags(SDL_GetWindowFlags(getWindow()));
    flags ^= SDL_WINDOW_FULLSCREEN_DESKTOP;
    SDL_SetWindowFullscreen(getWindow(), flags);

    if ((flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
    } else {
        SDL_SetWindowSize(getWindow(), screenWidth, screenHeight);
    }
}

int FlatEngine::getScreenHeight() const {
    return screenHeight;
}

int FlatEngine::getScreenWidth() const {
    return screenWidth;
}

void FlatEngine::setScreenSize(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

void FlatEngine::setExitSignal(int exitSignal) {
    this->exitSignal = exitSignal;
}

int FlatEngine::getExitSignal() const {
    return exitSignal;
}

void FlatEngine::setMouseCursorVisible(int mouseCursorVisible) {
    this->mouseCursorVisible = mouseCursorVisible;
}

int FlatEngine::getMouseCursorVisible() const {
    return mouseCursorVisible;
}

void FlatEngine::setController(Controller* controller) {
    this->controller = controller;
}

Controller* FlatEngine::getController() const {
    return controller;
}

void FlatEngine::update() {

}

unsigned int FlatEngine::getMouseState(int *x, int *y) {
    return (SDL_GetMouseState(x, y));
}