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

// 2018.10.26 SOUTH KOREA (vztpv@naver.com)


#include "Mapper.h"
#include "Log.h"
#include "Configuration.h"
#include "EU3World/EU3World.h"
#include "EU3World/EU3Country.h"
#include "EU3World/EU3Province.h"
#include "V2World/V2World.h"
#include "V2World/V2Country.h"
#include <algorithm>
#include <sys/stat.h>



void initProvinceMap(const wiz::load_data::UserType* obj, WorldType worldType, provinceMapping& provinceMap, inverseProvinceMapping& inverseProvinceMap, resettableMap& resettableProvinces)
{
	provinceMapping::iterator mapIter;

	if (obj->GetUserTypeListSize() < 1)
	{
		LOG(LogLevel::Error) << "No province mapping definitions loaded";
		return;
	}

	unsigned int mappingIdx = -1;
	for (int i = 0; i < obj->GetUserTypeListSize(); ++i)
	{
		switch (worldType)
		{
			case InNomine:
			{
				if (obj->GetUserTypeList(i)->GetName().ToString() == "in")
				{
					mappingIdx = i;
				}
				break;
			}
			case HeirToTheThrone:
			{
				if (obj->GetUserTypeList(i)->GetName().ToString() == "httt")
				{
					mappingIdx = i;
				}
				break;
			}
			case DivineWind:
			{
				if (obj->GetUserTypeList(i)->GetName().ToString() == "dw")
				{
					mappingIdx = i;
				}
				break;
			}
			case unknown:
			case VeryOld:
			default:
			{
				Log(LogLevel::Error) << "Unsupported world type. Cannot map provinces!";
				exit(-1);
			}
		}
	}

	LOG(LogLevel::Debug) << "Using world type " << obj->GetUserTypeList(mappingIdx)->GetName().ToString() << " mappings";
	std::vector<wiz::load_data::UserType*> data = obj->GetUserTypeList(mappingIdx)->GetUserTypeItem("link");

	for (std::vector<wiz::load_data::UserType*>::iterator i = data.begin(); i != data.end(); ++i) // ++i is faster than i++
	{
		std::vector<int> EU3nums;
		std::vector<int> V2nums;
		bool			resettable = false;

		for (int j=0; j < (*i)->GetItemListSize(); ++j)
		{
			std::string type = (*i)->GetItemList(j).GetName().ToString();
			if ("eu3" == type)
			{
				EU3nums.push_back((*i)->GetItemList(j).Get(0).ToInt());
			}
			else if ("vic" == type)
			{
				V2nums.push_back((*i)->GetItemList(j).Get(0).ToInt());
			}
			else if ("resettable" == type)
			{
				resettable = true;
			}
			else
			{
				LOG(LogLevel::Warning) << "Unknown data while mapping provinces";
			}
		}

		if (EU3nums.empty())
		{
			EU3nums.push_back(0);
		}
		if (V2nums.empty())
		{
			V2nums.push_back(0);
		}

		for (std::vector<int>::iterator j = V2nums.begin(); j != V2nums.end(); ++j)
		{
			if (*j != 0)
			{
				provinceMap.insert(std::make_pair(*j, EU3nums));
			}
			if (resettable)
			{
				resettableProvinces.insert(*j);
			}
		}
		for (std::vector<int>::iterator j = EU3nums.begin(); j != EU3nums.end(); ++j)
		{
			if (*j != 0)
			{
				inverseProvinceMap.insert(std::make_pair(*j, V2nums));
			}
		}
	}
}


static const std::vector<int> empty_vec;
const std::vector<int>& getV2ProvinceNums(const inverseProvinceMapping& invProvMap, int eu3ProvinceNum)
{
	inverseProvinceMapping::const_iterator itr = invProvMap.find(eu3ProvinceNum);
	if (itr == invProvMap.end())
	{
		return empty_vec;
	}
	else
	{
		return itr->second;
	}
}


