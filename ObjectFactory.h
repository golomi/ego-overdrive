/*
 * Copyright (C) 2024 thomas
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
 * File:   ObjectFactory.h
 * Author: thomas
 *
 * Created on 17. Februar 2024, 00:59
 */

#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "NonDukeObject.h"


/* TODO: Object Factory is currently static and directly used by MapLoader. In 
 * the future it should be a pure virtual class within a Duke File Tools package
 * and is implemented in the actual game
 */
class ObjectFactory {
public:
    static NonDukeObject* createObject(int x, int y, int tile);
};

#endif /* OBJECTFACTORY_H */

