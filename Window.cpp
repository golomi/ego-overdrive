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
 * File:   Window.cpp
 * Author: thomas
 * 
 * Created on 14. September 2022, 18:26
 */

#include "Window.h"

#include "WindowDrawer.h"

Window::Window(int tileX, int tileY, int tileWidth, int tileHeight) : tileX(tileX), tileY(tileY),
tileWidth(tileWidth), tileHeight(tileHeight) {
}

Window::~Window() {
}

void Window::draw(Canvas *canvas, DukeTextureContainer *textures) {
    WindowDrawer::draw(canvas, tileX, tileY, tileWidth, tileHeight);
}

void Window::setTileHeight(int tileHeight) {
    this->tileHeight = tileHeight;
}

int Window::getTileHeight() const {
    return tileHeight;
}

void Window::setTileWidth(int tileWidth) {
    this->tileWidth = tileWidth;
}

int Window::getTileWidth() const {
    return tileWidth;
}

void Window::setTileY(int tileY) {
    this->tileY = tileY;
}

int Window::getTileY() const {
    return tileY;
}

void Window::setTileX(int tileX) {
    this->tileX = tileX;
}

int Window::getTileX() const {
    return tileX;
}

//Canvas *Window::getElderCanvas() {
//
//}
//
//SDL_Renderer* Window::getRenderer() {
//
//}