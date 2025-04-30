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
 * File:   Duke.cpp
 * Author: thomas
 * 
 * Created on 10. September 2021, 20:56
 */

#include "Duke.h"
#include "DukeDefinitions.h"

Duke::Duke(int x, int y/*, Map *map*/) /*: x(x), y(y)*//*, map(map)*/ {
    setX(x);
    setY(y);
}

Duke::Duke() {

}

void Duke::setViewDirection(int viewDirection) {
    this->viewDirection = viewDirection;
}

int Duke::getViewDirection() const {
    return viewDirection;
}

void Duke::setMove(int move) {
    this->moveDirection = move;
}

int Duke::getMove() const {
    return moveDirection;
}

Duke::Duke(const Duke& orig) {
}

Duke::~Duke() {
}

void Duke::reset() {
    viewDirection = DIRECTION_RIGHT;
    jumpState = 0;
    jumping = false;
    falling = false;
    dukeMoveAnimation = 0;
    moveDirection = 0;
    DukeProperties properties;
    justHitCounter = INVINCIBLE_AFTER_HIT; // make Duke invulnerable for the start of the new world
}

void Duke::update(UpdateContext *updateContext) {

    DukeViewPort *viewPort = updateContext->getViewPort();
    // TODO: move update actions (jumping, moving, ...) in separate methods

    //TODO: check if duke hits the ceiling

    if (isDukeJumping()) {
        int jumpDiv;
        if ((properties.getInventory() & INVENTORY_SHOE) == 0) {
            jumpDiv = JUMP_RATE[jumpState];
        } else {
            jumpDiv = LONG_JUMP_RATE[jumpState];
        }

        if (isCeilingClose(jumpDiv)) {
            jumpDiv = y % TILE_HEIGHT;
            //jumpDiv=0; // TODO: change to the value, that duke exactly hits the ceiling
            finishJumping();
        }

        y -= jumpDiv;


        jumpState++;

        if (jumpState >= MAX_JUMP_RATE) {
            finishJumping();
            setDukeFalling(true);
        }

    } else if (!isGrounded()) {

        if (!isGroundClose()) {
            y += DUKE_FALL_RATE;
            setDukeFalling(true);
            if ((y - viewPort->getShiftY()) / TILE_WIDTH >= SCREEN_MAX_SHIFT_FALL_DISTANCE_Y) {
                viewPort->addShiftY(+16);
            }
        } else {
            y = y - y % TILE_HEIGHT + TILE_HEIGHT; //(int)(y / TILE_HEIGHT) * TILE_HEIGHT + 1;
            setDukeFalling(false);
        }
    } else {
        y = y - y % TILE_HEIGHT;
        setDukeFalling(false);

        if ((y - viewPort->getShiftY()) < SCREEN_MAX_SHIFT_DISTANCE_Y * TILE_WIDTH) {
            viewPort->addShiftY(-16);
        } else if ((y - viewPort->getShiftY()) > SCREEN_MAX_SHIFT_DISTANCE_Y * TILE_WIDTH) {
            viewPort->addShiftY(+16);
        }
    }




    if (moveDirection == DIRECTION_RIGHT) {
        dukeMoveAnimation++;
        dukeMoveAnimation %= 4;
        if (!isObstacleAhead()) {
            x += TILE_WIDTH / 2;
        }

        if ((x - viewPort->getShiftX()) / TILE_WIDTH >= SCREEN_MAP_AREA_TILE_WIDTH - SCREEN_MAX_SHIFT_DISTANCE_X) {
            viewPort->addShiftX(+8);
        }
    } else if (moveDirection == DIRECTION_LEFT) {
        dukeMoveAnimation++;
        dukeMoveAnimation %= 4;
        if (!isObstacleAhead()) {
            x -= TILE_WIDTH / 2;
        }

        if ((x - viewPort->getShiftX() + TILE_WIDTH / 2) / TILE_WIDTH <= SCREEN_MAX_SHIFT_DISTANCE_X) {
            viewPort->addShiftX(-8);
        }
    } else {

        dukeMoveAnimation = 0;
    }

    if (justHitCounter > 0)
        justHitCounter--;
}

