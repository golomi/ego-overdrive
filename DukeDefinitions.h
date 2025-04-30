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
 * File:   DukeDefinitions.h
 * Author: thomas
 *
 * Created on 12. September 2021, 22:37
 */

#ifndef DUKEDEFINITIONS_H
#define DUKEDEFINITIONS_H

#include <string>


/**
 * This file contains constants resulting from the original game
 */

// basic graphic defintions

static const int TILE_WIDTH = 16;
static const int TILE_HEIGHT = 16;
static const int DUKE_WIDTH = TILE_WIDTH * 2;
static const int DUKE_HEIGHT = TILE_HEIGHT * 2;
static const int FONT_WIDTH = 8;
static const int FONT_HEIGHT = 8;

static const int SCREEN_MAP_AREA_TILE_WIDTH = 13;
static const int SCREEN_MAP_AREA_TILE_HEIGHT = 10;

static const int SCREEN_MAP_AREA_OFFSET_X = 16;
static const int SCREEN_MAP_AREA_OFFSET_Y = 16;

// games definitions

static const int SCREEN_MAX_SHIFT_DISTANCE_X = 5;
static const int SCREEN_MAX_SHIFT_DISTANCE_Y = 6;
static const int SCREEN_MAX_SHIFT_FALL_DISTANCE_Y = 9;
static const int FRAMES_PER_SECOND = 16;

// duke character definitions
static const int HEALTH_MAX = 8;
static const int FIREPOWER_MAX = 3;
static const int DUKE_FALL_RATE = 16; /** Pixel per tick */
static const int MAX_JUMP_RATE = 9;
static const int MAX_BOUNCING_RATE = 14;
static const int JUMP_RATE[MAX_JUMP_RATE] = {13, 11, 9, 7, 5, 3, 0, 0, 0};
static const int LONG_JUMP_RATE[MAX_JUMP_RATE] = {15, 13, 11, 9, 7, 5, 1, 0};
static const int BOUNCING_BALL_RATE[MAX_BOUNCING_RATE] = {-16, -12, -10, -4, -1, -1, 0, 0, 1, 1, 4, 10, 12, 16};
static const int INVINCIBLE_AFTER_HIT = 20; /** frames */
static const int MAX_BULLET_FLY_DISTANCE = 40; /** tiles */
static const int MAX_BULLET_COUNT = 4;
static const int BULLET_MOVE_SPEED = 16; /** pixel per frame */


// General object definitions

static const int MOVE_SPEED = 2; /** pixel per frame */

// Definitions for textures


// Position of object textures 0
static const int BULLET_TEXTURE_POSITION = 6 * TILE_HEIGHT;

static const int SHOE_TEXTURE_POSITION = 10 * TILE_HEIGHT;
static const int CLAW_TEXTURE_POSITION = 18 * TILE_HEIGHT;

static const int GUN_TEXTURE_POSITION = 43 * TILE_HEIGHT;

static const int FIRE_LEFT_TEXTURE_POSITION = 24 * TILE_HEIGHT;
static const int FIRE_RIGHT_TEXTURE_POSITION = 29 * TILE_HEIGHT;

// Position of object textures 1
static const int HEALTH_TEXTURE_POSITION = 11 * TILE_HEIGHT;
static const int GLOVE_TEXTURE_POSITION = 13 * TILE_HEIGHT;
static const int BOARD_TEXTURE_POSITION = 14 * TILE_HEIGHT;

//Position of object textures 2
static const int RED_KEY_TEXTURE_POSITION = 24 * TILE_HEIGHT;
static const int GREEN_KEY_TEXTURE_POSITION = 25 * TILE_HEIGHT;
static const int BLUE_KEY_TEXTURE_POSITION = 26 * TILE_HEIGHT;
static const int PURPLE_KEY_TEXTURE_POSITION = 27 * TILE_HEIGHT;


// Defintions for loading world files

// TODO: replace SUBSTITUDE_TILE_DIRECTION_MAX to OBJECT_MAX
static const int MAP_OBJECT_MAX = 0x5F;

// map
static const int MAP_WIDTH = 128;
static const int MAP_HEIGHT = 90;
static const int MAP_TILE_BYTE_SIZE = 2;
static const int MAP_BYTE_SIZE = MAP_WIDTH * MAP_HEIGHT * MAP_TILE_BYTE_SIZE;

static const int MAX_WORLD_INDEX = 13;

static const unsigned int MAP_OBJECT_DUKE_START = 0x3032;

static const std::string noteText = "YOU ARE ABOUT TO ENTER\nTHE NEXT LEVEL. DON'T\n FORGET TO SAVE YOUR\nGAME.  GOOD LUCK!\n\n      PRESS ENTER:";

/**
 * Enum for the substitution table of the background objects
 */
enum SUBSTITUDE_TILE_DIRECTIONS {
    NONE, ABOVE, RIGHT, BELOW, LEFT
};

struct WorldDefinitions {
    int drop;
    int secondDrop;
};

const int DROP_BLACK = -1; /** purely black backround*/

/**
 * Data regarding world which is not definied in the world file
 * Currently only for episode 1
 */
