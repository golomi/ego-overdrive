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
 * File:   TextWriter.cpp
 * Author: thomas
 * 
 * Created on 5. August 2022, 15:24
 */

#include "TextWriter.h"

#include "DukeDefinitions.h"

DukeTextureContainer *TextWriter::textureContainer = nullptr;

TextWriter::TextWriter() {
}

TextWriter::TextWriter(const TextWriter& orig) {
}

TextWriter::~TextWriter() {
}

void TextWriter::print(Canvas* renderer, std::string text, int x, int y) {

    int charTile = 0;
    int charTexture = 0;

    static SDL_Rect sourceRect = {0, 0, FONT_WIDTH, FONT_HEIGHT};
    static SDL_Rect destRect = {0, 0, FONT_WIDTH, FONT_HEIGHT};

    int col = 0;
    int row = 0;

    for (unsigned int i = 0; i < text.length(); i++) {
        char c = text[i];

        if (c == '\n') {
            col = 0;
            row++;
        } else if (c <= 'Z') {
            charTile = (c - 22) % 50;
            charTexture = (c - 22) / 50;

            sourceRect.y = charTile*FONT_HEIGHT;
            destRect.x = x + col * 8;
            destRect.y = y + row * 8;

            renderer->draw(textureContainer->getTexture(FONT_TEXTURE + charTexture), &sourceRect, &destRect);

            col++;
        } else if (c <= 'z') {
            charTile = c - 'a' + 19;
            charTexture = 1;

            sourceRect.y = charTile*FONT_HEIGHT;
            destRect.x = x + col * 8;
            destRect.y = y + row * 8;

            renderer->draw(textureContainer->getTexture(FONT_TEXTURE + charTexture), &sourceRect, &destRect);

            col++;
        } else {

        }



    }
}

void TextWriter::setTextureContainer(DukeTextureContainer* intTextureContainer) {
    textureContainer = intTextureContainer;
}