void Duke::draw(Canvas *canvas, DukeTextureContainer *textures) {

    static SDL_Rect sourceRect = {0, 0, DUKE_WIDTH, DUKE_HEIGHT};
    static SDL_Rect destRect = {0, 0, DUKE_WIDTH, DUKE_HEIGHT};



    if (viewDirection == DIRECTION_LEFT) {
        destRect.x = x - (1) * TILE_WIDTH / 2;
        destRect.y = y - (1) * TILE_HEIGHT;

        if (justHitCounter > 0 && justHitCounter / 8 % 2 == 1) {
            sourceRect.y = 8 * TILE_HEIGHT * 2;
            canvas->draw(textures->getTexture(MAN_TEXTURE + 3), &sourceRect, &destRect);
        } else if (isDukeFalling()) {
            sourceRect.y = 10 * TILE_HEIGHT * 2;
            canvas->draw(textures->getTexture(MAN_TEXTURE + 0), &sourceRect, &destRect);
        } else if (isDukeJumping() && jumpState > 0) {
            sourceRect.y = 8 * TILE_HEIGHT * 2;
            canvas->draw(textures->getTexture(MAN_TEXTURE + 0), &sourceRect, &destRect);
        } else if (moveDirection == 0) {
            sourceRect.y = 0 * TILE_HEIGHT * 2;
            canvas->draw(textures->getTexture(MAN_TEXTURE + 1), &sourceRect, &destRect);
        } else {
            sourceRect.y = dukeMoveAnimation * TILE_HEIGHT * 2;
            canvas->draw(textures->getTexture(MAN_TEXTURE + 0), &sourceRect, &destRect);
        }


    } else if (viewDirection == DIRECTION_RIGHT) {
        destRect.x = x - (1) * TILE_WIDTH / 2;
        destRect.y = y - (1) * TILE_WIDTH;

        if (justHitCounter == INVINCIBLE_AFTER_HIT) {
            sourceRect.y = 9 * TILE_HEIGHT * 2;
            canvas->draw(textures->getTexture(MAN_TEXTURE + 3), &sourceRect, &destRect);
        } else if (justHitCounter > 0 && justHitCounter % 2 == 1) {

        } else if (isDukeFalling()) {
            sourceRect.y = 11 * TILE_HEIGHT * 2;
            canvas->draw(textures->getTexture(MAN_TEXTURE + 0), &sourceRect, &destRect);
        } else if (isDukeJumping() && jumpState > 0) {
            sourceRect.y = 9 * TILE_HEIGHT * 2;
            canvas->draw(textures->getTexture(MAN_TEXTURE + 0), &sourceRect, &destRect);
        } else if (moveDirection == 0) {
            sourceRect.y = 1 * TILE_HEIGHT * 2;
            canvas->draw(textures->getTexture(MAN_TEXTURE + 1), &sourceRect, &destRect);
        } else {
            sourceRect.y = (dukeMoveAnimation + 4) * TILE_HEIGHT * 2;
            canvas->draw(textures->getTexture(MAN_TEXTURE + 0), &sourceRect, &destRect);
        }
    } else {
        // TODO: error message
    }
}

bool Duke::isGrounded() {

    //    return (getMap()->isTileSolid((getX() + TILE_WIDTH / 2) / TILE_WIDTH, getY() / TILE_HEIGHT + 1) ||
    //    getMap()->isTileSolid((getX()) / TILE_WIDTH, getY() / TILE_HEIGHT + 1));

    return (getMap()->isTileSolid(getX() / TILE_WIDTH, getY() / TILE_HEIGHT + 1) ||
            getMap()->isTileSolid((getX() + TILE_WIDTH - 1) / TILE_WIDTH, getY() / TILE_HEIGHT + 1));
}

bool Duke::isGroundClose() {

    //    return (getMap()->isTileSolid(getX() / TILE_WIDTH, (getY() + DUKE_FALL_RATE) / TILE_HEIGHT + 1) ||
    //            getMap()->isTileSolid((getX() - TILE_WIDTH / 2) / TILE_WIDTH, (getY() + DUKE_FALL_RATE) / TILE_HEIGHT + 1));

    return (getMap()->isTileSolid(getX() / TILE_WIDTH, (getY() + DUKE_FALL_RATE) / TILE_HEIGHT + 1) ||
            getMap()->isTileSolid((getX() + TILE_WIDTH - 1) / TILE_WIDTH, (getY() + DUKE_FALL_RATE) / TILE_HEIGHT + 1));

}

bool Duke::isCeilingClose(int divY) {

    return (getMap()->isTileSolid(getX() / TILE_WIDTH, (getY() - divY) / TILE_HEIGHT - 1)
            || getMap()->isTileSolid((getX() + TILE_WIDTH - 1) / TILE_WIDTH, (getY() - divY) / TILE_HEIGHT - 1));
}

bool Duke::isObstacleAhead() {
    if (viewDirection == DIRECTION_RIGHT) {
        return (getMap()->isTileSolid((getX() + TILE_WIDTH) / TILE_WIDTH, getY() / TILE_HEIGHT) ||
                getMap()->isTileSolid((getX() + TILE_WIDTH) / TILE_WIDTH, getY() / TILE_HEIGHT - 1) ||
                getMap()->isTileSolid((getX() + TILE_WIDTH) / TILE_WIDTH, (getY() + TILE_HEIGHT - 4) / TILE_HEIGHT));
    } else if (viewDirection == DIRECTION_LEFT) {

        return (getMap()->isTileSolid((getX() - 8) / TILE_WIDTH, getY() / TILE_HEIGHT) ||
                getMap()->isTileSolid((getX() - 8) / TILE_WIDTH, getY() / TILE_HEIGHT - 1) ||
                getMap()->isTileSolid((getX() - 8) / TILE_WIDTH, (getY() + TILE_HEIGHT - 4) / TILE_HEIGHT));
    }

    return (false);
}

void Duke::jump() {

    if (!isDukeFalling() && !isDukeJumping())
        setDukeJumping(true);
}

/**
 * Has to be called if Duke is hit by a bullet or touches an injuring onject
 */
void Duke::hit(int h) {
    if (h <= 0) {
        if (getProperties()->getHealth() > HEALTH_MAX) {
            getProperties()->setHealth(HEALTH_MAX);
        }

    } else if (justHitCounter == 0) {

        getProperties()->setHealth(getProperties()->getHealth() - h);
        justHitCounter = INVINCIBLE_AFTER_HIT;
    } /*else {
        justHitCounter = INVINCIBLE_AFTER_HIT;
    }*/
}

/**
 * Get duke properties: health, firepower, ...
 * @return 
 */
DukeProperties * Duke::getProperties() {
    return &properties;
}

