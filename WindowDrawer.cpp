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
 * File:   WindowDrawer.cpp
 * Author: thomas
 * 
 * Created on 5. August 2022, 13:48
 */

#include "WindowDrawer.h"
#include "DukeDefinitions.h"
#include "DukeDrawSupport.h"

DukeTextureContainer *WindowDrawer::textureContainer = nullptr;

WindowDrawer::WindowDrawer() {
}

WindowDrawer::~WindowDrawer() {
}

void WindowDrawer::draw(Canvas* renderer, int x, int y, int width, int height) {
    //static SDL_Rect sourceRect = {0, 0, FONT_WIDTH, FONT_HEIGHT};
    // static SDL_Rect destRect = {0, 0, FONT_WIDTH*RESIZE_FACTOR_X, FONT_HEIGHT * RESIZE_FACTOR_Y};

    const int WINDOW_BACK = 17;
    const int WINDOW_BORDER_TOP_LEFT = 18;
    const int WINDOW_BORDER_TOP_RIGHT = 19;
    const int WINDOW_BORDER_BOTTOM_LEFT = 20;
    const int WINDOW_BORDER_BOTTOM_RIGHT = 21;
    const int WINDOW_BORDER_LEFT = 22;
    const int WINDOW_BORDER_RIGHT = 23;
    const int WINDOW_BORDER_TOP = 24;
    const int WINDOW_BORDER_BOTTOM = 25;

    // TODO: check width or height for upper limits
    if (width < 2 || height < 2) {
        return;
    }


    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), WINDOW_BORDER_TOP_LEFT*TILE_HEIGHT, x*TILE_WIDTH, y * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), WINDOW_BORDER_TOP_RIGHT*TILE_HEIGHT, (x + width) * TILE_WIDTH, y * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), WINDOW_BORDER_BOTTOM_LEFT*TILE_HEIGHT, x*TILE_WIDTH, (y + height) * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), WINDOW_BORDER_BOTTOM_RIGHT*TILE_HEIGHT, (x + width) * TILE_WIDTH, (y + height) * TILE_HEIGHT);

    for (int i = x + 1; i < x + width; i++) {
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), WINDOW_BORDER_TOP*TILE_HEIGHT, i*TILE_WIDTH, y * TILE_HEIGHT);
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), WINDOW_BORDER_BOTTOM*TILE_HEIGHT, i * TILE_WIDTH, (y + height) * TILE_HEIGHT);
    }

    for (int i = y + 1; i < y + height; i++) {
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), WINDOW_BORDER_LEFT*TILE_HEIGHT, x*TILE_WIDTH, i * TILE_HEIGHT);
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), WINDOW_BORDER_RIGHT*TILE_HEIGHT, (x + width) * TILE_WIDTH, i * TILE_HEIGHT);
    }

    for (int i = x + 1; i < x + width; i++)
        for (int j = y + 1; j < y + height; j++) {
            {
                DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), WINDOW_BACK*TILE_HEIGHT, i*TILE_WIDTH, j * TILE_HEIGHT);
            }
        }
}

void WindowDrawer::setTextureContainer(DukeTextureContainer* textureContainer) {
    WindowDrawer::textureContainer = textureContainer;
}