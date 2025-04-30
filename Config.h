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
 * File:   Config.h
 * Author: thomas
 *
 * Created on 10. September 2022, 18:25
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>

class Config {
private:
    static std::map<std::string,std::string> entries;
public:
     
    Config();
    static void setDefaultConfig();
    static std::string getEntry(std::string key);
    static void setEntry(std::string key, std::string value);
    static void load(std::string fileName);

  };

#endif /* CONFIG_H */

