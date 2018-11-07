﻿/*Copyright (c) 2014 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

// 2018.11.03 SOUTH KOREA (vztpv@naver.com)

#ifndef V2ARMY_H_
#define V2ARMY_H_



#include "../EU3World/EU3Army.h"



struct V2ArmyID
{
	public:
		V2ArmyID();
		void output(FILE* out, int indentlevel) const;

		int id;
		int type;
};


class V2Regiment // also Ship
{
	public:
		V2Regiment(RegimentCategory rc);
		void output(FILE* out) const;

		void setName(const std::string& _name)	noexcept { name = _name; };
		void setHome(int newHome)	noexcept { home = newHome; };

		bool					getShip()		const noexcept { return isShip; };
		RegimentCategory	getCategory()	const noexcept { return category; };
	private:
		V2ArmyID				id;
		std::string				name;
		std::string				type;
		int					home;
		bool					isShip;
		RegimentCategory	category;
};


class V2Army // also Navy
{
	private:
		bool valid = true;
	public:
		void noUse() {
			valid = false;
		}
	public:
		V2Army(EU3Army* oldArmy, const std::map<int, int>& leaderIDMap);
		void					output(FILE* out) const;
		void					addRegiment(V2Regiment reg);

		void					setLocation(int provinceID)			noexcept { location = provinceID; };
		void					setNavy(bool navy)			noexcept { isNavy = navy; };
		void					setArmyRemainders(RegimentCategory category, double remainder)	{ armyRemainders[category] = remainder; };

		std::string				getName() const noexcept { return name; };
		void					getRegimentCounts(int counts[num_reg_categories]) const;
		double				getArmyRemainder(RegimentCategory category) const { return armyRemainders[category]; };
		EU3Army*				getSourceArmy() const noexcept { return sourceArmy; };
		bool					getNavy() const noexcept { return isNavy; };
	private:
		V2ArmyID					id;
		std::string					name;
		int						location;
		std::vector<V2Regiment>	regiments;
		double					armyRemainders[num_reg_categories];
		EU3Army*					sourceArmy; // only valid during conversion
		bool						isNavy;
};



#endif