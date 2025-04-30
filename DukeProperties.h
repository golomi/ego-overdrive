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
 * File:   DukeProperties.h
 * Author: thomas
 *
 * Created on 7. November 2021, 23:09
 */

#ifndef DUKEPROPERTIES_H
#define DUKEPROPERTIES_H

#include "DukeDefinitions.h"

static const unsigned int INVENTORY_EMPTY = 0x00;
static const unsigned int INVENTORY_RED_KEY = 0x01;
static const unsigned int INVENTORY_GREEN_KEY = 0x02;
static const unsigned int INVENTORY_BLUE_KEY = 0x04;
static const unsigned int INVENTORY_PURPLE_KEY = 0x08;
static const unsigned int INVENTORY_SHOE = 0x10;
static const unsigned int INVENTORY_CLAW = 0x20;
static const unsigned int INVENTORY_GLOVE = 0x40;
static const unsigned int INVENTORY_BOARD = 0x80;
static const unsigned int INVENTORY_ALL = INVENTORY_RED_KEY | INVENTORY_GREEN_KEY | INVENTORY_GREEN_KEY | INVENTORY_BLUE_KEY | INVENTORY_PURPLE_KEY |
        INVENTORY_SHOE | INVENTORY_CLAW | INVENTORY_GLOVE | INVENTORY_BOARD;
static const unsigned int INVENTORY_NONKEYS = INVENTORY_SHOE | INVENTORY_CLAW;

class DukeProperties {
private:
    int health = HEALTH_MAX;
    unsigned int inventory = INVENTORY_EMPTY;
    unsigned int firepower = 2;
    int score = 1234;
public:
    DukeProperties();
    DukeProperties(const DukeProperties& orig);
    virtual ~DukeProperties();
    void setScore(int score);
    int getScore() const;
    void addScore(int score);
    void setFirepower(unsigned int firepower);
    unsigned int getFirepower() const;
    void setInventory(unsigned int inventory);
    void addInventory(unsigned int inventory);
    void clearKeys();
    unsigned int getInventory() const;
    void setHealth(int health);
    void addHealth(int health);
    int getHealth() const;

};

#endif /* DUKEPROPERTIES_H */

