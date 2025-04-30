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
 * File:   Bullet.cpp
 * Author: thomas
 * 
 * Created on 2. Mai 2022, 21:09
 */

#include "Bullet.h"

int Bullet::bulletCounter = 0;

Bullet::Bullet(int x, int y) : MapObject(x, y, 1, 1, 0) {

}

Bullet::~Bullet() {
}

void Bullet::update(UpdateContext *updateContext) {


    // TODO: isMaxFlyDistance()


    if (flyCounter < MAX_BULLET_FLY_DISTANCE) {
        flyCounter++;
        // TODO: isObstacleAhead()
        // TODO: moveBullet();
        // TODO: checkBounds
        if (flyCounter % 4 == 1)
            setX(getX() + BULLET_MOVE_SPEED * getViewDirection());
    } else {

    }

}

void Bullet::draw(Canvas *canvas, DukeTextureContainer *textures) {
    static SDL_Rect sourceRect = {0, TILE_HEIGHT * 40, TILE_WIDTH, TILE_HEIGHT};
    static SDL_Rect destRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};


    destRect.x = getX();
    destRect.y = getY();

    if (flyCounter < 4) {
        if (getViewDirection() == DIRECTION_LEFT) {
            sourceRect.y = 46 * TILE_HEIGHT;
        } else {
            sourceRect.y = 47 * TILE_HEIGHT;
        }

        //canvas->draw(textures->objectTexture[0], &sourceRect, &destRect);
        canvas->draw(textures->getTexture(25), &sourceRect, &destRect);
    } else if (flyCounter < MAX_BULLET_FLY_DISTANCE) {
        sourceRect.y = (6 + flyCounter / 4 % 4) * TILE_HEIGHT;
        canvas->draw(textures->getTexture(25), &sourceRect, &destRect);
        //        canvas->draw(textures->objectTexture[0], &sourceRect, &destRect);
    } else {
        // do nothing
    }

}

void Bullet::fire(int x, int y, int viewDirection) {
    if (flyCounter >= MAX_BULLET_FLY_DISTANCE) {
        setX(x + TILE_WIDTH / 4 * viewDirection);
        setY(y + 4 - 16 - 1);
        setViewDirection(viewDirection);
        flyCounter = 0;
    }
}

int Bullet::getBulletCounter() {

    return bulletCounter;
}

void Bullet::incBulletCounter() {
    if (bulletCounter < MAX_BULLET_COUNT) {

        bulletCounter++;
    }
}

void Bullet::decBulletCounter() {
    if (bulletCounter > 0) {
        bulletCounter--;
    } else {
    }
}

void Bullet::hit(int i) {
    flyCounter = MAX_BULLET_FLY_DISTANCE;
    setX(0);
    setY(0);
}
