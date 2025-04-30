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
 * File:   Camera.cpp
 * Author: thomas
 * 
 * Created on 29. Januar 2022, 23:14
 */

#include "Camera.h"
#include "DukeUpdateContext.h"

//Camera::Camera(int x, int y) : NonDukeObject(x, y, 1, 1) {
//}

Camera::Camera(int x, int y, int type) : NonDukeObject(x, y, 1, 1, type) {
}

//Camera::~Camera() {
//}
// void Camera::update(ViewPort *viewPort, Duke *duke)

void Camera::update(UpdateContext *updateContext) {
    

    if (getX() > ((DukeUpdateContext*)updateContext)->getDuke(0)->getX()) {
        setViewDirection(DIRECTION_LEFT);
    } else if (getX() < ((DukeUpdateContext*)updateContext)->getDuke(0)->getX()) {
        setViewDirection(DIRECTION_RIGHT);
    } else {
        setViewDirection(0);
    }
}

