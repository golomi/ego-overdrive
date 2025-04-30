/*
 * Copyright (C) 2023 thomas
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
 * File:   DestroyableWall.h
 * Author: thomas
 *
 * Created on 18. März 2023, 22:18
 */

#ifndef DESTROYABLEWALL_H
#define DESTROYABLEWALL_H

#include "NonDukeObject.h"

class DestroyableWall : public NonDukeObject {
public:
    DestroyableWall(int x, int y, int type);
    virtual ~DestroyableWall();

    virtual void updateSolidMap();

    virtual void draw(Canvas *canvas, DukeTextureContainer *textures);
};

#endif /* DESTROYABLEWALL_H */

