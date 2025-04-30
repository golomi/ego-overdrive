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
 * File:   Window.h
 * Author: thomas
 *
 * Created on 14. September 2022, 18:26
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "DukeGameObject.h"
#include "Canvas.h"

//class CascadedCanvas : public Canvas {
//    virtual Canvas *getElderCanvas();
//};

class Window : public DukeGameObject/*, public CascadedCanvas*/ {
private:
    int tileX, tileY;
    int tileWidth, tileHeight;
    
public:
    Window(int tileX, int tileY, int tileWidth, int tileHeight);
    virtual ~Window();
    virtual void draw(Canvas *canvas, DukeTextureContainer *textures);
    void setTileHeight(int tileHeight);
    int getTileHeight() const;
    void setTileWidth(int tileWidth);
    int getTileWidth() const;
    void setTileY(int tileY);
    int getTileY() const;
    void setTileX(int tileX);
    int getTileX() const;

//    virtual Canvas *getElderCanvas();
//    virtual SDL_Renderer* getRenderer();
};

#endif /* WINDOW_H */

