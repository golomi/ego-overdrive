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

/*! 
 * File:   OpenDukeEngine.h
 * Author: Thomas Lenck
 *
 * Created on 16. Februar 2021, 00:09
 */


#ifndef DUX_H
#define DUX_H

#include <cstdlib>
#include <list>
#include <vector>


#include <SDL2/SDL.h>


#include "FlatEngine.h"
#include "DukeTextureContainer.h"
#include "NonDukeObject.h"
#include "DukeDefinitions.h"
#include "Map.h"
#include "Duke.h"
#include "DukeProperties.h"
#include "Hud.h"
#include "DebugOutput.h"
#include "DukeViewPort.h"
#include "MainGameController.h"
#include "Bullet.h"
#include "GameCanvas.h"
#include "BaseCanvas.h"
#include "RenderContext.h"
#include "WindowDrawer.h"
#include "TextWriter.h"
#include "LobbyController.h"
#include "Window.h"

struct Position {
    int x;
    int y;
};


// TODO: remove separate defintitions for class NonDukeObject
class NonDukeObject;

class TestWindow : public Window {
public:

    TestWindow(int tileX, int tileY, int tileWidth, int tileHeight) :
    Window(tileX, tileY, tileWidth, tileHeight) {
    }

    virtual void draw(Canvas *canvas, DukeTextureContainer *textures) override {
        Window::draw(canvas, textures);

        TextWriter::print(canvas, "Test", getTileX() + 1, getTileY());
    }
};

enum CheatCommand {
    ADDINVENTORY, REMOVEINVENTORY, ADDHEALTH, SUBHEALTH, JUMPTONEXTWORLD, JUMPTOPREVWORLD, RESTARTWORLD, QUICKLOAD, QUICKSAVE
};

class OpenDukeEngine : public AbstractOpenDukeEngine, public RenderContext, public MapObjectNotifier {
private:

    //class MapLayer : public DrawLayerInterface {
    //    public:
    //
    //        virtual void draw(Canvas *canvas, RenderContext *context) override {
    //
    //            int shiftX = context->viewPort.getShiftX();
    //            int shiftY = context->viewPort.getShiftY();
    //
    //            SDL_Rect rect;
    //            SDL_Rect rect2;
    //
    //
    //            rect.x = 0;
    //            rect.y = 0;
    //            rect.w = TILE_WIDTH;
    //            rect.h = TILE_HEIGHT;
    //
    //            rect2.x = 0;
    //            rect2.y = 0;
    //            rect2.w = TILE_WIDTH;
    //            rect2.h = TILE_HEIGHT;
    //
    //
    //
    //
    //            if (shiftX >= (MAP_WIDTH - SCREEN_MAP_AREA_TILE_WIDTH) * TILE_WIDTH)
    //                shiftX = (MAP_WIDTH - SCREEN_MAP_AREA_TILE_WIDTH - 1) * TILE_WIDTH;
    //
    //
    //            if (shiftY >= (MAP_HEIGHT - SCREEN_MAP_AREA_TILE_HEIGHT) * TILE_WIDTH)
    //                shiftY = (MAP_HEIGHT - SCREEN_MAP_AREA_TILE_HEIGHT - 1) * TILE_WIDTH;
    //
    //            for (int y = 0; y < SCREEN_MAP_AREA_TILE_HEIGHT + 1; y++) {
    //                for (int x = 0; x < SCREEN_MAP_AREA_TILE_WIDTH + 1; x++) {
    //                    unsigned short int tile = map.getTile(x + shiftX / TILE_WIDTH, y + shiftY / TILE_HEIGHT);
    //
    //                    if (tile == 0) {
    //                        // 0: transparent for the background, so we have to do nothing
    //                    } else if (tile == 0x0020) {
    //                        // 0x20: draw second drop
    //                        rect.x = (x * TILE_WIDTH - shiftX % TILE_WIDTH);
    //                        rect.y = (y * TILE_HEIGHT - shiftY % TILE_HEIGHT);
    //
    //                        rect2.x = (x * TILE_WIDTH - shiftX % TILE_WIDTH);
    //                        rect2.y = (y * TILE_HEIGHT - shiftY % TILE_HEIGHT);
    //
    //                        canvas->draw(getTextureContainer()->getTexture(DROP2_TEXTURE), &rect, &rect2);
    //
    //
    //                    } else if (tile < 0x2fff) {
    //                        // 0x0001 - 0x2fff, except 0x0020: normal tile
    //                        int fileIndex = tile / 1536;
    //                        int rowInFile = (tile % 1536) / 2;
    //
    //                        DukeDrawSupport::drawTile(canvas, getTextureContainer()->getTexture(BACK_SOLID_TEXTURE + fileIndex),
    //                                tile < 0x0600 ? rowInFile + (tick) % 4 * TILE_HEIGHT :
    //                                rowInFile,
    //                                x * TILE_WIDTH - shiftX % TILE_WIDTH, y * TILE_HEIGHT - shiftY % TILE_HEIGHT);
    //                    }
    //                }
    //            }
    //        }
    //    } mapLayer;

