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
 * File:   DukeProperties.cpp
 * Author: thomas
 * 
 * Created on 7. November 2021, 23:09
 */

#include "DukeProperties.h"

DukeProperties::DukeProperties() {
}

DukeProperties::DukeProperties(const DukeProperties& orig) {
}

DukeProperties::~DukeProperties() {
}

void DukeProperties::setScore(int score) {
    this->score = score;
}

int DukeProperties::getScore() const {
    return score;
}

void DukeProperties::addScore(int score) {
    this->score += score;
}

void DukeProperties::setFirepower(unsigned int firepower) {
    this->firepower = firepower;
}

unsigned int DukeProperties::getFirepower() const {
    return firepower;
}

void DukeProperties::setInventory(unsigned int inventory) {
    this->inventory = inventory;
}

void DukeProperties::addInventory(unsigned int inventory) {
    this->inventory |= inventory;
}

/**
 * Remove Keys, incl. PCB and Glove from inventory
 */
void DukeProperties::clearKeys() {
    setInventory(getInventory()&INVENTORY_NONKEYS);
}

unsigned int DukeProperties::getInventory() const {
    return inventory;
}

void DukeProperties::setHealth(int health) {
    this->health = health;
}

void DukeProperties::addHealth(int health) {
    this->health += health;
    if (this->health < 0)
        this->health = 0;

    if (this->health > HEALTH_MAX)
        this->health = HEALTH_MAX;
}

int DukeProperties::getHealth() const {
    return health;
}

