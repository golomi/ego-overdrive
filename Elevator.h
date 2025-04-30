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
 * File:   Elevator.h
 * Author: thomas
 *
 * Created on 22. November 2022, 21:14
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "NonDukeObject.h"

enum ElevatorState {
    standing, rising, falling
};

class Elevator : public NonDukeObject {
private:
    int extended = 0;
    ElevatorState state = standing;
    Duke *duke;
public:
    Elevator(int x, int y, int w, int h, int type);
    virtual ~Elevator();

    virtual void draw(Canvas *canvas, DukeTextureContainer *textures) override;

    virtual void updateSolidMap() override;
    virtual void action(Duke *duke, int type, std::list<MapObject*> &objectVector, MapObjectNotifier *listener) override;
    virtual void standon(Duke *duke) override;
    virtual void clearStandon() override;
    virtual void update(UpdateContext *updateContext) override;

    virtual int getTileHeight() override;
    
    bool isCeilingClose();
};

#endif /* ELEVATOR_H */