typedef struct {
	int type;			// the type of adjacency 0 = normal, 1 = ford, 2 = river crossing
	int to;				// the province this one is adjacent to (expect one pointing back to this province)
	int via;				// the straight (if any) this crosses
	int unknown1;		// still unknown
	int unknown2;		// still unknown
	int pathX;			// the midpoint on the path drawn between provinces
	int pathY;			// the midpoint on the path drawn between provinces
	int unknown3;		// still unknown
	int unknown4;		// still unknown
} HODAdjacency;		// an entry in the HOD adjacencies.bin format
typedef struct {
	int type;			// the type of adjacency 0 = normal, 1 = ford, 2 = river crossing
	int to;				// the province this one is adjacent to (expect one pointing back to this province)
	int via;				// the straight (if any) this crosses
	int unknown1;		// still unknown
	int unknown2;		// still unknown
	int pathX;			// the midpoint on the path drawn between provinces
	int pathY;			// the midpoint on the path drawn between provinces
} AHDAdjacency;		// an entry in the AHD adjacencies.bin format
typedef struct {
	int type;			// the type of adjacency 0 = normal, 1 = ford, 2 = river crossing
	int to;				// the province this one is adjacent to (expect one pointing back to this province)
	int via;				// the straight (if any) this crosses
	int unknown1;		// still unknown
	int unknown2;		// still unknown
} VanillaAdjacency;	// an entry in the vanilla adjacencies.bin format
adjacencyMapping initAdjacencyMap()
{
	FILE* adjacenciesBin = nullptr;
	std::string filename = Configuration::getV2DocumentsPath() + "\\map\\cache\\adjacencies.bin";
	struct _stat st;
	if ((_stat(filename.c_str(), &st) != 0))
	{
		LOG(LogLevel::Warning) << "Could not find " << filename << " - looking in install folder";
		filename = Configuration::getV2Path() + "\\map\\cache\\adjacencies.bin";
	}
	fopen_s(&adjacenciesBin, filename.c_str(), "rb");
	if (adjacenciesBin == nullptr)
	{
		LOG(LogLevel::Error) << "Could not open " << filename;
		exit(1);
	}

	adjacencyMapping adjacencyMap;
	while (!feof(adjacenciesBin))
	{
		int numAdjacencies;
		if (fread(&numAdjacencies, sizeof(numAdjacencies), 1, adjacenciesBin) != 1)
		{
			break;
		}
		std::vector<int> adjacencies;	// the adjacencies for the current province
		for (int i = 0; i < numAdjacencies; i++)
		{
			if (Configuration::getV2Gametype() == "vanilla")
			{
				VanillaAdjacency readAdjacency;
				fread(&readAdjacency, sizeof(readAdjacency), 1, adjacenciesBin);
				adjacencies.push_back(readAdjacency.to);
			}
			else if (Configuration::getV2Gametype() == "AHD")
			{
				AHDAdjacency readAdjacency;
				fread(&readAdjacency, sizeof(readAdjacency), 1, adjacenciesBin);
				adjacencies.push_back(readAdjacency.to);
			}
			if ((Configuration::getV2Gametype() == "HOD") || (Configuration::getV2Gametype() == "HoD-NNM"))
			{
				HODAdjacency readAdjacency;
				fread(&readAdjacency, sizeof(readAdjacency), 1, adjacenciesBin);
				adjacencies.push_back(readAdjacency.to);
			}
		}
		adjacencyMap.push_back(adjacencies);
	}
	fclose(adjacenciesBin);

	/*FILE* adjacenciesData;
	fopen_s(&adjacenciesData, "adjacenciesData.csv", "w");
	fprintf(adjacenciesData, "From,To\n");
	for (unsigned int from = 0; from < adjacencyMap.size(); from++)
	{
		std::vector<int> adjacencies = adjacencyMap[from];
		for (unsigned int i = 0; i < adjacencies.size(); i++)
		{
			fprintf(adjacenciesData, "%d,%d\n", from, adjacencies[i]);
		}
	}
	fclose(adjacenciesData);*/
	
	return adjacencyMap;
}


void initContinentMap(const wiz::load_data::UserType* obj, continentMapping& continentMap)
{
	continentMap.clear();

	for (int i = 0; i < obj->GetUserTypeListSize(); ++i)
	{
		std::string continent = obj->GetUserTypeList(i)->GetName().ToString();
		std::vector<wiz::load_data::ItemType<wiz::DataType>> provinceNums = obj->GetUserTypeList(i)->GetItem("");
		for (unsigned int j = 0; j < provinceNums.size(); j++)
		{
			int province = provinceNums[j].Get(0).ToInt();
			continentMap.insert(std::make_pair(province, continent));
		}
	}
}


