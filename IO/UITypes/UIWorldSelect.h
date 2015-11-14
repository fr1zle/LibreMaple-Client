/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 Daniel Allendorf                                        //
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
#include "IO\UIElement.h"
#include "IO\UIInterface.h"
#include "Net\Login\Login.h"
#include "Net\SessionInterface.h"

namespace IO
{
	using Net::SessionInterface;

	class UIWorldSelect : public UIElement
	{
	public:
		enum Buttons
		{
			BT_ENTERWORLD = 0,
			BT_WORLD0 = 1,
			BT_CHANNEL0 = 17
		};

		UIWorldSelect(UIInterface&, SessionInterface&);
		void buttonpressed(uint16_t) override;

	private:
		UIInterface& ui;
		SessionInterface& session;

		uint8_t worldid;
		uint8_t channelid;
	};

	class ElementWorldSelect : public Element
	{
	public:
		ElementWorldSelect(UIInterface& u, SessionInterface& ses) : ui(u), session(ses) {}

		UIType type() const override
		{
			return WORLDSELECT;
		}

		UIElement* instantiate() const override
		{
			return new UIWorldSelect(ui, session);
		}
	private:
		UIInterface& ui;
		SessionInterface& session;
	};
}