    class MainDrop : public DrawLayerInterface {
    public:

        virtual void draw(Canvas *canvas, RenderContext *context) override {
            SDL_Rect rect;
            rect.x = TILE_WIDTH;
            rect.y = TILE_WIDTH;
            rect.w = SCREEN_MAP_AREA_TILE_WIDTH * TILE_WIDTH;
            rect.h = SCREEN_MAP_AREA_TILE_HEIGHT * TILE_WIDTH;
            canvas->draw(getTextureContainer()->getTexture(DROP_TEXTURE), NULL, &rect);
        }
    } mainDrop;

    WindowDrawer windowDrawer;

    // TestWindow *testWindow = new TestWindow(5, 5, 5, 5);

    std::list<MapObject*> objectVector;

    bool moveTick = 0;
    Map map;

    int worldIndex = 1; /** index of the current world */
    int isIntermediateWorld = false; /** intermediate world means the small, always looks the same world beetween to real worlds, where the player is able to safe*/
    int episode; /** episode currently played */


    int frameCounter = 0;
    int tick = 0, oldTick = 0;
    bool isNewTick = true; /** needed as graphic update rate ist higher than game update rate */

    Bullet *bullet;

    static const int DUKE_MAX = 2; // maximum number of dukes

    int dukeCount = 2; // actual number of dukes

    //Duke duke;
    Duke duke[DUKE_MAX]; /** the player character "Duke", intended for multiplayer, which is an array of Dukes*/


    GameCanvas *gameCanvas;

    Hud hud;
    //DebugOutput debugOutput;

    bool consoleActive = false;

    bool collision = false;

    MainGameController *mainGameController = NULL;
    LobbyController *lobbyController = NULL;

    // TODO: temporary for investigating objects
    std::string tileString = "";
    unsigned short int rawMap[MAP_WIDTH*MAP_HEIGHT];


public:

    OpenDukeEngine();

    // Access
    //*getDebugOutput();

    // Init
    virtual void postInit(SDL_Renderer* renderer) override;
    virtual void preInit(int argc, char** argv) override;
    virtual Controller *initController() override;
    void initWorld();

    // Draw
    virtual void draw(Canvas* renderer) override;

    /**
     * 
     * @param canvas
     */
    void drawObjects(Canvas *canvas);

    /**
     * The main drawing method
     * @param renderer
     */
    void drawMainGame(Canvas * renderer);

    /**
     * Draws the main backdrop (background) of the game
     * @param renderer
     */
    void drawMainDrop(Canvas* renderer);

    /**
     * Draws the map
     * @param canvas
     */
    void drawMap(Canvas* canvas);

    /**
     * Draws foreground of the game
     * @param renderer
     * @param shiftX
     * @param shiftY
     */
    void drawWorld(Canvas* renderer);

    /**
     * 
     * @param renderer
     */
    void drawLobby(Canvas * renderer);

    virtual void update() override;


    // Commands
    void action(int dukeNum, int type) override;
    void fire(int dukeNum)override;
    void jump(int dukeNum)override;
    void moveLeft(int dukeNum)override;
    void moveRight(int dukeNum)override;
    void stopLeft(int dukeNum)override;
    void stopRight(int dukeNum)override;

    // Debuging
    void outputDebugRawMapTile(int x, int y)  override;
    void outputDebugPosInMapFile(int x, int y)  override;
    void toggleConsoleActive()  override;


    // Game control
    virtual void finishWorld()  override;
    virtual void restartWorld()  override;
    virtual void startWorld(int campaign)  override;
    void startNewGame(int episode);
    void loadGame(std::string fileName);
    void loadMap(std::string text);


    // Object interaction
    virtual void action(MapObject *object, Action action, void *parameter) override;
    virtual bool request(MapObject *object, Request request, void *parameter)  override;
    void cheat(CheatCommand command, unsigned int value);

};


#endif /* DUX_H */

