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

/** 
 * @class DukeImage Loads images from the Duke specific file formats
 */

#include <cstdio>
#include <iostream>

#include "DukeImage.h"

using namespace std;

DukeImage::DukeImage() {
}

unsigned char *DukeImage::loadFullScreenImage(std::string fileName, unsigned char *image, int pitch, int destDepth) {

    const int RAW_IMAGE_BYTE_SIZE = FULLSCREEN_WIDTH * FULLSCREEN_HEIGHT * FULLSCREEN_RAW_BIT_DEPTH / 8;

    unsigned char rawData[RAW_IMAGE_BYTE_SIZE];

    FILE *file = fopen((const char *) fileName.c_str(), "rb");
    if (file == NULL) {
        printf("Fehler beim Öffnen der Bild-Datei");
        return NULL;
    }


    if (fread(rawData, RAW_IMAGE_BYTE_SIZE, 1, file) != 1) {
        printf("Fehler beim Lesen der Datei");
        return NULL;
    }



    fclose(file);

    const int ROW_WIDTH = FULLSCREEN_WIDTH / 8; // as 1 bit/pixel
    const int BLOCK_SIZE = FULLSCREEN_HEIGHT * ROW_WIDTH;


    for (int y = 0; y < FULLSCREEN_HEIGHT; y++) {
        for (int x = 0; x < FULLSCREEN_WIDTH; x++) {
            int mod = 7 - (x % 8);
            int positionInBlock = y * ROW_WIDTH + (int) (x / 8);
            int b0 = (rawData[positionInBlock + BLOCK_SIZE * 0] >> mod)&1;
            int b1 = (rawData[positionInBlock + BLOCK_SIZE * 1] >> mod)&1;
            int b2 = (rawData[positionInBlock + BLOCK_SIZE * 2] >> mod)&1;
            int b3 = (rawData[positionInBlock + BLOCK_SIZE * 3] >> mod)&1;
            int color = b0 + b1 * 2 + b2 * 4 + b3 * 8;
            image[y * pitch + x * destDepth] = PALETTE[color][0];
            image[y * pitch + x * destDepth + 1] = PALETTE[color][1];
            image[y * pitch + x * destDepth + 2] = PALETTE[color][2];
        }

    }
    return image;
}

unsigned char *DukeImage::loadTileSingle(std::string fileName, int n) {


    unsigned char *image = new unsigned char[TILE_WIDTH * TILE_HEIGHT * TILE_DEPTH];

    const int RAW_IMAGE_BYTE_SIZE = TILE_WIDTH * TILE_HEIGHT * TILE_RAW_BIT_DEPTH / 8;

    unsigned char rawData[RAW_IMAGE_BYTE_SIZE];
    unsigned char preambleData[3];

    FILE *file = fopen(fileName.c_str(), "rb");

    if (file == NULL) {
        printf("Fehler beim Öffnen der Kachel-Datei");
        return NULL;
    }


    if (fread(preambleData, 3, 1, file) != 1) {
        printf("Fehler beim Lesen der Datei");
        return NULL;
    }
    // TODO: Präambel prüfen

    fseek(file, RAW_IMAGE_BYTE_SIZE*n, SEEK_CUR);
    fread(rawData, RAW_IMAGE_BYTE_SIZE, 1, file);

    fclose(file);

    const int ROW_WIDTH = 10; //TILE_WIDTH * TILE_RAW_BIT_DEPTH / 8;
    const int ROW_BLOCK_WIDTH = 5; //TILE_RAW_BIT_DEPTH;

    for (int y = 0; y < TILE_HEIGHT; y++) {
        for (int x = 0; x < TILE_WIDTH; x++) {
            int mod = 7 - (x % 8);
            int rowPosition = y * ROW_WIDTH;
            int positionInRow = (int) (x / 8);
            int bT = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 0] >> mod)&1;
            int b0 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 1] >> mod)&1;
            int b1 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 2] >> mod)&1;
            int b2 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 3] >> mod)&1;
            int b3 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 4] >> mod)&1;
            int color = b0 + b1 * 2 + b2 * 4 + b3 * 8;
            image[(y * (TILE_WIDTH) + x) * TILE_DEPTH + 0] = PALETTE[color][0];
            image[(y * (TILE_WIDTH) + x) * TILE_DEPTH + 1] = PALETTE[color][1];
            image[(y * (TILE_WIDTH) + x) * TILE_DEPTH + 2] = PALETTE[color][2];
            image[(y * (TILE_WIDTH) + x) * TILE_DEPTH + 3] = bT * 255;
        }

    }
    return image;
}

