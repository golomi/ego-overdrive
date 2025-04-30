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
 * File:   ExitDoor.h
 * Author: thomas
 *
 * Created on 25. April 2022, 23:13
 */

#ifndef EXITDOOR_H
#define EXITDOOR_H

#include "NonDukeObject.h"

class ExitDoor : public NonDukeObject {
private:
    bool doorOpened = false;
    int doorOpenCounter = 0;

public:
    ExitDoor(int x, int y, int type);
    virtual void action(Duke *duke, std::list<MapObject*> &objectVector, MapObjectNotifier *listener) override;
    virtual void draw(Canvas *canvas, DukeTextureContainer *textures) override;
    virtual void update(UpdateContext *updateContext) override;
};


#endif /* EXITDOOR_H */

