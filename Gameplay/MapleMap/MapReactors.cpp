//////////////////////////////////////////////////////////////////////////////
// This file is part of the LibreMaple MMORPG client                        //
// Copyright © 2015-2016 Daniel Allendorf, 2018-2019 LibreMaple Team        //
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
#include "MapReactors.h"

#include "Reactor.h"

namespace jrc
{
void MapReactors::draw(Layer::Id layer,
                       double viewx,
                       double viewy,
                       float alpha) const
{
    reactors.draw(layer, viewx, viewy, alpha);
}

void MapReactors::update(const Physics& physics)
{
    for (; !spawns.empty(); spawns.pop()) {
        const ReactorSpawn& spawn = spawns.front();

        std::int32_t oid = spawn.get_oid();
        if (auto reactor = reactors.get(oid)) {
            reactor->activate();
        } else {
            reactors.add(spawn.instantiate(physics));
        }
    }

    reactors.update(physics);
}

void MapReactors::spawn(ReactorSpawn&& spawn)
{
    spawns.emplace(std::move(spawn));
}

void MapReactors::remove(std::int32_t oid,
                         std::int8_t state,
                         Point<std::int16_t> position)
{
    if (nullable_ptr<Reactor> reactor = reactors.get(oid)) {
        reactor->destroy(state, position);
    }
}

void MapReactors::clear()
{
    reactors.clear();
}
} // namespace jrc
