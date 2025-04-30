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
 * File:   LobbyController.cpp
 * Author: thomas
 * 
 * Created on 6. August 2022, 01:07
 */

#include "LobbyController.h"


#include <SDL2/SDL.h>

LobbyController::LobbyController(AbstractOpenDukeEngine *engine) {
    this->engine = engine;
}

void LobbyController::update() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        processEvent(&e);
    }
}

void LobbyController::processEvent(SDL_Event *event) {

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


            case SDLK_1:
                switch (engine->getLobbyState()) {

                    case CAMPAIGN:
                        engine->startWorld(1);
                        break;
                    default:
                        break;
                }
                break;
            case SDLK_2:
                switch (engine->getLobbyState()) {

                    case CAMPAIGN:
                        engine->startWorld(2);
                        break;
                    default:
                        break;
                }
                break;
            case SDLK_3:
                switch (engine->getLobbyState()) {

                    case CAMPAIGN:
                        engine->startWorld(3);
                        break;
                    default:
                        break;
                }
                break;
            case SDLK_r:
                switch (engine->getLobbyState()) {

                    case CAMPAIGN:
                            engine->setLobbyState(MAIN_MENU);
                        break;
                    default:
                        break;
                }
                break;
            case SDLK_s:
                switch (engine->getLobbyState()) {
                    case MAIN_MENU:
                        engine->setLobbyState(CAMPAIGN);
                        break;
                    case CAMPAIGN:

                        break;
                    default:
                        break;
                }

                break;
            case SDLK_i:
                break;
            case SDLK_o:
                break;
            case SDLK_g:
                break;
            case SDLK_h:
                break;
            case SDLK_p:
                break;
            case SDLK_v:
                break;
            case SDLK_t:
                break;
            case SDLK_c:
                break;
            case SDLK_q:
                engine->setExitSignal(true);
                break;
            default:
                break;
        }
    }
}
