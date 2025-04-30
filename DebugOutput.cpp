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
 * File:   DebugOutput.cpp
 * Author: thomas
 * 
 * Created on 8. November 2021, 00:05
 */

#include "DebugOutput.h"

#include "TextWriter.h"


std::vector<std::string> DebugOutput::messages;
std::vector<DebugOutputNotifier*> DebugOutput::notifiers;

void DebugOutput::fireNotifiers() {
    for (int i = 0; i < (int)notifiers.size(); i++) {
        notifiers[i]->notify();
    }
}

void DebugOutput::draw(Canvas* renderer) {
    //if (messages.size() > 0) {
    //  for (int i = messages.size() >= 3 ? messages.size() - 3 : 0; i < messages.size(); i++) 
    int count = messages.size() >= 3 ? 3 : messages.size();
    int firstMessage = messages.size() - count;
    int i;
    for (i = 0; i < count; i++) {
        TextWriter::print(renderer, messages[i + firstMessage], 16, 16 + i * 12);
    }
    TextWriter::print(renderer, ">", 16, 16 + i * 12);
    //  }
}

void DebugOutput::addLine(std::string message) {
    messages.push_back(message);
    printf("DebugOutput: %s\n", message.c_str());
    fireNotifiers();
}

void DebugOutput::addNotifier(DebugOutputNotifier *notifier) {
    notifiers.push_back(notifier);
}
