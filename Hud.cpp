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
 * File:   Hud.cpp
 * Author: thomas
 * 
 * Created on 7. November 2021, 23:06
 */

#include <cstdlib>
#include <iomanip>

#include "Hud.h"
#include "TextWriter.h"
#include "DukeDrawSupport.h"

Hud::Hud() {
}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}

void Hud::draw(Canvas *renderer, DukeProperties *properties, DukeTextureContainer *textureContainer) {


    // score
    std::stringstream scoreStringFormat;
    scoreStringFormat << std::setw(8) << std::setfill('0') << properties->getScore();

    TextWriter::print(renderer, scoreStringFormat.str(), 15 * TILE_WIDTH, 1.5 * TILE_HEIGHT);
    //Dux::drawText(renderer, tileString, 15 * TILE_WIDTH, 1.5 * TILE_HEIGHT);

    // health
    drawBorder(renderer, textureContainer);
    for (int i = 0; i < properties->getHealth(); i++) {
        DukeDrawSupport::drawHalfTile(renderer,textureContainer->getTexture(25+1), HEALTH_TEXTURE_POSITION, (15 + i * .5) * TILE_WIDTH, 3.75 * TILE_HEIGHT);
    }

    // firepower
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(25), GUN_TEXTURE_POSITION, 16.5 * TILE_WIDTH, 6 * TILE_HEIGHT);
    for (unsigned int i = 0; i < properties->getFirepower(); i++) {
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(25), BULLET_TEXTURE_POSITION, (15 + i * 1) * TILE_WIDTH, 6.75 * TILE_HEIGHT);
    }


    // inventory
    if (properties->getInventory() & INVENTORY_RED_KEY)
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(25+2), RED_KEY_TEXTURE_POSITION, 15 * TILE_WIDTH, 9 * TILE_HEIGHT);

    if (properties->getInventory() & INVENTORY_GREEN_KEY)
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(25+2), GREEN_KEY_TEXTURE_POSITION, 16 * TILE_WIDTH, 9 * TILE_HEIGHT);

    if (properties->getInventory() & INVENTORY_BLUE_KEY)
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(25+2), BLUE_KEY_TEXTURE_POSITION, 17 * TILE_WIDTH, 9 * TILE_HEIGHT);

    if (properties->getInventory() & INVENTORY_PURPLE_KEY)
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(25+2), PURPLE_KEY_TEXTURE_POSITION, 18 * TILE_WIDTH, 9 * TILE_HEIGHT);



    if (properties->getInventory() & INVENTORY_SHOE)
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(25), SHOE_TEXTURE_POSITION, 15 * TILE_WIDTH, 10 * TILE_HEIGHT);

    if (properties->getInventory() & INVENTORY_CLAW)
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(25), CLAW_TEXTURE_POSITION, 16 * TILE_WIDTH, 10 * TILE_HEIGHT);

    if (properties->getInventory() & INVENTORY_GLOVE)
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(25+1), GLOVE_TEXTURE_POSITION, 17 * TILE_WIDTH, 10 * TILE_HEIGHT);

    if (properties->getInventory() & INVENTORY_BOARD)
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(25+1), BOARD_TEXTURE_POSITION, 18 * TILE_WIDTH, 10 * TILE_HEIGHT);


}

void Hud::drawBorder(Canvas *renderer, DukeTextureContainer *textureContainer) {

    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 4 * TILE_HEIGHT, 0, 0);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 7 * TILE_HEIGHT, 0, 11 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 9 * TILE_HEIGHT, 19 * TILE_WIDTH, 0);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 11 * TILE_HEIGHT, 19 * TILE_WIDTH, 11 * TILE_HEIGHT);

    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 5 * TILE_HEIGHT, 14 * TILE_WIDTH, 0);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 6 * TILE_HEIGHT, 14 * TILE_WIDTH, 11 * TILE_HEIGHT);


    for (int i = 1; i < 11; i++) {
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 0 * TILE_HEIGHT, 0, i * TILE_HEIGHT);
    }

    for (int i = 1; i < 11; i++) {
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 1 * TILE_HEIGHT, 14 * TILE_WIDTH, i * TILE_HEIGHT);
    }

    for (int i = 1; i < 14; i++) {
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 2 * TILE_HEIGHT, i*TILE_WIDTH, 0);
    }

    for (int i = 1; i < 14; i++) {
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 3 * TILE_HEIGHT, i*TILE_WIDTH, 11 * TILE_HEIGHT);
    }

    for (int i = 1; i < 11; i++) {
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 10 * TILE_HEIGHT, 19 * TILE_WIDTH, i * TILE_HEIGHT);
    }

    // Box: PRESS F1 FOR HELP
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 26 * TILE_HEIGHT, 5.5 * TILE_WIDTH, 11 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 27 * TILE_HEIGHT, 6.5 * TILE_WIDTH, 11 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 28 * TILE_HEIGHT, 7.5 * TILE_WIDTH, 11 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 29 * TILE_HEIGHT, 8.5 * TILE_WIDTH, 11 * TILE_HEIGHT);

    // Box: SCORE
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 8 * TILE_HEIGHT, 15 * TILE_WIDTH, 0);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 38 * TILE_HEIGHT, 16 * TILE_WIDTH, 0);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 39 * TILE_HEIGHT, 17 * TILE_WIDTH, 0);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 8 * TILE_HEIGHT, 18 * TILE_WIDTH, 0);

    // BOX: HEALTH
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 14 * TILE_HEIGHT, 14 * TILE_WIDTH, 2.5 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 8 * TILE_HEIGHT, 15 * TILE_WIDTH, 2.5 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 36 * TILE_HEIGHT, 16 * TILE_WIDTH, 2.5 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 37 * TILE_HEIGHT, 17 * TILE_WIDTH, 2.5 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 8 * TILE_HEIGHT, 18 * TILE_WIDTH, 2.5 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 15 * TILE_HEIGHT, 19 * TILE_WIDTH, 2.5 * TILE_HEIGHT);

    // BOX: FIREPOWER
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 14 * TILE_HEIGHT, 14 * TILE_WIDTH, 5 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 8 * TILE_HEIGHT, 15 * TILE_WIDTH, 5 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 8 * TILE_HEIGHT, 18 * TILE_WIDTH, 5 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 33 * TILE_HEIGHT, 15.5 * TILE_WIDTH, 5 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 34 * TILE_HEIGHT, 16.5 * TILE_WIDTH, 5 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 35 * TILE_HEIGHT, 17.5 * TILE_WIDTH, 5 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 15 * TILE_HEIGHT, 19 * TILE_WIDTH, 5 * TILE_HEIGHT);

    // BOX: INVENTORY
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 14 * TILE_HEIGHT, 14 * TILE_WIDTH, 8 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 8 * TILE_HEIGHT, 15 * TILE_WIDTH, 8 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 8 * TILE_HEIGHT, 18 * TILE_WIDTH, 8 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 30 * TILE_HEIGHT, 15.5 * TILE_WIDTH, 8 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 31 * TILE_HEIGHT, 16.5 * TILE_WIDTH, 8 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 32 * TILE_HEIGHT, 17.5 * TILE_WIDTH, 8 * TILE_HEIGHT);
    DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 15 * TILE_HEIGHT, 19 * TILE_WIDTH, 8 * TILE_HEIGHT);

    for (int i = 15; i < 19; i++) {
        DukeDrawSupport::drawTile(renderer, textureContainer->getTexture(BORDER_TEXTURE), 8 * TILE_HEIGHT, i* TILE_WIDTH, 11 * TILE_HEIGHT);
    }

}