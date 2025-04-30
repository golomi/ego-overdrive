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
 * File:   LobbyController.h
 * Author: thomas
 *
 * Created on 6. August 2022, 01:07
 */

#ifndef LOBBYCONTROLLER_H
#define LOBBYCONTROLLER_H

#include <SDL2/SDL.h>

#include "Controller.h"

#include "AbstractOpenDukeEngine.h"

class LobbyController : public Controller {
private:
    AbstractOpenDukeEngine *engine;
public:
    LobbyController(AbstractOpenDukeEngine *engine);
    virtual void update()  override;
    virtual void processEvent(SDL_Event *e);
};

#endif /* LOBBYCONTROLLER_H */

