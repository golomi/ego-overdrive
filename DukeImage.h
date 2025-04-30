/*
 * Copyright (C) 2021 Thomas Lenck
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

/*! 
 * File:   DukeImage.h
 * Author: Thomas Lenck
 *
 * Created on 26. Januar 2021, 15:42
 */

#ifndef DNIMAGE_H
#define DNIMAGE_H

#include <iostream>

/*!
 * DukeImage loads the various file formats of Duke and converts it to a 24 or 32 bit RGB(A) image
 */
class DukeImage {
private:
    /*!
     * The palatte for converting EGA to 24bit color
     */
    const unsigned char PALETTE[16][3] = {
        {0, 0, 0}, // 0
        {0, 0, 170}, // 1
        {0, 170, 0}, // 2
        {0, 170, 170}, // 3
        {170, 0, 0}, // 4
        {170, 0, 170}, // 5
        {170, 85, 0}, // 6
        {170, 170, 170}, // 7
        {85, 85, 85}, // 8
        {85, 85, 255}, // 9
        {85, 255, 85}, // 10    
        {85, 255, 255}, // 11
        {255, 85, 85}, // 12
        {255, 85, 255}, // 13
        {255, 255, 0}, // 14
        {255, 255, 255} // 15
    };

public:
    static const int FULLSCREEN_WIDTH = 320;
    static const int FULLSCREEN_HEIGHT = 200;
    static const int FULLSCREEN_RAW_BIT_DEPTH = 4;
    static const int FULLSCREEN_DEPTH = 3; // RGB
    static const int TILE_WIDTH = 16;
    static const int TILE_HEIGHT = 16;
    static const int TILE_RAW_BIT_DEPTH = 5;
    static const int TILE_DEPTH = 4; // RGBA
    static const int TILES_PER_FILE = 50;
    static const int DROP_TILES_PER_FILE = 130;
    static const int DROP_TILES_HORIZONTAL = 13;
    static const int DROP_TILES_VERTICAL = DROP_TILES_PER_FILE / DROP_TILES_HORIZONTAL;
    static const int DROP_WIDTH = 208;
    static const int DROP_HEIGHT = 160;
    static const int DROP_DEPTH = 4;
    static const int MAN_TILES_PER_FILE = 12;
    static const int MAN_TILES_HORIZONTAL = 2;
    static const int MAN_TILES_VERTICAL = 2;
    static const int MAN_TILES_WIDTH = 32;
    static const int MAN_TILES_HEIGHT = 32;
    static const int MAN_TILES_DEPTH = 4;
    static const int FONT_WIDTH = 8;
    static const int FONT_HEIGHT = 8;
    static const int FONT_RAW_BIT_DEPTH = 5;
    static const int FONT_DEPTH = 4;
    static const int FONT_PER_FILE = 50;

    DukeImage();

    unsigned char *loadTileSingle(std::string fileName, int n);
    unsigned char *loadTiles(std::string fileName, unsigned char *image, int pitch, int destDepth);
    unsigned char *loadFullScreenImage(std::string fileName, unsigned char *image, int pitch, int destDepth);
    unsigned char *loadDrop(std::string fileName, unsigned char *image, int pitch, int destDepth);
    unsigned char *loadMan(std::string fileName, unsigned char *image, int pitch, int destDepth);
    unsigned char *loadFont(std::string fileName, unsigned char *image, int pitch, int destDepth);
};

#endif /* DNIMAGE_H */

