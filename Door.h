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
 * File:   Door.h
 * Author: thomas
 *
 * Created on 3. Februar 2022, 23:58
 */

#ifndef DOOR_H
#define DOOR_H

#include "NonDukeObject.h"

enum DoorState {
    CLOSED, OPENED
};

class Door : public NonDukeObject {
private:
    DoorState doorState = CLOSED;
    int openState = 0;
public:
    Door(int x, int y, int type);
    virtual void open() override;
    virtual void updateSolidMap() override;
    virtual void update(UpdateContext *updateContext) override;
};

#endif /* DOOR_H */

