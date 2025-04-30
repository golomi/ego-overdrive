/*
 * Copyright (C) 2024 thomas
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
 * File:   UpdateContext.cpp
 * Author: thomas
 * 
 * Created on 12. Januar 2024, 00:31
 */

#include "UpdateContext.h"

UpdateContext::UpdateContext(DukeViewPort *viewPort) : viewPort(viewPort){
//    setViewPort(viewPort);
}

UpdateContext::~UpdateContext() {
}

//void UpdateContext::setViewPort(ViewPort *viewPort) {
//    this->viewPort = viewPort;
//
//}

DukeViewPort *UpdateContext::getViewPort() {
    return (viewPort);
}
