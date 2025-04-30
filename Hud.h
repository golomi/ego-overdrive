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
 * File:   Hud.h
 * Author: thomas
 *
 * Created on 7. November 2021, 23:06
 */

#ifndef HUD_H
#define HUD_H

#include "DukeProperties.h"
#include "DukeTextureContainer.h"
#include "GameCanvas.h"

// TODO: inherit from DrawInterface
class Hud {
private:
public:
    Hud();
    Hud(const Hud& orig);
    virtual ~Hud();

    void draw(Canvas *canvas, DukeProperties *properties, DukeTextureContainer *textureContainer);
    void drawBorder(Canvas *canvas, DukeTextureContainer *textureContainer);
};

#endif /* HUD_H */

