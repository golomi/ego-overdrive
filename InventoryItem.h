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
 * File:   Key.h
 * Author: thomas
 *
 * Created on 1. Februar 2022, 23:14
 */

#ifndef KEY_H
#define KEY_H

#include "NonDukeObject.h"

class InventoryItem : public NonDukeObject {
private:

public:
    InventoryItem(int x, int y, int type);
    virtual ~InventoryItem();
    void touch(Duke *duke, std::list<MapObject*> &objectVector) override;
};

#endif /* KEY_H */