void mergeNations(EU3World& world, const wiz::load_data::UserType *mergeObj)
{
	std::vector<wiz::load_data::UserType*> rules = mergeObj->GetUserTypeItem("merge_nations");
	if (rules.size() < 0)
	{
		LOG(LogLevel::Debug) << "No nations have merging requested (skipping)";
		return;
	}

	for (int i = 0; i < rules[0]->GetItemListSize(); ++i) {
		if (rules[0]->GetItemList(i).GetName().ToString() == "merge_daimyos")
		{
			if (rules[0]->GetItemList(i).Get(0).ToString() == "yes")
			{
				uniteJapan(world);
			}
			continue;
		}
	}

	for (int i=0; i < rules[0]->GetUserTypeListSize(); ++i)
	{
		std::string masterTag;
		std::vector<std::string> slaveTags;
		bool enabled = false;
		for (int j=0; j < rules[0]->GetUserTypeList(i)->GetItemListSize(); ++j)
		{
			wiz::load_data::ItemType<wiz::DataType> ruleName = rules[0]->GetUserTypeList(i)->GetItemList(j);

			if (ruleName.GetName().ToString() == "merge" && ruleName.Get(0).ToString() == "yes")
			{
				enabled = true;
			}
			else if (ruleName.GetName().ToString() == "master")
			{
				masterTag = ruleName.Get(0).ToString();
			}
			else if (ruleName.GetName().ToString() == "slave")
			{
				slaveTags.push_back(ruleName.Get(0).ToString());
			}
		}
		EU3Country* master = world.getCountry(masterTag);
		if ( enabled && (master != nullptr) && (slaveTags.size() > 0) )
		{
			for (std::vector<std::string>::iterator sitr = slaveTags.begin(); sitr != slaveTags.end(); ++sitr)
			{
				master->eatCountry(world.getCountry(*sitr));
			}
		}
	}
}


void uniteJapan(EU3World& world)
{
	EU3Country* japan = world.getCountry("JAP");
	if (japan == nullptr)
	{
		return;
	}
	if( japan->hasFlag("united_daimyos_of_japan") )
	{
		return;
	}

	std::map<std::string, EU3Country*> countries = world.getCountries();
	for (std::map<std::string, EU3Country*>::iterator i = countries.begin(); i != countries.end(); ++i)
	{
		if ( i->second->getPossibleDaimyo() )
		{
			japan->eatCountry(i->second);
		}
	}
}


void removeEmptyNations(EU3World& world)
{
	std::map<std::string, EU3Country*> countries = world.getCountries();
	for (std::map<std::string, EU3Country*>::iterator i = countries.begin(); i != countries.end(); ++i)
	{
		std::vector<EU3Province*> provinces	= i->second->getProvinces();
		std::vector<EU3Province*> cores			= i->second->getCores();
		if ( (provinces.size()) == 0 && (cores.size() == 0) )
		{
			world.removeCountry(i->first);
			LOG(LogLevel::Debug) << "Removing empty nation " << i->first;
		}
	}
}


void removeDeadLandlessNations(EU3World& world)
{
	std::map<std::string, EU3Country*> allCountries = world.getCountries();

	std::map<std::string, EU3Country*> landlessCountries;
	for (std::map<std::string, EU3Country*>::iterator i = allCountries.begin(); i != allCountries.end(); ++i)
	{
		std::vector<EU3Province*> provinces = i->second->getProvinces();
		if (provinces.size() == 0)
		{
			landlessCountries.insert(*i);
		}
	}

	for (std::map<std::string, EU3Country*>::iterator countryItr = landlessCountries.begin(); countryItr != landlessCountries.end(); ++countryItr)
	{
		std::string primaryCulture		= countryItr->second->getPrimaryCulture();
		std::vector<EU3Province*> cores	= countryItr->second->getCores();
		bool cultureSurvives			= false;
		for (std::vector<EU3Province*>::iterator coreItr = cores.begin(); coreItr != cores.end(); ++coreItr)
		{
			if ( (*coreItr)->getOwner() == nullptr)
			{
				continue;
			}
			if (  (*coreItr)->getOwner()->getPrimaryCulture() == primaryCulture  )
			{
				continue;
			}

			std::vector<EU3PopRatio> popRatios = (*coreItr)->getPopRatios();
			double culturePercent = 0.0f;
			for (std::vector<EU3PopRatio>::iterator popItr = popRatios.begin(); popItr != popRatios.end(); ++popItr)
			{
				if (popItr->culture == primaryCulture)
				{
					culturePercent += popItr->popRatio;
				}
			}
			if ( culturePercent >= 0.5 )
			{
				cultureSurvives = true;
				break;
			}
		}

		if (cultureSurvives == false)
		{
			world.removeCountry( countryItr->first );
			LOG(LogLevel::Debug) << "Removing dead landless nation " << countryItr->first;
		}
	}
}


