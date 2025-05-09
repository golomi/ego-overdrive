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
 * File:   TextWriter.h
 * Author: thomas
 *
 * Created on 5. August 2022, 15:24
 */

#ifndef TEXTWRITER_H
#define TEXTWRITER_H

#include "DukeTextureContainer.h"
#include "Canvas.h"

class TextWriter {
private:
    static DukeTextureContainer *textureContainer;
public:
    TextWriter();
    TextWriter(const TextWriter& orig);
    virtual ~TextWriter();
    static void print(Canvas* renderer, std::string text, int x, int y);
    static void setTextureContainer(DukeTextureContainer* intTextureContainer);
};

#endif /* TEXTWRITER_H */

