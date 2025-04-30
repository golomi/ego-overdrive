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
 * File:   Duke.h
 * Author: thomas
 *
 * Created on 10. September 2021, 20:56
 */

#ifndef DUKE_H
#define DUKE_H

#include <list>

#include "MapObject.h"
#include "Map.h"
#include "DukeTextureContainer.h"
#include "DukeProperties.h"
#include "UpdateContext.h"
//#include "DefaultMapObject.h"


class Duke : public MapObject {
private:
    int viewDirection = DIRECTION_RIGHT;
    int jumpState = 0;
    bool jumping = false;
    bool falling = false;
    int dukeMoveAnimation = 0;
    int moveDirection = 0;
    DukeProperties properties;
    int justHitCounter = 0;

public:
    Duke(int x, int y/*, Map *map*/);
    Duke();
    Duke(const Duke& orig);
    virtual ~Duke();


//    void update(ViewPort *viewPort);
    void update(UpdateContext *updateContext) override;

    void reset();

    virtual void draw(Canvas *canvas, DukeTextureContainer *textures) override;

    void jump();

    bool isGrounded() override;
    bool isGroundClose() override;
    bool isCeilingClose(int divY);
    bool isObstacleAhead() override;

    void setDukeJumping(bool jumping) {
        this->jumping = jumping;
    }

    bool isDukeJumping() const {
        return jumping;
    }

    void setDukeFalling(bool falling) {
        this->falling = falling;
    }

    bool isDukeFalling() const {
        return falling;
    }
    
    void finishJumping() {
        setDukeJumping(false);
        jumpState=0;
    }

    void setViewDirection(int viewDirection);
    int getViewDirection() const;
    void setMove(int move);
    int getMove() const;

    void hit(int h) override;

    DukeProperties *getProperties();
};

#endif /* DUKE_H */