unsigned char *DukeImage::loadTiles(std::string fileName, unsigned char *image, int pitch, int destDepth) {

    // unsigned char *image = new unsigned char[TILE_WIDTH * TILE_HEIGHT * TILE_DEPTH * TILES_PER_FILE];

    const int RAW_IMAGE_BYTE_SIZE = TILE_WIDTH * TILE_HEIGHT * TILE_RAW_BIT_DEPTH / 8;

    unsigned char rawData[RAW_IMAGE_BYTE_SIZE * TILES_PER_FILE];
    unsigned char preambleData[3];

    FILE *file = fopen(fileName.c_str(), "rb");

    if (file == NULL) {
        printf("Fehler beim Öffnen der Kacheldatei");
        return NULL;
    }


    fread(preambleData, 3, 1, file);
    // TODO: Präambel prüfen

    fread(rawData, RAW_IMAGE_BYTE_SIZE * TILES_PER_FILE, 1, file);

    fclose(file);

    const int ROW_WIDTH = 10; //TILE_WIDTH * TILE_RAW_BIT_DEPTH / 8;
    const int ROW_BLOCK_WIDTH = 5; //TILE_RAW_BIT_DEPTH;

    for (int y = 0; y < TILE_HEIGHT * TILES_PER_FILE; y++) {
        for (int x = 0; x < TILE_WIDTH; x++) {
            int mod = 7 - (x % 8);
            int rowPosition = y * ROW_WIDTH;
            int positionInRow = (int) (x / 8);
            int bT = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 0] >> mod)&1;
            int b0 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 1] >> mod)&1;
            int b1 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 2] >> mod)&1;
            int b2 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 3] >> mod)&1;
            int b3 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 4] >> mod)&1;
            int color = b0 + b1 * 2 + b2 * 4 + b3 * 8;
            image[y * pitch + x * destDepth + 0] = PALETTE[color][0];
            image[y * pitch + x * destDepth + 1] = PALETTE[color][1];
            image[y * pitch + x * destDepth + 2] = PALETTE[color][2];
            image[y * pitch + x * destDepth + 3] = bT * 255;
        }

    }
    return image;
}

