/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2013 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef GTKEYBOARD_UTILS_H
#define GTKEYBOARD_UTILS_H

#include "GTKeyboardDriver.h"
#include "api/GTGlobals.h"

namespace U2 {

class GTKeyboardUtils {
public:
    static void selectAll(U2OpStatus&); // ctrl (or cmd on MacOS) + A
    static void copy(U2OpStatus&);      // ctrl (or cmd on MacOS) + C
    static void paste(U2OpStatus&);     // ctrl (or cmd on MacOS) + V
    static void cut(U2OpStatus&);       // ctrl (or cmd on MacOS) + X
};

} // namespace U2

#endif
