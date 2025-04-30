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
 * File:   ViewPort.h
 * Author: thomas
 *
 * Created on 23. Januar 2022, 10:57
 */

#include "DukeDefinitions.h"

#include "ViewPort.h"

#ifndef DUKEVIEWPORT_H
#define DUKEVIEWPORT_H

class DukeViewPort : public ViewPort {
private:
    const int MAX_SHIFT_X = (MAP_WIDTH - SCREEN_MAP_AREA_TILE_WIDTH) * TILE_WIDTH;
    const int MAX_SHIFT_Y = (MAP_HEIGHT - SCREEN_MAP_AREA_TILE_HEIGHT) * TILE_HEIGHT;

    int shiftX, shiftY;
public:
    DukeViewPort();
    void setShiftX(int shiftX) override;
    int getShiftX() override;
    void addShiftX(int deltaX);
    void setShiftY(int shiftY) override;
    int getShiftY() override;
    void addShiftY(int deltaY);

};

#endif /* DUKEVIEWPORT_H */

