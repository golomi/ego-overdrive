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
 * File:   GreenAlien.cpp
 * Author: thomas
 * 
 * Created on 30. April 2022, 23:26
 */

#include "GreenAlien.h"

#include "DukeDrawSupport.h"

//GreenAlien::GreenAlien(int x, int y) : NonDukeObject(x, y) {
//}

GreenAlien::GreenAlien(int x, int y, int type) : NonDukeObject(x, y, 1, 1, type) {
    // TODO: check if wall mounted
}

GreenAlien::~GreenAlien() {
}

const int GREEN_ALIEN_MOVE_SPEED = 1;

void GreenAlien::update(UpdateContext *updateContext) {

    if (isObstacleAhead() || isEdgeAhead()) {
        turnViewDirection();
    } //else {

        setY(getY() + GREEN_ALIEN_MOVE_SPEED * getViewDirection());
   // }
}


//bool GreenAlien::isWallMounted() {
//
//    return (getMap()->isTileSolid(getTileX() /*/ TILE_WIDTH*/, getTileY() /*/ TILE_HEIGHT*/ + 1) //||
//            //   getMap()->isSolid((getTileX() /*- TILE_WIDTH / 2*/) /*/ TILE_WIDTH*/, getTileY() /*/ TILE_HEIGHT*/ + 1)
//            );
//}

bool GreenAlien::isObstacleAhead() {
    //    if (getViewDirection() == DIRECTION_DOWN) {
    //        return (getMap()->isTileSolid(x / TILE_WIDTH, (y + 8) / TILE_HEIGHT) ||
    //                getMap()->isTileSolid((x + TILE_WIDTH - 4) / TILE_WIDTH, (y + 8) / TILE_HEIGHT));
    //    } else if (getViewDirection() == DIRECTION_UP) {
    //        return (getMap()->isTileSolid(x / TILE_WIDTH, (y - 8 - 8) / TILE_HEIGHT) ||
    //                getMap()->isTileSolid((x + TILE_WIDTH - 4) / TILE_WIDTH, (y - 8 - 8) / TILE_HEIGHT));
    //    }

    if (getViewDirection() == DIRECTION_DOWN) {
        return (getMap()->isTileSolid(getTileX(), getTileY() + 1));
    } else if (getViewDirection() == DIRECTION_UP) {
        return (getMap()->isTileSolid(getTileX(), getTileY() ));
    }
    return (false);

}

bool GreenAlien::isEdgeAhead() {
    if (getType() == 0x16) {
        return (isEdgeLeftAhead());
    } else if (getType() == 0x17) {
        return (isEdgeRightAhead());
    }

    return (false);
}

bool GreenAlien::isEdgeLeftAhead() {
    if (getViewDirection() == DIRECTION_DOWN) {
        return (!getMap()->isTileSolid(getTileX() - 1, getTileY() + 1));
    } else if (getViewDirection() == DIRECTION_UP) {
        return (!getMap()->isTileSolid(getTileX() - 1, getTileY()));
    }
    return (false);
}

bool GreenAlien::isEdgeRightAhead() {
    if (getViewDirection() == DIRECTION_DOWN) {
        return (!getMap()->isTileSolid(getTileX() + 1, getTileY() + 1));
    } else if (getViewDirection() == DIRECTION_UP) {
        return (!getMap()->isTileSolid(getTileX() + 1, getTileY()));
    }
    return (false);
}

void GreenAlien::draw(Canvas *canvas, DukeTextureContainer *textures) {
    static SDL_Rect sourceRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    static SDL_Rect destRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};



    destRect.x = getX(); //getTileX() * 16;
    destRect.y = getY(); //getTileY() * 16;

    SDL_Texture *texture = NULL;

    if (isSimpleObject() == true) {
        int speed = 1;

        texture = textureContainer.getTexture(3 + getObjectTextureFileIndex());

        int anim;

        if (getViewDirection() == DIRECTION_UP) {
            anim = getIndex() + ((getTick() / speed) % getAnimCount());
        } else {
            anim = getIndex() + (getAnimCount()-((getTick() / speed) % getAnimCount()) - 1);
        }


        DukeDrawSupport::drawMultiTile(canvas, texture, 16 * anim * getTileWidth() * getTileHeight(),
                getTileHeight(), getTileHeight(), getX(), getY());


    } else {
        texture = textureContainer.getTexture(3 + 1);
        sourceRect = {0, 16 * (43 + getTick() % 3), 16, 16};

        if (texture != NULL) {
            canvas->draw(texture, &sourceRect, &destRect);
        }
    }
}