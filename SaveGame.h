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
 * File:   SaveGame.h
 * Author: thomas
 *
 * Created on 10. August 2024, 22:34
 */

#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <string>
#include <cstdint>

struct DukeSaveGame {
    uint16_t viewX; // 	View X position in half-tiles (8 pixels)
    uint16_t viewY; // 	View Y position in tiles
    uint16_t dukeX; // 	Duke's X position on screen relative to view position in half-tiles (8 pixels)
    uint16_t dukeY; // 	Duke's Y position on screen relative to view position in pixels
    uint16_t world; // 	Current level: odd values lead to intermediate worlds, even values lead to game worlds. 1: first intermediate word (WORLDAL2), 2: second "real" world (WORLDAL3), ...
    uint16_t firepower; // 	Amount of rays (1 to 4)
    uint16_t boots; // 	Jumping Boots (0 or 1). Set to 1 to have the jumping boots, other values have strange results.
    uint16_t claw; // glove (0 or 1). Set to 1 to have the hook.
    uint16_t health; // 	Hit points (1 to 9). Note that when the game displays no life bar, you still have one hit point.
    uint16_t glove; // 	Robohand (0 or 1). Set to 1 to have the Robohand.
    uint16_t hint1; // 	Secret tip 1 (0 or 1). "Find the key that goes here and press the UP ARROW."
    uint16_t hint2; // 	Secret tip 2 (0 or 1). "Press the up arrow to read the notes."
    uint16_t hint3; // 	Secret tip 3 (0 or 1). "Drink soda to increase your health!"
    uint16_t hint4; // 	Secret tip 4 (0 or 1). "Eat turkey to increase your health!"
    uint16_t hint5; // 	Secret tip 5 (0 or 1). "The nuclear molecule increases your health to maximum!"
    uint16_t hint6; // 	Secret tip 6 (0 or 1). "Press the up arrow to open the door"
    uint16_t hint7; // 	Secret tip 7 (0 or 1). "Press the up arrow to activate the elevators."
    uint16_t hint8; // 	Secret tip 8 (0 or 1). "Press the up arrow to activate the transporter."
    uint16_t hint9; // 	Secret tip 9 (0 or 1). "Press the up arrow here after you have found the Robohand"
    uint16_t hint10; // 	Secret tip 10 (0 or 1). "Find the access card and press the up arrow here"
    uint16_t hint11; // 	Secret tip 11 (0 or 1).
    uint16_t hint12; // 	Secret tip 12 (0 or 1).
};

class SaveGameException {
};

class SaveGameNotFoundException : public SaveGameException {
};

class SaveGameCorruptException : public SaveGameException {
};

class SaveGame {
private:
public:
    SaveGame();
    static DukeSaveGame load(std::string fileName);
    static void save(std::string fileName, DukeSaveGame safeGame);
};

#endif /* SAVEGAME_H */

