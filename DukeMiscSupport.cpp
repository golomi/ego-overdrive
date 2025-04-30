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
 * File:   DukeMiscSupport.cpp
 * Author: thomas
 * 
 * Created on 5. August 2022, 16:30
 */

#include "DukeMiscSupport.h"

#include <iomanip>

#include "Tools.h"

//DukeMiscSupport::DukeMiscSupport() {
//}


/**
 * 
 * @param mapIndex 1-12 (file names are in hex, 2 = transition map)
 * @param dukePartIndex Duke1 = 1, ...
 * @return 
 */
std::string DukeMiscSupport::generateDukeMapPath(int mapIndex, int dukePartIndex, std::string directory) {
 
    // move to sepate OS support 
    char directorySeparator = Tools::getDirectorySeparator();

    //  std::replace( directory.begin(), directory.end(), 'x', 'y'); // replace directory separators if necessary


    if (mapIndex >= 1 && mapIndex <= 12 && dukePartIndex >= 1 && dukePartIndex <= 3) {
        std::stringstream mapFileNameStream;
        mapFileNameStream << directory << directorySeparator << "WORLDAL" << std::hex << std::uppercase << mapIndex;
        mapFileNameStream << ".DN" << dukePartIndex;
        std::string mapFileName = mapFileNameStream.str();
        printf("%s\n", mapFileName.c_str());
        return (mapFileName);
    } else {
        return (std::string(""));
    }

}

/**
 * 
 * @param dropIndex 1-13 (file names are in hex, 2 = transition map)
 * @param dukePartIndex Duke1 = 1, ...
 * @return 
 */
std::string DukeMiscSupport::generateDukeDropPath(int dropIndex, int dukePartIndex, std::string directory) {
 
    // move to sepate OS support 
    char directorySeparator = Tools::getDirectorySeparator();

    //  std::replace( directory.begin(), directory.end(), 'x', 'y'); // replace directory separators if necessary


    if (dropIndex >= 0 && dropIndex <= 13 && dukePartIndex >= 1 && dukePartIndex <= 3) {
        std::stringstream mapFileNameStream;
        mapFileNameStream << directory << directorySeparator << "DROP" << dropIndex;
        mapFileNameStream << ".DN" << dukePartIndex;
        std::string mapFileName = mapFileNameStream.str();
        printf("%s\n", mapFileName.c_str());
        return (mapFileName);
    } else {
        return (std::string(""));
    }

}

