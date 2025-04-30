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
 * File:   DissolvingGround.h
 * Author: thomas
 *
 * Created on 12. März 2023, 13:15
 */

#ifndef DISSOLVINGGROUND_H
#define DISSOLVINGGROUND_H

#include "NonDukeObject.h"

enum DissolvingGroundState {
    initial, firstTouch, firstUntouch, secondTouch
};

class DissolvingGround : public NonDukeObject {
private:
    DissolvingGroundState state = initial;
    bool dukeStandon = false;
public:
    DissolvingGround(int x, int y, int type);
    virtual ~DissolvingGround();

    virtual void updateSolidMap() override;
    virtual void standon(Duke *duke) override;
    virtual void clearStandon() override;

    virtual void update(UpdateContext * updateContext) override;

    virtual void draw(Canvas *canvas, DukeTextureContainer *textures) override;
};

#endif /* DISSOLVINGGROUND_H */

