/*Copyright (c) 2014 The Paradox Game Converters Project

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


// 2018.10.24 SOUTH KOREA (vztpv@naver.com)

#ifndef EU3ARMY_H_
#define EU3ARMY_H_



#include <string>
#include <map>
#include <vector>


#include "wiz/load_data_types.h"


typedef enum
{
	// ground units
	infantry = 0,
	cavalry,
	artillery,
	// navy units
	big_ship,
	light_ship,
	galley,
	transport,
	// end of enum
	num_reg_categories
} RegimentCategory;


static const char* RegimentCategoryNames[] = {
	"infantry",
	"cavalry",
	"artillery",
	"big_ship",
	"light_ship",
	"galley",
	"transport"
};


typedef std::map<std::string, std::pair<RegimentCategory, int> > RegimentTypeMap;


class EU3Regiment // also Ship
{
	public:
		EU3Regiment(const wiz::load_data::UserType* obj);

		void					setCategory(const RegimentCategory cat) { category = cat; }
		void					setTypeStrength(const int typeStrength) { type_strength = typeStrength; }

		std::string				getName() const noexcept { return name; }
		std::string				getType() const noexcept { return type; }
		int						getHome() const noexcept { return home; }
		double					getStrength() const noexcept { return strength; }
		RegimentCategory		getCategory() const noexcept { return category; }
		int						getTypeStrength() const noexcept { return type_strength; }
private:
		std::string				name;
		std::string				type;
		int						home;
		double					strength;
		RegimentCategory		category;
		int						type_strength;
};


class EU3Army // also Navy
{
	public:
		EU3Army(const wiz::load_data::UserType* obj);
		void						resolveRegimentTypes(const RegimentTypeMap& regimentTypeMap);
		double						getAverageStrength(RegimentCategory category) const;
		int							getTotalTypeStrength(RegimentCategory category) const;
		int							getProbabilisticHomeProvince(RegimentCategory category) const;
		void						blockHomeProvince(int home);

		std::string					getName() const noexcept { return name; }
		int							getLocation() const noexcept { return location; }
		int							getAtSea() const noexcept { return at_sea; }
		int							getLeaderID() const noexcept { return leaderID; }
	private:
		std::string					name;
		int							location;
		int							at_sea;
		std::vector<EU3Regiment*>	regiments;
		std::vector<int>			blocked_homes;
		int							leaderID;
};


void AddCategoryToRegimentTypeMap(wiz::load_data::UserType* obj, RegimentCategory category, std::string categoryName, RegimentTypeMap& rtm);
void AddUnitFileToRegimentTypeMap(std::string directory, std::string name, RegimentTypeMap& rtm);



#endif