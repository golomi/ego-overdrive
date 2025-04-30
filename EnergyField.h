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
 * File:   EnergieField.h
 * Author: thomas
 *
 * Created on 1. Mai 2022, 00:27
 */

#ifndef ENERGYFIELD_H
#define ENERGYFIELD_H

#include "NonDukeObject.h"

class EnergyField : public NonDukeObject {
private:
public:
    EnergyField(int x, int y, int type);
    virtual ~EnergyField();
    
     virtual void draw(Canvas *canvas, DukeTextureContainer *textures)  override;
};

#endif /* ENERGYFIELD_H */

