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
 * File:   Can.cpp
 * Author: thomas
 * 
 * Created on 20. Februar 2021, 23:07
 */

#include "Powerup.h"

#include "DebugOutput.h"

Powerup::Powerup(int x, int y, int w, int h, int type) : NonDukeObject(x, y, 1, 1, type) {
    DebugOutput::addLine("init Powerup\n");
}

Powerup::~Powerup() {
}

void Powerup::collect(Duke *duke) {
    switch (getType()) {
        case 0x51:
        case 0x52:
            duke->getProperties()->addHealth(1);
            break;
        case 0x67:
            duke->getProperties()->addHealth(2);
            break;
        case 0x62:
            duke->getProperties()->setHealth(HEALTH_MAX);
            break;
        default:
            DebugOutput::addLine("How is this possible?\n");
            break;
    }
}