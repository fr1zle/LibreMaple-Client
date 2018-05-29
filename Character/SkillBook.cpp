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
#include "SkillBook.h"

#include "../Data/SkillData.h"

namespace jrc
{
void Skillbook::set_skill(std::int32_t id,
                          std::int32_t level,
                          std::int32_t mlevel,
                          std::int64_t expire)
{
    skillentries[id] = {level, mlevel, expire};
}

bool Skillbook::has_skill(std::int32_t id) const
{
    return skillentries.count(id) > 0;
}

std::int32_t Skillbook::get_level(std::int32_t id) const
{
    auto iter = skillentries.find(id);
    if (iter == skillentries.end())
        return 0;

    return iter->second.level;
}

std::int32_t Skillbook::get_masterlevel(std::int32_t id) const
{
    auto iter = skillentries.find(id);
    if (iter == skillentries.end())
        return 0;

    return iter->second.masterlevel;
}

std::int64_t Skillbook::get_expiration(std::int32_t id) const
{
    auto iter = skillentries.find(id);
    if (iter == skillentries.end())
        return 0;

    return iter->second.expiration;
}

std::map<std::int32_t, std::int32_t> Skillbook::collect_passives() const
{
    std::map<std::int32_t, std::int32_t> passives;
    for (auto& iter : skillentries) {
        if (SkillData::get(iter.first).is_passive()) {
            passives.emplace(iter.first, iter.second.level);
        }
    }
    return passives;
}
} // namespace jrc
