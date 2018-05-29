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
#include "MapDrops.h"

#include "../../Constants.h"
#include "../../Data/ItemData.h"
#include "Drop.h"
#include "ItemDrop.h"
#include "MesoDrop.h"
#include "nlnx/node.hpp"
#include "nlnx/nx.hpp"

namespace jrc
{
MapDrops::MapDrops()
{
    lootenabled = false;
}

void MapDrops::init()
{
    nl::node src = nl::nx::item["Special"]["0900.img"];

    mesoicons[BRONZE] = src["09000000"]["iconRaw"];
    mesoicons[GOLD] = src["09000001"]["iconRaw"];
    mesoicons[BUNDLE] = src["09000002"]["iconRaw"];
    mesoicons[BAG] = src["09000003"]["iconRaw"];
}

void MapDrops::draw(Layer::Id layer,
                    double viewx,
                    double viewy,
                    float alpha) const
{
    drops.draw(layer, viewx, viewy, alpha);
}

void MapDrops::update(const Physics& physics)
{
    for (; !spawns.empty(); spawns.pop()) {
        const DropSpawn& spawn = spawns.front();

        std::int32_t oid = spawn.get_oid();
        if (nullable_ptr<MapObject> drop = drops.get(oid)) {
            drop->makeactive();
        } else {
            std::int32_t itemid = spawn.get_itemid();
            bool meso = spawn.is_meso();
            if (meso) {
                MesoIcon mesotype = (itemid > 999)
                                        ? BAG
                                        : (itemid > 99)
                                              ? BUNDLE
                                              : (itemid > 49) ? GOLD : BRONZE;
                const Animation& icon = mesoicons[mesotype];
                drops.add(spawn.instantiate(icon));
            } else if (const ItemData& itemdata = ItemData::get(itemid)) {
                const Texture& icon = itemdata.get_icon(true);
                drops.add(spawn.instantiate(icon));
            }
        }
    }

    for (auto& mesoicon : mesoicons) {
        mesoicon.update();
    }

    drops.update(physics);

    lootenabled = true;
}

void MapDrops::spawn(DropSpawn&& spawn)
{
    spawns.emplace(std::move(spawn));
}

void MapDrops::remove(std::int32_t oid, std::int8_t mode, const PhysicsObject* looter)
{
    if (nullable_ptr<Drop> drop = drops.get(oid)) {
        drop->expire(mode, looter);
    }
}

void MapDrops::clear()
{
    drops.clear();
}

MapDrops::Loot MapDrops::find_loot_at(Point<std::int16_t> playerpos)
{
    if (!lootenabled)
        return {0, {}};

    for (auto& mmo : drops) {
        nullable_ptr<const Drop> drop = mmo.second.get();
        if (drop && drop->bounds().contains(playerpos)) {
            lootenabled = false;

            std::int32_t oid = mmo.first;
            Point<std::int16_t> position = drop->get_position();
            return {oid, position};
        }
    }
    return {0, {}};
}
} // namespace jrc
