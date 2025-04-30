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
 * File:   DukeRenderContext.h
 * Author: thomas
 *
 * Created on 12. Januar 2024, 02:06
 */

#ifndef DUKEUPDATECONTEXT_H
#define DUKEUPDATECONTEXT_H

#include "UpdateContext.h"

#include "Duke.h"

class DukeUpdateContext : public UpdateContext {
private:
    Duke *dukes;
public:
    DukeUpdateContext(DukeViewPort *viewPort, Duke *duke);
    DukeUpdateContext(const DukeUpdateContext& orig);
    virtual ~DukeUpdateContext() override;
    Duke *getDuke(int i);
};

#endif /* DUKEUPDATECONTEXT_H */

