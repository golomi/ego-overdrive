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
 * File:   GiftBox.h
 * Author: thomas
 *
 * Created on 26. April 2022, 22:41
 */

#ifndef GIFTBOX_H
#define GIFTBOX_H

#include "NonDukeObject.h"

class GiftBox : public NonDukeObject {
private:

public:
    // GiftBox(int x, int y);
    GiftBox(int x, int y, int type);
    virtual ~GiftBox();

    //    virtual NonDukeObject* getSuccessorObject();

    virtual void hit(int h) override;
    virtual NonDukeObject* createSuccessorObject() override;

};

#endif /* GIFTBOX_H */