void removeLandlessNations(EU3World& world)
{
	std::map<std::string, EU3Country*> countries = world.getCountries();

	for (std::map<std::string, EU3Country*>::iterator i = countries.begin(); i != countries.end(); ++i)
	{
		std::vector<EU3Province*> provinces = i->second->getProvinces();
		if (provinces.empty())
		{
			world.removeCountry(i->first);
			LOG(LogLevel::Debug) << "Removing landless nation " << i->first;
		}
	}
}


void initStateMap(const wiz::load_data::UserType* obj, stateMapping& stateMap, stateIndexMapping& stateIndexMap)
{
	for (unsigned int i = 0; i < obj->GetUserTypeListSize(); ++i)
	{
		std::vector<wiz::load_data::ItemType<wiz::DataType>> provinces = obj->GetUserTypeList(i)->GetItem("");
		std::vector<int>		neighbors;

		for (std::vector<wiz::load_data::ItemType<wiz::DataType>>::iterator j = provinces.begin(); j != provinces.end(); ++j)
		{
			neighbors.push_back( j->Get(0).ToInt() );
			stateIndexMap.insert( std::make_pair( j->Get(0).ToInt(), i) );
		}
		for (std::vector<int>::iterator j = neighbors.begin(); j != neighbors.end(); ++j)
		{
			stateMap.insert(std::make_pair(*j, neighbors));
		}
	}
}


cultureMapping initCultureMap(const wiz::load_data::UserType* obj) // TODO: consider cleaning up the distinguishers
{
	cultureMapping cultureMap;

	for (int i=0; i < obj->GetUserTypeListSize(); ++i)
	{
		std::vector<std::string>		srcCultures;
		std::string						dstCulture;
		std::vector< distinguisher >	distinguishers;
		for (int j = 0; j < obj->GetUserTypeList(i)->GetItemListSize(); ++j)
		{
			const std::string type = obj->GetUserTypeList(i)->GetItemList(j).GetName().ToString();
			const std::string value = obj->GetUserTypeList(i)->GetItemList(j).Get(0).ToString();

			if (type == "vic")
			{
				dstCulture = value; // todo - std::move,  remove const ~ ?
			}
			else if (type == "eu3")
			{
				srcCultures.push_back(value);
			}
			else if (type == "owner")
			{
				distinguisher newD;
				newD.first = DTOwner;
				newD.second = value;
				distinguishers.push_back(std::move(newD));
			}
			else if (type == "religion")
			{
				distinguisher newD;
				newD.first = DTReligion;
				newD.second = value;
				distinguishers.push_back(newD);
			}
			else if (type == "region")
			{
				distinguisher newD;	// a new distinguiser
				newD.first	= DTRegion;
				newD.second = value;
				distinguishers.push_back(std::move(newD));
			}
		}

		for (std::vector<std::string>::iterator j = srcCultures.begin(); j != srcCultures.end(); ++j)
		{
			cultureStruct rule;
			rule.srcCulture		= (*j);
			rule.dstCulture		= dstCulture;
			rule.distinguishers	= distinguishers;
			cultureMap.push_back(std::move(rule));
		}
	}

	return cultureMap;
}


religionMapping initReligionMap(const wiz::load_data::UserType* obj)
{
	religionMapping religionMap;
	
	for (int i=0; i < obj->GetUserTypeListSize(); ++i)
	{
		std::string					dstReligion;
		std::vector<std::string>	srcReligion;

		for (int j=0; j < obj->GetUserTypeList(i)->GetItemListSize(); ++j)
		{
			std::string type = obj->GetUserTypeList(i)->GetItemList(j).GetName().ToString();
			std::string value = obj->GetUserTypeList(i)->GetItemList(j).Get(0).ToString();

			if (type == "vic" )
			{
				dstReligion = std::move(value);
			}
			else if (type == "eu3" )
			{
				srcReligion.push_back(std::move(value));
			}
		}

		for (std::vector<std::string>::iterator j = srcReligion.begin(); j != srcReligion.end(); ++j)
		{
			religionMap.insert(std::make_pair((*j), dstReligion));
		}
	}

	return religionMap;
}


