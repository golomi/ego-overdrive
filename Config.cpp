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
 * File:   Config.cpp
 * Author: thomas
 * 
 * Created on 10. September 2022, 18:25
 */

#include "Config.h"

#include <utility>   

std::map<std::string,std::string> Config::entries;

Config::Config() {
}

void Config::setDefaultConfig() {
    setEntry("episode1directory", "dukedata");
    setEntry("episode2directory", "dukedata");
    setEntry("episode3directory", "dukedata");

}

std::string Config::getEntry(std::string key) {

    std::map<std::string, std::string>::iterator it = entries.find(key);
    if (it != entries.end()) {
        return it->second;
    }

    return "";
}

void Config::setEntry(std::string key, std::string value) {
    entries.insert(std::pair<std::string, std::string>(key, value));
}

void Config::load(std::string fileName) {

}