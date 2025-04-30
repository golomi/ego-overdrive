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
 * File:   DukeGameObject.cpp
 * Author: thomas
 * 
 * Created on 18. September 2022, 21:42
 */

#include "DukeGameObject.h"

DukeTextureContainer *DukeGameObject::textureContainer = NULL;

void DukeGameObject::setTextureContainer(DukeTextureContainer* textureContainer) {
    DukeGameObject::textureContainer = textureContainer;
}

DukeTextureContainer* DukeGameObject::getTextureContainer() {
    return textureContainer;
}

DukeGameObject::DukeGameObject() {
}

DukeGameObject::~DukeGameObject() {
}

void DukeGameObject::draw(Canvas *canvas) {
    draw(canvas, getTextureContainer());
}