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
 * File:   DrawInterface.h
 * Author: thomas
 *
 * Created on 9. Februar 2022, 09:38
 */

#ifndef DRAWINTERFACE_H
#define DRAWINTERFACE_H

#include "Canvas.h"

class DrawInterface {
public:
    virtual void draw(Canvas *canvas)=0;
};

#endif /* DRAWINTERFACE_H */

