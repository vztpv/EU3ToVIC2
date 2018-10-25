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

#include "EU3Army.h"
#include "../Log.h"
#include "wiz/load_data.h"


EU3Regiment::EU3Regiment(const wiz::load_data::UserType *obj)
{
	std::vector<wiz::load_data::ItemType<wiz::DataType>> objName = obj->GetItem("name");
	if (objName.size() > 0)
	{
		name = objName[0].Get(0).ToString();
	}
	else
	{
		name = "";
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> objType = obj->GetItem("type");
	if (objType.size() > 0)
	{
		type = objType[0].Get(0).ToString();
	}
	else
	{
		LOG(LogLevel::Warning) << "Regiment or Ship " << name << " has no type";
		type = "";
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> objHome = obj->GetItem("home");
	if (objHome.size() > 0)
	{
		home = objHome[0].Get(0).ToInt();
	}
	else
	{
		LOG(LogLevel::Warning) << "Regiment or Ship " << name << " has no home";
		home = -1;
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> objStr = obj->GetItem("strength");
	if (objStr.size() > 0)
	{
		strength = (double)objStr[0].Get(0).ToFloat();
	}
	else
	{
		strength = 0.0;
	}

	category		= num_reg_categories;
	type_strength	= 0;
}


EU3Army::EU3Army(const wiz::load_data::UserType *obj)
{
	std::vector<wiz::load_data::ItemType<wiz::DataType>> objName = obj->GetItem("name");
	if (objName.size() > 0)
	{
		name = objName[0].Get(0).ToString();
	}
	else
	{
		name = "";
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> objLoc = obj->GetItem("location");
	if (objLoc.size() > 0)
	{
		location = objLoc[0].Get(0).ToInt();
	}
	else
	{
		LOG(LogLevel::Warning) << "Army or Navy " << name << " has no location";
		location = -1;
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> objAtSea = obj->GetItem("at_sea");
	if (objAtSea.size() > 0)
	{
		at_sea = objAtSea[0].Get(0).ToInt();
	}
	else
	{
		at_sea = 0;
	}

	regiments.clear();
	std::vector<wiz::load_data::UserType*> objRegs = obj->GetUserTypeItem("regiment");
	for (std::vector<wiz::load_data::UserType*>::iterator itr = objRegs.begin(); itr != objRegs.end(); ++itr)
	{
		EU3Regiment* reg = new EU3Regiment(*itr);
		regiments.push_back(reg);
	}
	std::vector<wiz::load_data::UserType*> objShips = obj->GetUserTypeItem("ship");
	for (std::vector<wiz::load_data::UserType*>::iterator itr = objShips.begin(); itr != objShips.end(); ++itr)
	{
		EU3Regiment* reg = new EU3Regiment(*itr);
		regiments.push_back(reg);
	}

	blocked_homes.clear();

	std::vector<wiz::load_data::UserType*> objLeader = obj->GetUserTypeItem("leader");
	if (objLeader.size() > 0)
	{
		//objLeader = objLeader[0]->getValue("id");
		leaderID = objLeader[0]->GetItem("id")[0].Get(0).ToInt();
	}
	else
	{
		leaderID = 0;
	}
}


void EU3Army::resolveRegimentTypes(const RegimentTypeMap& regimentTypeMap)
{
	for (std::vector<EU3Regiment*>::iterator itr = regiments.begin(); itr != regiments.end(); ++itr)
	{
		RegimentTypeMap::const_iterator ritr = regimentTypeMap.find( (*itr)->getType() );
		if (ritr != regimentTypeMap.end())
		{
			(*itr)->setCategory(ritr->second.first);
			(*itr)->setTypeStrength(ritr->second.second);
		}
		else
		{
			LOG(LogLevel::Warning) << "Unknown unit type " << (*itr)->getType() << " for regiment \"" << (*itr)->getName() << "\"\n";
		}
	}
}


double EU3Army::getAverageStrength(RegimentCategory category) const
{
	int count = 0;
	double total = 0.0;
	for (std::vector<EU3Regiment*>::const_iterator itr = regiments.begin(); itr != regiments.end(); ++itr)
	{
		if ( (*itr)->getCategory() == category )
		{
			total += (*itr)->getStrength();
			++count;
		}
	}
	return (total / count);
}


int EU3Army::getTotalTypeStrength(RegimentCategory category) const
{
	int total = 0;
	for (std::vector<EU3Regiment*>::const_iterator itr = regiments.begin(); itr != regiments.end(); ++itr)
	{
		if ( (*itr)->getCategory() == category )
		{
			total += (*itr)->getTypeStrength();
		}
	}
	return total;
}


int EU3Army::getProbabilisticHomeProvince(RegimentCategory category) const
{
	std::vector<int> homeProvinces;
	for (std::vector<EU3Regiment*>::const_iterator itr = regiments.begin(); itr != regiments.end(); ++itr)
	{
		if ( (*itr)->getCategory() == category )
		{
			int home = (*itr)->getHome();
			bool blocked = false;
			for (std::vector<int>::const_iterator bitr = blocked_homes.begin(); bitr != blocked_homes.end(); ++bitr)
			{
				if (home == *bitr)
				{
					blocked = true;
					break;
				}
			}
			if (!blocked)
				homeProvinces.push_back(home);
		}
	}
	if (homeProvinces.size() == 0)
		return -1;

	return homeProvinces[int(homeProvinces.size() * ((double)rand() / RAND_MAX))];
}


void EU3Army::blockHomeProvince(int home)
{
	blocked_homes.push_back(home);
}


void AddCategoryToRegimentTypeMap(wiz::load_data::UserType* obj, RegimentCategory category, std::string categoryName, RegimentTypeMap& rtm)
{
	std::vector<wiz::load_data::UserType*> top = obj->GetUserTypeItem(categoryName);
	if (top.size() != 1)
	{
		LOG(LogLevel::Error) << "Could not get regiment type map for " << categoryName;
		exit(1);
	}
	std::vector<wiz::load_data::ItemType<wiz::DataType>> types = top[0]->GetItem("");
	if (types.size() == 0)
	{
		LOG(LogLevel::Error) << "No regiment types to map for " << categoryName;
		exit(1);
	}
	for (std::vector<wiz::load_data::ItemType<wiz::DataType>>::iterator itr = types.begin(); itr != types.end(); ++itr)
	{
		std::string type = (*itr).GetName().ToString();
		std::string strength = (*itr).Get(0).ToString();
		rtm[type] = std::pair<RegimentCategory, int>(category, atoi(strength.c_str()));
	}
}


void AddUnitFileToRegimentTypeMap(std::string directory, std::string name, RegimentTypeMap& rtm)
{
	wiz::load_data::UserType obj;

	if (!wiz::load_data::LoadData::LoadDataFromFile3((directory + "\\" + name + ".txt"), obj, 0, 0))
	{
		LOG(LogLevel::Error) << "Could not parse file " << directory << '\\' << name << ".txt";
		exit(-1);
	}

	int rc = -1;
	std::vector<wiz::load_data::ItemType<wiz::DataType>> typeObj = obj.GetItem("type");
	if (typeObj.size() < 1)
	{
		LOG(LogLevel::Warning) << "Unit file for " << name << " has no type";
		return;
	}
	std::string type = typeObj[0].Get(0).ToString();
	for (int i = 0; i < num_reg_categories; ++i)
	{
		if (type == RegimentCategoryNames[i]) {
			rc = i;
		}
	}
	if (rc == -1)
	{
		LOG(LogLevel::Warning) << "Unit file for " << name << " has unrecognized type " << type;
		return;
	}

	int unitStrength = 0;
	std::vector<wiz::load_data::ItemType<wiz::DataType>> strObj;
	strObj = obj.GetItem("maneuver");
	if (strObj.size() > 0) 
		unitStrength += strObj[0].Get(0).ToInt();
	strObj = obj.GetItem("offensive_morale");
	if (strObj.size() > 0)
		unitStrength += strObj[0].Get(0).ToInt();
	strObj = obj.GetItem("defensive_morale");
	if (strObj.size() > 0)
		unitStrength += strObj[0].Get(0).ToInt();
	strObj = obj.GetItem("offensive_fire");
	if (strObj.size() > 0)
		unitStrength += strObj[0].Get(0).ToInt();
	strObj = obj.GetItem("defensive_fire");
	if (strObj.size() > 0)
		unitStrength += strObj[0].Get(0).ToInt();
	strObj = obj.GetItem("offensive_shock");
	if (strObj.size() > 0)
		unitStrength += strObj[0].Get(0).ToInt();
	strObj = obj.GetItem("defensive_shock");
	if (strObj.size() > 0)
		unitStrength += strObj[0].Get(0).ToInt();
	strObj = obj.GetItem("hull_size");
	if (strObj.size() > 0)
		unitStrength += strObj[0].Get(0).ToInt();

	// give all transports equal weight for 1-to-1 conversion
	if (rc == transport)
	{
		unitStrength = 24;
	}

	if (unitStrength == 0)
	{
		LOG(LogLevel::Warning) << "Unit " << name << " has no strength";
		return;
	}

	rtm[name] = std::pair<RegimentCategory, int>((RegimentCategory)rc, unitStrength);
}