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
 * File:   SaveGame.cpp
 * Author: thomas
 * 
 * Created on 10. August 2024, 22:34
 */

#include <cstring>

#include "SaveGame.h"

SaveGame::SaveGame() {
}

DukeSaveGame SaveGame::load(std::string fileName) {

    FILE *file = fopen((const char*) fileName.c_str(), "rb");

    DukeSaveGame saveGame;
    
    memset(&saveGame,0,sizeof(DukeSaveGame));

    if (file == NULL) {
        throw new SaveGameNotFoundException();
        // TODO: remove printf
        printf("Error opening the safe game file");
        return(saveGame);
    }

    // TODO: check for file size


    if (fread(&saveGame, sizeof (DukeSaveGame), 1, file) != 1) {
        throw new SaveGameCorruptException();
        // TODO: remove printf
        printf("Error while reading the safe game file");
        return(saveGame);
    }

    fclose(file);

    return saveGame;
}

void SaveGame::save(std::string fileName, DukeSaveGame safeGame) {
    FILE *file = fopen((const char*) fileName.c_str(), "wb");

    if (file == NULL) {
        throw new SaveGameNotFoundException();
        // TODO: remove printf
        printf("Error opening the save game file");
        return;
    }

    // TODO: check for file size


    if (fwrite(&safeGame, sizeof (DukeSaveGame), 1, file) != 1) {
        throw new SaveGameCorruptException();
        // TODO: remove printf
        printf("Error while reading the save game file");
        return;
    }

    fclose(file);

}
