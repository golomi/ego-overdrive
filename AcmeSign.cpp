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
 * File:   AcmeSign.cpp
 * Author: thomas
 * 
 * Created on 8. September 2024, 02:23
 */

#include "AcmeSign.h"

AcmeSign::AcmeSign(int x, int y, int w, int h, int type) : NonDukeObject(x, y, w, h, type) {
    setY(getY() + 1); // the ACME sign is shifted one pixel by default
}

AcmeSign::~AcmeSign() {
}

void AcmeSign::update(UpdateContext *updateContext) {
    switch (acmeState) {
        case FIXED:
            if (((DukeUpdateContext*) updateContext)->getDuke(0)->getX() >= getX() &&
                    ((DukeUpdateContext*) updateContext)->getDuke(0)->getX() <= getX() + getWidth() &&
                    ((DukeUpdateContext*) updateContext)->getDuke(0)->getY() > getY()) {
                acmeState = WOBBLING_UP;
            }
            break;
        case WOBBLING_UP:
            wobbleCounter--;


            if (wobbleCounter <= 0) {
                setY(getY() + ACME_FALL_RATE);  
                acmeState = FALLING;
            } else {
                setY(getY() - 1);
                acmeState = WOBBLING_DOWN;
            }
            break;
        case WOBBLING_DOWN:
            setY(getY() + 1);
            acmeState = WOBBLING_UP;
            break;
        case FALLING:
            setY(getY() + ACME_FALL_RATE);

            if (isGrounded()) {
                acmeState = EXPLODING;
            }
            break;
        case EXPLODING:
            remove();
        default:
            // Something stragnge happened
            break;
    }
}
//
//void AcmeSign::draw(Canvas *canvas, DukeTextureContainer *textures) {
//
//
////    SDL_Texture *texture = NULL;
////
////    int flameTick = (getTick()) % STATE_FINAL;
////
////    if (getType() == 0x3009 || getType() == 0x09) {
////        texture = textureContainer.getTexture(25 + getObjectTextureFileIndex());
////    } else if (getType() == 0x300A || getType() == 0x0A) {
////        texture = textureContainer.getTexture(25 + getObjectTextureFileIndex());
////    }
////
////    if (flameTick < STATE_SMALL_FLAME) {
////        // nothing to draw
////    } else if (flameTick < STATE_FULL_FLAME) {
////
////        if ((getTick()) % 2 == 0) {
////
////            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * getIndex(), 1, 1, getX(), getY());
////
////
////        }
////    } else if (flameTick < STATE_FINAL) {
////        int flameIndex = getTick() % 2;
////        if (getType() == 0x3009 || getType() == 0x09) {
////            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 1 + flameIndex),
////                    1, 1, getX(), getY());
////            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 1 + flameIndex),
////                    1, 1, getX() + 1 * TILE_WIDTH, getY());
////            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 3 + flameIndex),
////                    1, 1, getX() + 2 * TILE_WIDTH, getY());
////        } else if (getType() == 0x300A || getType() == 0x0A) {
////            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 1 + flameIndex),
////                    1, 1, getX(), getY());
////            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 1 + flameIndex),
////                    1, 1, getX() - 1 * TILE_WIDTH, getY());
////            DukeDrawSupport::drawMultiTile(canvas, texture, 16 * (getIndex() + 3 + flameIndex),
////                    1, 1, getX() - 2 * TILE_WIDTH, getY());
////        }
////
////    }
//
//}

