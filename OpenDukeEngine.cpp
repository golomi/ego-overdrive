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
 * File:   OpenDukeEngine.cpp
 * Author: Thomas Lenck
 * 
 * Created on 16. Februar 2021, 00:09
 */

#include "OpenDukeEngine.h"

#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <string>


#include "DukeImage.h"
#include "NonDukeObject.h"
#include "Powerup.h"
#include "Map.h"
#include "MapObject.h"
#include "Duke.h"
#include "Hud.h"
#include "MapLoader.h"
#include "CollisionDetector.h"
#include "Tools.h"
#include "Bullet.h"
#include "GameCanvas.h"
#include "DukeDrawSupport.h"
#include "DukeMiscSupport.h"
#include "LobbyController.h"
#include "Config.h"
#include "DukeUpdateContext.h"
#include "ListDrawLayer.h"
#include "SaveGame.h"


using namespace std;

OpenDukeEngine::OpenDukeEngine() : episode(1) {

}

void OpenDukeEngine::preInit(int argc, char** argv) {
    setScreenSize(640, 400);
}

void OpenDukeEngine::postInit(SDL_Renderer* renderer) {

    DukeGameObject::setTextureContainer(getTextureContainer());

    WindowDrawer::setTextureContainer(getTextureContainer());
    TextWriter::setTextureContainer(getTextureContainer());

    gameCanvas = new GameCanvas(renderer, &viewPort);

    getTextureContainer()->loadCommon(renderer);

    bullet = new Bullet(0, 0);

    NonDukeObject::setTick(&tick);
    MapObject::setMap(&map);
}

void OpenDukeEngine::drawMainGame(Canvas * renderer) {
    drawMainDrop(renderer);
    drawWorld(renderer);
    hud.draw(renderer, duke[0].getProperties(), getTextureContainer());


    if (consoleActive)
        DebugOutput::draw(renderer);

}

void OpenDukeEngine::drawMainDrop(Canvas* renderer) {
    mainDrop.draw(renderer, this);
}

void OpenDukeEngine::drawLobby(Canvas *renderer) {
    SDL_Rect destRect = {0, 0, 320, 200};

    renderer->draw(getTextureContainer()->getTexture(DN_TEXTURE), NULL, &destRect);

    switch (getLobbyState()) {
        case MAIN_MENU:
            windowDrawer.draw(renderer, 3, 2, 12, 8);
            TextWriter::print(renderer, "OPENDUKE MAIN MENU\n------------------", 11 * 8, 6 * 8);
            TextWriter::print(renderer, "S)TART A NEW GAME\nR)ESTORE AN OLD GAME\nI)NSTRUCTIONS\nO)RDERING INFORMATION\nG)AME SETUP\nH)IGH SCORES\nP)REVIEWS/MAIN DEMO!\nV)IEW USER DEMO\nT)ITLE SCREEN\nC)REDITS\nQ)UIT TO OS", 10 * 8, 9 * 8);
            break;
        case CAMPAIGN:
            windowDrawer.draw(renderer, 3, 2, 12, 8);
            TextWriter::print(renderer, "CHOOSE CAMPAIGN\n---------------", 11 * 8, 6 * 8);
            TextWriter::print(renderer, "1)EPISODE 1\n2)EPISODE 2\n3)EPISODE 3\n\nR)ETURN", 10 * 8, 9 * 8);

            break;
        default:
            break;
    }

    //testWindow->draw(renderer, NULL);
}

void OpenDukeEngine::draw(Canvas* renderer) {

    renderer->renderClear();

    switch (getState()) {
        case STARTUP:
            // TODO: show splash screen and wait a few seconds or wait for user interaction
            break;
        case LOBBY:
            drawLobby(renderer);
            break;
        case INITWORLD:
            break;
        case PLAY:
            drawMainGame(renderer);
            break;
        case CLEANUPWORLD:
            break;
        case END:
            break;
        default:
            break;
    }

}

void OpenDukeEngine::loadMap(std::string fileName) {

    MapLoader::load(fileName, &map, &duke[0], objectVector, rawMap);

    viewPort.setShiftX(duke[0].getX() - SCREEN_MAP_AREA_TILE_WIDTH * TILE_WIDTH / 2);
    viewPort.setShiftY(duke[0].getY() - SCREEN_MAX_SHIFT_DISTANCE_Y * TILE_WIDTH);
}


// TODO: move to separate class
// TODO: make method independet from viewPort

