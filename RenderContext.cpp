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
 * File:   RenderContext.cpp
 * Author: thomas
 * 
 * Created on 9. Februar 2022, 09:50
 */

#include "RenderContext.h"

DukeTextureContainer *RenderContext::textureContainer = NULL;

RenderContext::RenderContext() {
    textureContainer = new DukeTextureContainer();
}

DukeViewPort *RenderContext::getViewPort() {
    return &viewPort;
}

RenderContext::RenderContext(const RenderContext& orig) {
}

RenderContext::~RenderContext() {
}

//static void RenderContext::setTextureContainer(TextureContainer *textureContainer) {
//    RenderContext::textureContainer = textureContainer;
//}

DukeTextureContainer *RenderContext::getTextureContainer() {
    return textureContainer;
}

