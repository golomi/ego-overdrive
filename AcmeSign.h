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
 * File:   AcmeSign.h
 * Author: thomas
 *
 * Created on 8. September 2024, 02:23
 */

#ifndef ACMESIGN_H
#define ACMESIGN_H

#include "NonDukeObject.h"
#include "DukeUpdateContext.h"

const int AcmeShift[] = {-1, 1, -1, 1, -1, 1};
const int WOBBLECOUNTER_MAX = 50;
const int ACME_FALL_RATE = 12;

enum AcmeState {
    FIXED, WOBBLING_UP, WOBBLING_DOWN, FALLING, EXPLODING
};

class AcmeSign : public NonDukeObject {
private:
    AcmeState acmeState = FIXED;
    int wobbleCounter = 5;
public:
    AcmeSign(int x, int y, int w, int h, int type);
    virtual ~AcmeSign();
    virtual void update(UpdateContext *updateContext) override;
    //    virtual void draw(Canvas *canvas, DukeTextureContainer *textures) override;
};

#endif /* ACMESIGN_H */