void OpenDukeEngine::drawMap(Canvas* renderer) {
    //    mapLayer.draw(renderer, this);



    int shiftX = viewPort.getShiftX();
    int shiftY = viewPort.getShiftY();

    SDL_Rect rect;
    SDL_Rect rect2;


    rect.x = 0;
    rect.y = 0;
    rect.w = TILE_WIDTH;
    rect.h = TILE_HEIGHT;

    rect2.x = 0;
    rect2.y = 0;
    rect2.w = TILE_WIDTH;
    rect2.h = TILE_HEIGHT;




    if (shiftX >= (MAP_WIDTH - SCREEN_MAP_AREA_TILE_WIDTH) * TILE_WIDTH)
        shiftX = (MAP_WIDTH - SCREEN_MAP_AREA_TILE_WIDTH - 1) * TILE_WIDTH;


    if (shiftY >= (MAP_HEIGHT - SCREEN_MAP_AREA_TILE_HEIGHT) * TILE_WIDTH)
        shiftY = (MAP_HEIGHT - SCREEN_MAP_AREA_TILE_HEIGHT - 1) * TILE_WIDTH;

    for (int y = 0; y < SCREEN_MAP_AREA_TILE_HEIGHT + 1; y++) {
        for (int x = 0; x < SCREEN_MAP_AREA_TILE_WIDTH + 1; x++) {
            unsigned short int tile = map.getTile(x + shiftX / TILE_WIDTH, y + shiftY / TILE_HEIGHT);

            if (tile == 0) {
                // 0: transparent for the background, so we have to do nothing
            } else if (tile == 0x0020) {
                // 0x20: draw second drop
                rect.x = (x * TILE_WIDTH - shiftX % TILE_WIDTH);
                rect.y = (y * TILE_HEIGHT - shiftY % TILE_HEIGHT);

                rect2.x = (x * TILE_WIDTH - shiftX % TILE_WIDTH);
                rect2.y = (y * TILE_HEIGHT - shiftY % TILE_HEIGHT);

                renderer->draw(getTextureContainer()->getTexture(DROP2_TEXTURE), &rect, &rect2);


            } else if (tile < 0x2fff) {
                // 0x0001 - 0x2fff, except 0x0020: normal tile
                int fileIndex = tile / 1536;
                int rowInFile = (tile % 1536) / 2;

                DukeDrawSupport::drawTile(renderer, getTextureContainer()->getTexture(BACK_SOLID_TEXTURE + fileIndex),
                        tile < 0x0600 ? rowInFile + (tick) % 4 * TILE_HEIGHT :
                        rowInFile,
                        x * TILE_WIDTH - shiftX % TILE_WIDTH, y * TILE_HEIGHT - shiftY % TILE_HEIGHT);
            }
        }
    }
}

void OpenDukeEngine::drawWorld(Canvas* canvas) {

    SDL_Rect rect;


    rect.x = SCREEN_MAP_AREA_OFFSET_X*RESIZE_FACTOR_X;
    rect.y = SCREEN_MAP_AREA_OFFSET_Y*RESIZE_FACTOR_Y;
    rect.w = SCREEN_MAP_AREA_TILE_WIDTH * TILE_WIDTH*RESIZE_FACTOR_X;
    rect.h = SCREEN_MAP_AREA_TILE_HEIGHT * TILE_HEIGHT*RESIZE_FACTOR_Y;

    // TODO: do something else instead of retreiving the SDL renderer
    SDL_RenderSetViewport(canvas->getRenderer(), &rect);

    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_MAP_AREA_TILE_WIDTH * TILE_WIDTH*RESIZE_FACTOR_X;
    rect.h = SCREEN_MAP_AREA_TILE_HEIGHT * TILE_HEIGHT*RESIZE_FACTOR_Y;
    // TODO: do something else instead of retreiving the SDL renderer
    SDL_RenderSetClipRect(canvas->getRenderer(), &rect);

    drawMap(canvas);


    drawObjects(gameCanvas);

    duke[0].draw(gameCanvas, getTextureContainer());
    bullet->draw(gameCanvas, getTextureContainer());


    SDL_RenderSetClipRect(canvas->getRenderer(), NULL);
    SDL_RenderSetViewport(canvas->getRenderer(), NULL);

}

void OpenDukeEngine::drawObjects(Canvas *canvas) {

    for (MapObject*& value : objectVector) {
        value->draw(canvas, getTextureContainer());
    }
}

bool isDestroyed(MapObject* value) {
    if (value->shouldBeRemoved() == true) {
        /*  MapObject *successor = value->getSuccessorObject();
          if(successor!=NULL) {
              objectVector
          }*/
        return (true);
    } else {
        return (false);
    }
}

