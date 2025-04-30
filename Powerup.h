/*
 * Copyright (C) 2021 thomas
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
 * File:   Can.h
 * Author: thomas
 *
 * Created on 20. Februar 2021, 23:07
 */

#ifndef CAN_H
#define CAN_H

#include "NonDukeObject.h"

#include "GameCanvas.h"

class Powerup : public NonDukeObject {
private:

public:
    Powerup(int x, int y, int w, int h, int type);
    virtual ~Powerup();

//    virtual void draw(GameCanvas *canvas, TextureContainer *textures);
    virtual void collect(Duke *duke) override;

};

#endif /* CAN_H */

