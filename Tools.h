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
 * File:   Tools.h
 * Author: thomas
 *
 * Created on 30. April 2022, 12:35
 */

#ifndef TOOLS_H
#define TOOLS_H

class Tools {
private:

public:
    Tools();
    Tools(const Tools& orig);
    virtual ~Tools();

    static inline char getDirectorySeparator() {
#ifdef _WIN32
        return '\\';
#else
        return '/';
#endif
    }
};

#endif /* TOOLS_H */

