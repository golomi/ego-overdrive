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
 * File:   Bullet.h
 * Author: thomas
 *
 * Created on 2. Mai 2022, 21:09
 */

#ifndef BULLET_H
#define BULLET_H

#include "MapObject.h"

class Bullet : public MapObject {
private:
    int flyCounter = 0;
    static int bulletCounter;
public:
    Bullet(int x, int y);
    virtual ~Bullet() override;


    void update(UpdateContext *updateContext) override;
    virtual void draw(Canvas *canvas, DukeTextureContainer *textures) override;
    void fire(int x, int y, int viewDirection);

    virtual void hit(int i) override;

    static int getBulletCounter();
    static void incBulletCounter();
    static void decBulletCounter();

};

#endif /* BULLET_H */