static const WorldDefinitions WORLD_DEFINITIONS[3][12] = {
    { /*Episode 1*/
        {0, 0}, /*1*/
        {DROP_BLACK, 0}, /*2*/
        {0, 0}, /*3*/
        {7, 0}, /*4*/
        {5, 0}, /*5*/
        {DROP_BLACK, 0}, /*6*/
        {2, 0}, /*7*/
        {DROP_BLACK, 0}, /*8*/
        {3, 0}, /*9*/
        {DROP_BLACK, 0}, /*A*/
        {DROP_BLACK, 0}, /*B*/
        {13, 9}, /*C*/
    },
    { /*Episode 2*/
        {8, 0}, /*1*/
        {DROP_BLACK, 0}, /*2*/
        {0, 0}, /*3*/
        {7, 0}, /*4*/
        {5, 0}, /*5*/
        {DROP_BLACK, 0}, /*6*/
        {2, 0}, /*7*/
        {DROP_BLACK, 0}, /*8*/
        {3, 0}, /*9*/
        {DROP_BLACK, 0}, /*A*/
        {DROP_BLACK, 0}, /*B*/
        {13, 9}, /*C*/
    },
    { /*Episode 3*/
        {0, 0}, /*1*/
        {DROP_BLACK, 0}, /*2*/
        {0, 0}, /*3*/
        {7, 0}, /*4*/
        {5, 0}, /*5*/
        {DROP_BLACK, 0}, /*6*/
        {2, 0}, /*7*/
        {DROP_BLACK, 0}, /*8*/
        {3, 0}, /*9*/
        {DROP_BLACK, 0}, /*A*/
        {DROP_BLACK, 0}, /*B*/
        {13, 9}, /*C*/
    }
};

// TODO: load substitudeTileDirection from file
/**
 *  Table for substitution of the background of dynamic objects
 */
static const SUBSTITUDE_TILE_DIRECTIONS substitudeTileDirection[MAP_OBJECT_MAX + 1] = {
    /*0x00*/ LEFT,
    /*0x01*/ ABOVE,
    /*0x02*/ ABOVE,
    /*0x03*/ ABOVE,
    /*0x04*/ ABOVE,
    /*0x05*/ ABOVE,
    /*0x06*/ ABOVE,
    /*0x07*/ ABOVE,
    /*0x08*/ ABOVE,
    /*0x09*/ ABOVE,
    /*0x0A*/ ABOVE,
    /*0x0B*/ LEFT,
    /*0x0C*/ LEFT,
    /*0x0D*/ LEFT,
    /*0x0E*/ ABOVE,
    /*0x0F*/ ABOVE,
    /*0x10*/ LEFT,
    /*0x11*/ ABOVE,
    /*0x12*/ LEFT,
    /*0x13*/ ABOVE,
    /*0x14*/ ABOVE,
    /*0x15*/ LEFT,
    /*0x16*/ ABOVE,
    /*0x17*/ ABOVE,
    /*0x18*/ ABOVE,
    /*0x19*/ ABOVE,
    /*0x1A*/ ABOVE,
    /*0x1B*/ ABOVE,
    /*0x1C*/ ABOVE,
    /*0x1D*/ ABOVE,
    /*0x1E*/ ABOVE,
    /*0x1F*/ LEFT,
    /*0x20*/ ABOVE,
    /*0x21*/ LEFT,
    /*0x22*/ ABOVE,
    /*0x23*/ LEFT,
    /*0x24*/ LEFT,
    /*0x25*/ ABOVE,
    /*0x26*/ ABOVE,
    /*0x27*/ ABOVE,
    /*0x28*/ ABOVE,
    /*0x29*/ LEFT,
    /*0x2A*/ LEFT,
    /*0x2B*/ ABOVE,
    /*0x2C*/ ABOVE,
    /*0x2D*/ ABOVE,
    /*0x2E*/ LEFT,
    /*0x2F*/ ABOVE,
    /*0x30*/ ABOVE,
    /*0x31*/ LEFT,
    /*0x32*/ ABOVE,
    /*0x33*/ ABOVE,
    /*0x34*/ ABOVE,
    /*0x35*/ ABOVE,
    /*0x36*/ ABOVE,
    /*0x37*/ ABOVE,
    /*0x38*/ ABOVE,
    /*0x39*/ ABOVE,
    /*0x3A*/ ABOVE,
    /*0x3B*/ ABOVE,
    /*0x3C*/ ABOVE,
    /*0x3D*/ ABOVE,
    /*0x3E*/ NONE,
    /*0x3F*/ NONE,
    /*0x40*/ ABOVE,
    /*0x41*/ ABOVE,
    /*0x42*/ ABOVE,
    /*0x43*/ ABOVE,
    /*0x44*/ ABOVE,
    /*0x45*/ ABOVE,
    /*0x46*/ ABOVE,
    /*0x47*/ ABOVE,
    /*0x48*/ ABOVE,
    /*0x49*/ ABOVE,
    /*0x4A*/ ABOVE,
    /*0x4B*/ ABOVE,
    /*0x4C*/ RIGHT,
    /*0x4D*/ RIGHT,
    /*0x4E*/ RIGHT,
    /*0x4F*/ RIGHT,
    /*0x50*/ LEFT,
    /*0x51*/ ABOVE,
    /*0x52*/ ABOVE,
    /*0x53*/ LEFT,
    /*0x54*/ ABOVE,
    /*0x55*/ LEFT,
    /*0x56*/ LEFT,
    /*0x57*/ ABOVE,
    /*0x58*/ ABOVE,
    /*0x59*/ BELOW,
    /*0x5A*/ ABOVE,
    /*0x5B*/ ABOVE,
    /*0x5C*/ ABOVE,
    /*0x5D*/ ABOVE,
    /*0x5E*/ ABOVE,
    /*0x5F*/ NONE
};




#endif /* DUKEDEFINITIONS_H */