void OpenDukeEngine::initWorld() {
    duke[0].reset();


    std::string directory = "";

    switch (episode) {
        case 1:
            directory = Config::getEntry("episode1directory");
            break;
        case 2:
            directory = Config::getEntry("episode2directory");
            break;
        case 3:
            directory = Config::getEntry("episode3directory");
            break;
        default:
            // TODO: error, there is no episode beside 1,2 and 3, throw exception
            break;

    }
    std::string mapFileName;
    if (isIntermediateWorld == true) {
        mapFileName = DukeMiscSupport::generateDukeMapPath(2, episode, "dukedata");
    } else {
        mapFileName = DukeMiscSupport::generateDukeMapPath(worldIndex, episode, "dukedata");
    }

    loadMap(mapFileName);



    std::string dropFileName = "";
    std::string drop2FileName = "";

    if (WORLD_DEFINITIONS[episode - 1][worldIndex - 1].drop != DROP_BLACK) {
        dropFileName = DukeMiscSupport::generateDukeDropPath(WORLD_DEFINITIONS[episode - 1][worldIndex - 1].drop, episode, "dukedata");
    }

    if (WORLD_DEFINITIONS[episode - 1][worldIndex - 1].secondDrop != DROP_BLACK) {
        drop2FileName = DukeMiscSupport::generateDukeDropPath(WORLD_DEFINITIONS[episode - 1][worldIndex - 1].secondDrop, episode, "dukedata");
    }

    getTextureContainer()->loadDrops(renderer, dropFileName, drop2FileName);
}

void OpenDukeEngine::update() {

    // TODO: Currently fixed to 60 fps

    frameCounter++;

    oldTick = tick;
    tick = (frameCounter) / 4; //* 15 / 60;
    isNewTick = oldTick != tick;


    switch (getState()) {
        case STARTUP:
            // TODO: show splash screen and wait a few seconds or wait for user interaction
            setState(LOBBY);
            break;
        case LOBBY:
            break;
        case INITWORLD:
            initWorld();
            setState(PLAY);
            break;
        case PLAY:
            // TODO: put whole content of case PLAY in separete method
        {
            DukeUpdateContext *dukeUpdateContext = new DukeUpdateContext(getViewPort(), duke);
            // TODO: rebuild structure to reset, interaction, update
            if (isNewTick) {

                // TODO: iterate through all Dukes
                duke[0].update(dukeUpdateContext);

                for (MapObject*& object : objectVector) {
                    object->update(dukeUpdateContext);
                }
                CollisionDetector::executeTouch(&duke[0], objectVector);

                CollisionDetector::executeHit(bullet, objectVector);

                for (MapObject*& object : objectVector) {
                    ((NonDukeObject*) object)->clearStandon();
                }

                CollisionDetector::executeStandon(&duke[0], objectVector);

                for (MapObject*& object : objectVector) {

                    MapObject *newObject;
                    if (object->shouldBeRemoved() && (newObject = ((NonDukeObject*) object)->getSuccessorObject()) != NULL) {
                        objectVector.push_back(newObject);
                    }
                }
                // TODO: objects are getting removed from the list, but not getting deleted up tp now
                objectVector.remove_if(isDestroyed);


            }



            // TODO: why is bullet->update outside "isNewTick"
            bullet->update(dukeUpdateContext);

            delete dukeUpdateContext;

            // TODO: why ist creation of solid map outside "isNewTick"
            map.flushTempSolid();

            for (std::list<MapObject*>::iterator it = objectVector.begin(); it != objectVector.end(); ++it) {
                MapObject *object = *it;
                ((NonDukeObject*) object)->updateSolidMap();
            }
        }


            break;
        case CLEANUPWORLD:
            break;
        case END:
            // TODO: End splash
            break;
        default:
            // TODO: Error Message
            break;
    }
}

//DebugOutput *OpenDukeEngine::getDebugOutput() {
//
//    return &debugOutput;
//}

Controller *OpenDukeEngine::initController() {
    mainGameController = new MainGameController(this);
    lobbyController = new LobbyController(this);

    return (lobbyController);
}

void OpenDukeEngine::action(int dukeNum, int type) {

    CollisionDetector::executeAction(&duke[0], type, objectVector, this);
}

void OpenDukeEngine::fire(int dukeNum) {

    bullet->fire(duke[0].getX(), duke[0].getY(), duke[0].getViewDirection());
}

void OpenDukeEngine::jump(int dukeNum) {

    duke[0].jump();
}

void OpenDukeEngine::moveLeft(int dukeNum) {

    duke[0].setMove(-1);
    duke[0].setViewDirection(-1);
}

void OpenDukeEngine::moveRight(int dukeNum) {

    duke[0].setMove(+1);
    duke[0].setViewDirection(+1);
}

void OpenDukeEngine::stopLeft(int dukeNum) {

    if (duke[0].getMove() == -1)
        duke[0].setMove(0);

}

void OpenDukeEngine::stopRight(int dukeNum) {

    if (duke[0].getMove() == 1)
        duke[0].setMove(0);
}

