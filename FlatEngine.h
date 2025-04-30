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
 * File:   FlatEngine.h
 * Author: thomas
 *
 * Created on 4. Februar 2021, 14:25
 */

#ifndef FLATENGINE_H
#define FLATENGINE_H

#include <SDL2/SDL.h>

#include <iostream>
#include <list>

#include "Controller.h"
#include "Canvas.h"
#include "DrawLayerInterface.h"

class FlatEngine {
private:
    SDL_Window* window = NULL; /** The window we'll be rendering to*/

//    SDL_Surface* screenSurface = NULL; /** The surface contained by the window*/

    SDL_Texture* cursorTexture = NULL;
    SDL_Texture* cursorClickedTexture = NULL;

    int screenWidth = 800;
    int screenHeight = 600;

    int mouseCursorVisible = 1;

    int exitSignal = false; /** starts exit procedure as soon as true*/

    Controller *controller;
public:
    SDL_Renderer* renderer = NULL;
    Canvas *canvas;
    
    std::list<DrawLayerInterface*> drawLayers;

    
    FlatEngine();
    FlatEngine(const FlatEngine& orig);
    virtual ~FlatEngine();
    virtual void init(int argc, char** argv);
    void loop();
    void cleanup();

    virtual void postInit(SDL_Renderer* renderer);
    virtual void preInit(int argc, char** argv);

    void setExitSignal(int exitSignal);
    int getExitSignal() const;

    // Engine
    virtual Controller *initController() = 0;

    // Model
    virtual void update();

    // Controller
    virtual void processEvent(SDL_Event *event);

    // View
    void setVideoMode(int x, int y, int c, int flags);
    SDL_Texture* loadTexture(std::string path);
    virtual void draw(/*SDL_Renderer* renderer*/Canvas* renderer);
    void setRenderer(SDL_Renderer* renderer);
    SDL_Renderer* getRenderer() const;
    void setWindow(SDL_Window* window);
    SDL_Window* getWindow() const;
    void toggleFullscreen();
    int getScreenHeight() const;
    int getScreenWidth() const;
    void setScreenSize(int screenWidth, int screenHeight);
    void setMouseCursorVisible(int mouseCursorVisible);
    int getMouseCursorVisible() const;
    void setController(Controller* controller);
    Controller* getController() const;
    unsigned int  getMouseState(int *x, int *y);
};

#endif /* FLATENGINE_H */

