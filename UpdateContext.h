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
 * File:   UpdateContext.h
 * Author: thomas
 *
 * Created on 12. Januar 2024, 00:31
 */

#ifndef UPDATECONTEXT_H
#define UPDATECONTEXT_H

#include "DukeViewPort.h"
#include "Map.h"

class UpdateContext {
private:
    DukeViewPort *viewPort;
public:
    UpdateContext(DukeViewPort *viewPort);
    virtual ~UpdateContext();
//    void setViewPort(ViewPort *viewPort);
    DukeViewPort *getViewPort();
};

#endif /* UPDATECONTEXT_H */

