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
 * File:   DukeController.cpp
 * Author: thomas
 * 
 * Created on 4. April 2022, 22:58
 */

#include "MainGameController.h"
#include "NonDukeObject.h"
#include "OpenDukeEngine.h"

#include <SDL2/SDL.h>

MainGameController::MainGameController(AbstractOpenDukeEngine *engine) {
    this->engine = engine;
}

void MainGameController::update() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        processEvent(&e);
    }
}

void MainGameController::processEvent(SDL_Event *event) {

    if (event->type == SDL_QUIT) {
        engine->setExitSignal(true);
    } else if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                engine->setExitSignal(true);
                break;
            case SDLK_RETURN:
                engine->toggleFullscreen();
                break;

                // moving the view
                /* case SDLK_w:
                     viewPort.addShiftY(-8);
                     break;
                 case SDLK_s:
                     viewPort.addShiftY(+8);
                     break;
                 case SDLK_a:
                     viewPort.addShiftX(-8);
                     break;
                 case SDLK_d:
                     viewPort.addShiftX(+8);
                     break;*/

                // duke actions
            case SDLK_LEFT:
                engine->moveLeft(0);
                break;
            case SDLK_RIGHT:
                engine->moveRight(0);
                break;
                //case SDLK_RCTRL:
            case SDLK_LCTRL:
                engine->jump(0);
                break;
            case SDLK_UP:
                engine->action(0, 1);
                break;
            case SDLK_LALT:
                engine->fire(0);
                break;
            case SDLK_F1:
                engine->toggleConsoleActive();
                break;
            // "developer keys"
            case SDLK_n:
                engine->finishWorld();
                break;
            case SDLK_r:
                engine->restartWorld();
                break;
            case SDLK_s:
                ((OpenDukeEngine*) engine)->cheat(QUICKSAVE,0);
                break;
            case SDLK_l:
                ((OpenDukeEngine*) engine)->cheat(QUICKLOAD,0);
                break;
            case SDLK_PLUS:
                ((OpenDukeEngine*) engine)->cheat(ADDINVENTORY, INVENTORY_ALL);
                break;
        }
    } else if (event->type == SDL_KEYUP) {
        switch (event->key.keysym.sym) {
                // moving duke
            case SDLK_LEFT:
                engine->stopLeft(0);
                break;
            case SDLK_RIGHT:
                engine->stopRight(0);
                break;
            case SDLK_UP:
                engine->action(0, 0);
                break;
        }
    } else if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        Uint32 mouseButton = SDL_GetMouseState(&x, &y);

        if (mouseButton & 1) {
            engine->outputDebugRawMapTile(x, y);
        } else if (mouseButton & 2) {
            engine->outputDebugPosInMapFile(x, y);
        }
    }
}