unsigned char *DukeImage::loadDrop(std::string fileName, unsigned char *image, int pitch, int destDepth) {


    const int RAW_IMAGE_BYTE_SIZE = TILE_WIDTH * TILE_HEIGHT * TILE_RAW_BIT_DEPTH / 8;

    unsigned char rawData[RAW_IMAGE_BYTE_SIZE * DROP_TILES_PER_FILE];
    unsigned char preambleData[3];

    //printf("Datei mit Hintergrundbild öffnen: %s\n", fileName.c_str());

    FILE *file = fopen((const char *) fileName.c_str(), "rb");

    if (file == NULL) {
        printf("Fehler beim Öffnen der Drop-Datei");
        return NULL;
    }


    if (fread(preambleData, 3, 1, file) != 1) {
        printf("Fehler beim Datei Lesen");
        return NULL;
    }
    // TODO: Präambel prüfen

    if (fread(rawData, RAW_IMAGE_BYTE_SIZE * DROP_TILES_PER_FILE, 1, file) != 1) {
        printf("Fehler beim Datei Lesen");
        return NULL;
    }

    fclose(file);

    const int ROW_WIDTH = 10; //TILE_WIDTH * TILE_RAW_BIT_DEPTH / 8;
    const int ROW_BLOCK_WIDTH = 5; //TILE_RAW_BIT_DEPTH;

    for (int ty = 0; ty < DROP_TILES_VERTICAL; ty++)
        for (int tx = 0; tx < DROP_TILES_HORIZONTAL; tx++)
            for (int y = 0; y < TILE_HEIGHT; y++)
                for (int x = 0; x < TILE_WIDTH; x++) {
                    int mod = 7 - (x % 8);
                    int rowPosition = y * ROW_WIDTH;
                    int positionInRow = (int) (x / 8);
                    int bT = (rawData[positionInRow * ROW_BLOCK_WIDTH + RAW_IMAGE_BYTE_SIZE * (tx + ty * DROP_TILES_HORIZONTAL) + rowPosition + 0] >> mod)&1;
                    int b0 = (rawData[positionInRow * ROW_BLOCK_WIDTH + RAW_IMAGE_BYTE_SIZE * (tx + ty * DROP_TILES_HORIZONTAL) + rowPosition + 1] >> mod)&1;
                    int b1 = (rawData[positionInRow * ROW_BLOCK_WIDTH + RAW_IMAGE_BYTE_SIZE * (tx + ty * DROP_TILES_HORIZONTAL) + rowPosition + 2] >> mod)&1;
                    int b2 = (rawData[positionInRow * ROW_BLOCK_WIDTH + RAW_IMAGE_BYTE_SIZE * (tx + ty * DROP_TILES_HORIZONTAL) + rowPosition + 3] >> mod)&1;
                    int b3 = (rawData[positionInRow * ROW_BLOCK_WIDTH + RAW_IMAGE_BYTE_SIZE * (tx + ty * DROP_TILES_HORIZONTAL) + rowPosition + 4] >> mod)&1;
                    int color = b0 + b1 * 2 + b2 * 4 + b3 * 8;
                    image[(y + ty * TILE_HEIGHT) * pitch + (x + tx * TILE_WIDTH) * destDepth + 0] = PALETTE[color][0];
                    image[(y + ty * TILE_HEIGHT) * pitch + (x + tx * TILE_WIDTH) * destDepth + 1] = PALETTE[color][1];
                    image[(y + ty * TILE_HEIGHT) * pitch + (x + tx * TILE_WIDTH) * destDepth + 2] = PALETTE[color][2];
                    image[(y + ty * TILE_HEIGHT) * pitch + (x + tx * TILE_WIDTH) * destDepth + 3] = bT * 255;
                }


    return image;
}

unsigned char *DukeImage::loadMan(std::string fileName, unsigned char *image, int pitch, int destDepth) {



    const int RAW_TILE_BYTE_SIZE = TILE_WIDTH * TILE_HEIGHT * TILE_RAW_BIT_DEPTH / 8;
    const int RAW_IMAGE_BYTE_SIZE = RAW_TILE_BYTE_SIZE * MAN_TILES_HORIZONTAL * MAN_TILES_VERTICAL;

    unsigned char rawData[RAW_IMAGE_BYTE_SIZE * MAN_TILES_PER_FILE];
    unsigned char preambleData[3];

    FILE *file = fopen((const char *) fileName.c_str(), "rb");

    if (file == NULL) {
        printf("Fehler beim Datei öffnen");
        return NULL;
    }


    fread(preambleData, 3, 1, file);
    // TODO: check preamble

    fread(rawData, RAW_IMAGE_BYTE_SIZE * MAN_TILES_PER_FILE, 1, file);

    fclose(file);

    const int ROW_WIDTH = 10; //TILE_WIDTH * TILE_RAW_BIT_DEPTH / 8;
    const int ROW_BLOCK_WIDTH = 5; //TILE_RAW_BIT_DEPTH;

    for (int ty = 0; ty < MAN_TILES_VERTICAL * MAN_TILES_PER_FILE; ty++)
        for (int tx = 0; tx < MAN_TILES_HORIZONTAL; tx++)
            for (int y = 0; y < TILE_HEIGHT; y++)
                for (int x = 0; x < TILE_WIDTH; x++) {
                    int mod = 7 - (x % 8);
                    int rowPosition = y * ROW_WIDTH;
                    int positionInRow = (int) (x / 8);
                    int bT = (rawData[positionInRow * ROW_BLOCK_WIDTH + RAW_TILE_BYTE_SIZE * (tx + ty * MAN_TILES_HORIZONTAL) + rowPosition + 0] >> mod)&1;
                    int b0 = (rawData[positionInRow * ROW_BLOCK_WIDTH + RAW_TILE_BYTE_SIZE * (tx + ty * MAN_TILES_HORIZONTAL) + rowPosition + 1] >> mod)&1;
                    int b1 = (rawData[positionInRow * ROW_BLOCK_WIDTH + RAW_TILE_BYTE_SIZE * (tx + ty * MAN_TILES_HORIZONTAL) + rowPosition + 2] >> mod)&1;
                    int b2 = (rawData[positionInRow * ROW_BLOCK_WIDTH + RAW_TILE_BYTE_SIZE * (tx + ty * MAN_TILES_HORIZONTAL) + rowPosition + 3] >> mod)&1;
                    int b3 = (rawData[positionInRow * ROW_BLOCK_WIDTH + RAW_TILE_BYTE_SIZE * (tx + ty * MAN_TILES_HORIZONTAL) + rowPosition + 4] >> mod)&1;
                    int color = b0 + b1 * 2 + b2 * 4 + b3 * 8;
                    image[(y + ty * TILE_HEIGHT) * pitch + (x + tx * TILE_WIDTH) * destDepth + 0] = PALETTE[color][0];
                    image[(y + ty * TILE_HEIGHT) * pitch + (x + tx * TILE_WIDTH) * destDepth + 1] = PALETTE[color][1];
                    image[(y + ty * TILE_HEIGHT) * pitch + (x + tx * TILE_WIDTH) * destDepth + 2] = PALETTE[color][2];
                    image[(y + ty * TILE_HEIGHT) * pitch + (x + tx * TILE_WIDTH) * destDepth + 3] = bT * 255;
                }


    return image;
}

