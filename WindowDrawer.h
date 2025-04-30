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
 * File:   WindowDrawer.h
 * Author: thomas
 *
 * Created on 5. August 2022, 13:48
 */

#include "DukeTextureContainer.h"
#include "Canvas.h"

#ifndef WINDOWDRAWER_H
#define WINDOWDRAWER_H

class WindowDrawer {
private:
    static DukeTextureContainer *textureContainer;
public:
    WindowDrawer();
    virtual ~WindowDrawer();
    
    /**
     * Draws a window with frame tiles of the border textures 18 ff including back
     * 
     * @param renderer the renderer
     * @param x x position of the window in tile grid
     * @param y y position of the window in tile grid
     * @param width width of the window in tile grid
     * @param height height of the window int tile grid
     */
    static void draw(Canvas* renderer, int x, int y, int width, int height);
    static void setTextureContainer(DukeTextureContainer* textureContainer);
};

#endif /* WINDOWDRAWER_H */

