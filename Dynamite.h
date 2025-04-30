/*
 * Copyright (C) 2025 thomas
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
 * File:   Dynamite.h
 * Author: thomas
 *
 * Created on 8. März 2025, 09:47
 */

#ifndef DYNAMITE_H
#define DYNAMITE_H

#include "NonDukeObject.h"

enum DynamiteState {hold, explode};

class Dynamite : public NonDukeObject {
private:
    DynamiteState state = hold;
    int counter = 0;
    int counterMax=18;
public:
    Dynamite(int x, int y, int w, int h, int type);
    virtual ~Dynamite();
    virtual void hit(int h) override;
    virtual void update(UpdateContext *updateContext) override;
    virtual void draw(Canvas *canvas, DukeTextureContainer *textures) override;


};

#endif /* DYNAMITE_H */