unsigned char *DukeImage::loadFont(std::string fileName, unsigned char *image, int pitch, int destDepth) {

    // unsigned char *image = new unsigned char[ FONT_WIDTH * FONT_HEIGHT * FONT_PER_FILE * FONT_DEPTH];

    const int RAW_IMAGE_BYTE_SIZE = FONT_WIDTH * FONT_HEIGHT * FONT_RAW_BIT_DEPTH / 8;


    unsigned char rawData[RAW_IMAGE_BYTE_SIZE * FONT_PER_FILE];
    unsigned char preambleData[3];

    FILE *file = fopen((const char *) fileName.c_str(), "rb");

    if (file == NULL) {
        printf("Fehler beim öffnen der Font-Datei");
        return NULL;
    }


    fread(preambleData, 3, 1, file);
    // TODO: check preamble

    fread(rawData, RAW_IMAGE_BYTE_SIZE * FONT_PER_FILE, 1, file);

    fclose(file);

    const int ROW_WIDTH = FONT_WIDTH * FONT_RAW_BIT_DEPTH / 8;
    const int ROW_BLOCK_WIDTH = 5; //TILE_RAW_BIT_DEPTH;

    for (int y = 0; y < FONT_HEIGHT * FONT_PER_FILE; y++) {
        for (int x = 0; x < FONT_WIDTH; x++) {
            int mod = 7 - (x % 8);
            int rowPosition = y * ROW_WIDTH;
            int positionInRow = (int) (x / 8);
            int bT = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 0] >> mod)&1;
            int b0 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 1] >> mod)&1;
            int b1 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 2] >> mod)&1;
            int b2 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 3] >> mod)&1;
            int b3 = (rawData[positionInRow * ROW_BLOCK_WIDTH + rowPosition + 4] >> mod)&1;
            int color = b0 + b1 * 2 + b2 * 4 + b3 * 8;
            image[(y * (FONT_WIDTH) + x) * FONT_DEPTH + 0] = PALETTE[color][0];
            image[(y * (FONT_WIDTH) + x) * FONT_DEPTH + 1] = PALETTE[color][1];
            image[(y * (FONT_WIDTH) + x) * FONT_DEPTH + 2] = PALETTE[color][2];
            image[(y * (FONT_WIDTH) + x) * FONT_DEPTH + 3] = bT * 255;
        }

    }
    return image;
}