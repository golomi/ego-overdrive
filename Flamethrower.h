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
 * File:   Flamethrower.h
 * Author: thomas
 *
 * Created on 20. März 2024, 01:21
 */

#ifndef FLAMETHROWER_H
#define FLAMETHROWER_H

#include "NonDukeObject.h"

class Flamethrower : public NonDukeObject {
private:
    const int STATE_SMALL_FLAME = 16;
    const int STATE_FULL_FLAME = STATE_SMALL_FLAME + 8;
    const int STATE_FINAL = STATE_FULL_FLAME + 20;
    int state = 0;
public:
    Flamethrower(int x, int y, int type);
    virtual ~Flamethrower();
    virtual void draw(Canvas *canvas, DukeTextureContainer *textures) override;
};

#endif /* FLAMETHROWER_H */

