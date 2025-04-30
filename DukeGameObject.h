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
 * File:   DukeGameObject.h
 * Author: thomas
 *
 * Created on 18. September 2022, 21:42
 */

#ifndef DUKEGAMEOBJECT_H
#define DUKEGAMEOBJECT_H

#include "DrawInterface.h"

#include "DukeTextureContainer.h"

class DukeGameObject : public DrawInterface {
private:
    static DukeTextureContainer *textureContainer;
public:
    static void setTextureContainer(DukeTextureContainer* textureContainer);
    DukeTextureContainer* getTextureContainer();

    DukeGameObject();
    virtual ~DukeGameObject();
    
    virtual void draw(Canvas *canvas) override;
    virtual void draw(Canvas *canvas, DukeTextureContainer *textures) = 0;

};

#endif /* DUKEGAMEOBJECT_H */