unionMapping initUnionMap(const wiz::load_data::UserType* obj)
{
	unionMapping unionMap;

	for (int i=0; i < obj->GetUserTypeListSize(); ++i)
	{
		std::string tag;
		std::string culture;

		for (int j=0; j < obj->GetUserTypeList(i)->GetItemListSize(); ++j)
		{
			std::string name = obj->GetUserTypeList(i)->GetItemList(j).GetName().ToString();
			std::string value = obj->GetUserTypeList(i)->GetItemList(j).Get(0).ToString();


			if (name == "tag" )
			{
				tag = std::move(value);
			}
			if (name == "culture" )
			{
				culture = std::move(value);
			}
		}

		unionMap.push_back(std::make_pair(std::move(culture), std::move(tag)));
	}

	return unionMap;
}


governmentMapping initGovernmentMap(const wiz::load_data::UserType* obj)
{
	governmentMapping governmentMap;
	
	for (int i=0; i < obj->GetUserTypeListSize(); ++i)
	{
		std::string				dstGovernment;
		std::vector<std::string>		srcGovernments;

		for (int j = 0; j < obj->GetUserTypeList(i)->GetItemListSize(); ++j)
		{
			std::string type = obj->GetUserTypeList(i)->GetItemList(j).GetName().ToString();
			std::string value = obj->GetUserTypeList(i)->GetItemList(j).Get(0).ToString();

			if (type == "vic")
			{
				dstGovernment = std::move(value);
			}
			if (type == "eu3")
			{
				srcGovernments.push_back(std::move(value));
			}
		}

		for (std::vector<std::string>::iterator j = srcGovernments.begin(); j != srcGovernments.end(); ++j)
		{
			governmentMap.insert(make_pair((*j), dstGovernment));
		}
	}

	return governmentMap;
}


void initUnionCultures(const wiz::load_data::UserType* obj, unionCulturesMap& unionCultures, inverseUnionCulturesMap& inverseUnionCultures)
{
	for (int i = 0; i < obj->GetUserTypeListSize(); ++i)
	{
		bool						hasUnion = false;
		std::string					tag;
		std::vector<std::string>	cultures;

		for (int j = 0; j < obj->GetUserTypeList(i)->GetItemListSize(); ++j)
		{
			std::string name = obj->GetUserTypeList(i)->GetItemList(j).GetName().ToString();
			std::string value = obj->GetUserTypeList(i)->GetItemList(j).Get(0).ToString();

			if (name == "union")
			{
				hasUnion = true;
				tag = std::move(value);
			}
			else if (name == "dynasty_names")
			{
				continue;
			}
		}
		for(int j=0; j < obj->GetUserTypeList(i)->GetUserTypeListSize(); ++j)
		{
			std::string group = obj->GetUserTypeList(i)->GetName().ToString();
			std::string name = obj->GetUserTypeList(i)->GetUserTypeList(j)->GetName().ToString();

			cultures.push_back(name);
			inverseUnionCultures.insert(std::make_pair(std::move(name), std::move(group)));
		}

		if (hasUnion)
		{
			unionCultures[std::move(tag)] = std::move(cultures);
		}
	}
}


void initEU3RegionMap(const wiz::load_data::UserType *obj, EU3RegionsMapping& regions)
{
	regions.clear();

	for (int i=0; i < obj->GetUserTypeListSize(); ++i)
	{
		const wiz::load_data::UserType* regionsObj = obj->GetUserTypeList(i);

		std::string regionName = regionsObj->GetName().ToString();
		
		for (int j=0; j < regionsObj->GetItemListSize(); ++j)
		{
			int provinceNum = regionsObj->GetItemList(j).Get(0).ToInt();
			auto mapping = regions.find(provinceNum);
			if (mapping == regions.end())
			{
				std::set<std::string> newRegions;
				newRegions.insert(regionName);
				regions.insert(std::make_pair(provinceNum, std::move(newRegions)));
			}
			else
			{
				mapping->second.insert(regionName);
			}
		}
	}
}


std::string CardinalToOrdinal(int cardinal)
{
	int hundredRem = cardinal % 100;
	int tenRem = cardinal % 10;
	if (hundredRem - tenRem == 10)
	{
		return "th";
	}

	switch (tenRem)
	{
	case 1:
		return "st";
	case 2:
		return "nd";
	case 3:
		return "rd";
	default:
		return "th";
	}
}
