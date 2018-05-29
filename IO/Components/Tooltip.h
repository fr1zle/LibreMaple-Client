//////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright © 2015-2016 Daniel Allendorf                                   //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../../Template/Point.h"
#include "../UIElement.h"

#include <cstdint>

namespace jrc
{
/// Interface for tooltips, information windows about something
/// the mouse cursor is pointed at.
class Tooltip
{
public:
    /// Possible parent UIs for Tooltips.
    enum Parent { NONE, EQUIPINVENTORY, ITEMINVENTORY, SKILLBOOK, SHOP };

    static constexpr bool same_ui_type(Parent p, UIElement::Type t) noexcept
    {
        switch (p) {
        case NONE:
            return t == UIElement::Type::NONE;
        case EQUIPINVENTORY:
            return t == UIElement::Type::EQUIPINVENTORY;
        case ITEMINVENTORY:
            return t == UIElement::Type::ITEMINVENTORY;
        case SKILLBOOK:
            return t == UIElement::Type::SKILLBOOK;
        case SHOP:
            return t == UIElement::Type::SHOP;
        }

        return false;
    }

    virtual ~Tooltip() = default;

    virtual void draw(Point<std::int16_t> cursorpos) const = 0;
};
} // namespace jrc
