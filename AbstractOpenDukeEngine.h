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
 * File:   AbstractOpenDukeEngine.h
 * Author: thomas
 *
 * Created on 4. April 2022, 23:34
 */

#ifndef ABSTRACTOPENDUKEENGINE_H
#define ABSTRACTOPENDUKEENGINE_H

#include "FlatEngine.h"

enum STATES {
    STARTUP, LOBBY, INITWORLD, PLAY, CLEANUPWORLD, END
};

enum LobbyState {
    MAIN_MENU, CAMPAIGN
};

class AbstractOpenDukeEngine : public FlatEngine {
private:
    STATES state = STARTUP;
    LobbyState lobbyState = MAIN_MENU;

public:
    AbstractOpenDukeEngine();

    virtual void action(int dukeNum, int type) = 0;
    virtual void fire(int dukeNum) = 0;
    virtual void jump(int dukeNum) = 0;
    virtual void moveLeft(int dukeNum) = 0;
    virtual void moveRight(int dukeNum) = 0;
    virtual void stopLeft(int dukeNum) = 0;
    virtual void stopRight(int dukeNum) = 0;

    virtual void outputDebugRawMapTile(int x, int y) = 0;
    virtual void outputDebugPosInMapFile(int x, int y) = 0;

    virtual void toggleConsoleActive() = 0;

    virtual void startWorld(int campaign) = 0;

    void setState(STATES state);
    STATES getState() const;

    void setLobbyState(LobbyState lobbyState);
    LobbyState getLobbyState() const;

    virtual void finishWorld() = 0;
    virtual void restartWorld() = 0;
    
};

#endif /* ABSTRACTOPENDUKEENGINE_H */