void OpenDukeEngine::outputDebugRawMapTile(int x, int y) {

    int tileX = (x + (viewPort.getShiftX() - SCREEN_MAP_AREA_OFFSET_X) * RESIZE_FACTOR_X) / (TILE_WIDTH * RESIZE_FACTOR_X);
    int tileY = (y + (viewPort.getShiftY() - SCREEN_MAP_AREA_OFFSET_Y) * RESIZE_FACTOR_Y) / (TILE_HEIGHT * RESIZE_FACTOR_Y);
    // score
    std::stringstream tileStringFormat;
    tileStringFormat << "Raw map tile: 0x" << hex << uppercase << setw(4) << setfill('0') << rawMap[tileY * MAP_WIDTH + tileX];
    tileString = tileStringFormat.str();
    DebugOutput::addLine(tileString);
}

void OpenDukeEngine::outputDebugPosInMapFile(int x, int y) {

    int tileX = (x + (viewPort.getShiftX() - SCREEN_MAP_AREA_OFFSET_X) * RESIZE_FACTOR_X) / (TILE_WIDTH * RESIZE_FACTOR_X);
    int tileY = (y + (viewPort.getShiftY() - SCREEN_MAP_AREA_OFFSET_Y) * RESIZE_FACTOR_Y) / (TILE_HEIGHT * RESIZE_FACTOR_Y);
    // score
    std::stringstream tileStringFormat;
    tileStringFormat << "Pos in map file: 0x" << hex << uppercase << setw(4) << setfill('0') << tileX + tileY * 0x100;
    tileString = tileStringFormat.str();
    DebugOutput::addLine(tileString);
}

void OpenDukeEngine::toggleConsoleActive() {

    consoleActive ^= true;
}

void OpenDukeEngine::startWorld(int campaign) {
    worldIndex = 1;
    isIntermediateWorld = false;
    episode = campaign;

    setState(INITWORLD);
    setController(mainGameController);
}

void OpenDukeEngine::finishWorld() {
    DebugOutput::addLine("Exit: finished map");
    duke->getProperties()->clearKeys();
    if (isIntermediateWorld == true) {
        isIntermediateWorld = false;
    } else if (worldIndex < MAX_WORLD_INDEX) {
        if (worldIndex == 1) {
            worldIndex = 3;
        } else {
            worldIndex++;
        }
        isIntermediateWorld = true;
    } else {
        // TODO: episode finished
    }
    setState(INITWORLD);
}

void OpenDukeEngine::restartWorld() {
    DebugOutput::addLine("Restart");
    setState(INITWORLD);
}

void OpenDukeEngine::action(MapObject *object, Action action, void *parameter) {
    if (action == FinishedWorld) {
        finishWorld();
    } else if (action == DukeDied) {
        DebugOutput::addLine("Duke died");
    } else {
        DebugOutput::addLine("Unknown action" + action);
    }
}

bool OpenDukeEngine::request(MapObject *object, Request request, void *parameter) {
    DebugOutput::addLine("Request " + request);

    switch (request) {
        case AllowRedDoorOpen:
            return (duke[0].getProperties()->getInventory() & INVENTORY_RED_KEY);
            break;
        case AllowGreenDoorOpen:
            return (duke[0].getProperties()->getInventory() & INVENTORY_GREEN_KEY);
            break;
        case AllowBlueDoorOpen:
            return (duke[0].getProperties()->getInventory() & INVENTORY_BLUE_KEY);
            break;
        case AllowPurpleDoorOpen:
            return (duke[0].getProperties()->getInventory() & INVENTORY_PURPLE_KEY);
            break;
    }

    return false;
}

void OpenDukeEngine::cheat(CheatCommand command, unsigned int value) {
    switch (command) {
        case ADDINVENTORY:
            duke[0].getProperties()->addInventory(value);
            break;
        case REMOVEINVENTORY: break;
        case ADDHEALTH: break;
        case SUBHEALTH: break;
        case JUMPTONEXTWORLD: break;
        case JUMPTOPREVWORLD: break;
        case RESTARTWORLD: break;
        case QUICKLOAD:
        {
            DukeSaveGame data = SaveGame::load("quicksave.dnx");
            duke[0].setX(data.dukeX * 8);
            duke[0].setY(data.dukeY);

            //TODO: currently view port has to be set manually
            viewPort.setShiftX(duke[0].getX() - SCREEN_MAP_AREA_TILE_WIDTH * TILE_WIDTH / 2);
            viewPort.setShiftY(duke[0].getY() - SCREEN_MAX_SHIFT_DISTANCE_Y * TILE_WIDTH);
        }
            break;
        case QUICKSAVE:
        {
            DukeSaveGame data;

            data.viewX = 0;
            data.viewY = 0;
            data.dukeX = duke[0].getX() / 8;
            data.dukeY = duke[0].getY();

            SaveGame::save("quicksave.dnx", data);
        }
            break;
        default:
            break;
    }
}