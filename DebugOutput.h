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
 * File:   DebugOutput.h
 * Author: thomas
 *
 * Created on 8. November 2021, 00:05
 */

#ifndef DEBUGOUTPUT_H
#define DEBUGOUTPUT_H

#include<vector>
#include<string>

#include <SDL2/SDL.h>

#include "GameCanvas.h"

class DebugOutput;

class DebugOutputNotifier {
public:
    virtual void notify() = 0;
};

class DebugOutput {
private:
    static std::vector<std::string>messages;
    static std::vector<DebugOutputNotifier*> notifiers;
    static void fireNotifiers();
public:
    static void draw(Canvas* renderer);
    static void addLine(std::string message);
    static void addNotifier(DebugOutputNotifier *notifier);
};



#endif /* DEBUGOUTPUT_H */

