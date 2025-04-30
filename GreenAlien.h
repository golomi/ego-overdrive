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
 * File:   GreenAlien.h
 * Author: thomas
 *
 * Created on 30. April 2022, 23:26
 */

#ifndef GREENALIEN_H
#define GREENALIEN_H

#include "NonDukeObject.h"

class GreenAlien : public NonDukeObject {
private:
public:
    //    GreenAlien(int x, int y);
    GreenAlien(int x, int y, int type);
    virtual ~GreenAlien();
    virtual void update(UpdateContext *updateContext) override;

    bool isObstacleAhead() override;
    bool isEdgeAhead() override;
    bool isEdgeLeftAhead();
    bool isEdgeRightAhead();

    virtual void draw(Canvas *canvas, DukeTextureContainer *textures) override;
};

#endif /* GREENALIEN_H */

