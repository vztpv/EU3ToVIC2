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


// 2018.11.04 SOUTH KOREA (vztpv@naver.com)


#include <cstdlib>

#include "V2Factory.h"
#include "../Log.h"
#include "../Configuration.h"

#include "wiz/load_data.h"


V2FactoryType::V2FactoryType(const wiz::load_data::UserType* factory)
{
	name = factory->GetName().ToString();

	std::vector<wiz::load_data::ItemType<wiz::DataType>> is_coastal = factory->GetItem("is_coastal");
	if ((is_coastal.size() > 0) && (is_coastal[0].Get(0).ToString() == "yes"))
	{
		requireCoastal = true;
	}
	else
	{
		requireCoastal = false;
	}

	requireTech						= "";
	vanillaRequiredInvention	= (vanillaInventionType)-1;
	HODRequiredInvention			= (HODInventionType)-1;
	HODNNMRequiredInvention		= (HODNNMInventionType)-1;

	std::vector<wiz::load_data::ItemType<wiz::DataType>> local_supply = factory->GetItem("limit_by_local_supply");
	if ((local_supply.size() > 0) && (local_supply[0].Get(0).ToString() == "yes"))
	{
		requireLocalInput = true;
	}
	else
	{
		requireLocalInput = false;
	}

	inputs.clear();
	std::vector<wiz::load_data::UserType*> inputGoods = factory->GetUserTypeItem("input_goods");
	if (inputGoods.size() > 0)
	{
		for (long long x = 0; x < inputGoods[0]->GetItemListSize(); ++x)
		{
			inputs.insert(std::make_pair(inputGoods[0]->GetItemList(x).GetName().ToString(),
				inputGoods[0]->GetItemList(x).Get(0).ToFloat()));
		}
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> outputGoodsObj = factory->GetItem("output_goods");
	if (outputGoodsObj.size() > 0)
	{
		outputGoods = outputGoodsObj[0].Get(0).ToString();
	}
}


void V2Factory::output(FILE* output) const
{
	fprintf(output, "state_building=\n");
	fprintf(output, "{\n");
	fprintf(output, "\tlevel=%d\n", level);
	fprintf(output, "\tbuilding = %s\n", type->name.c_str());
	fprintf(output, "\tupgrade = yes\n");
	fprintf(output, "}\n");
}


std::map<std::string,float> V2Factory::getRequiredRGO() const
{
	if (type->requireLocalInput)
	{
		return type->inputs;
	}
	else
	{
		std::map<std::string,float> emptyMap;
		emptyMap.clear();
		return emptyMap;
	}
}


void V2Factory::increaseLevel()
{
	level++;
}


V2FactoryFactory::V2FactoryFactory()
{
	// load required techs/inventions
	factoryTechReqs.clear();
	loadRequiredTechs(Configuration::getV2Path() + "\\technologies\\army_tech.txt");
	loadRequiredTechs(Configuration::getV2Path() + "\\technologies\\commerce_tech.txt");
	loadRequiredTechs(Configuration::getV2Path() + "\\technologies\\culture_tech.txt");
	loadRequiredTechs(Configuration::getV2Path() + "\\technologies\\industry_tech.txt");
	loadRequiredTechs(Configuration::getV2Path() + "\\technologies\\navy_tech.txt");
	factoryInventionReqs.clear();
	loadRequiredInventions(Configuration::getV2Path() + "\\inventions\\army_inventions.txt");
	loadRequiredInventions(Configuration::getV2Path() + "\\inventions\\commerce_inventions.txt");
	loadRequiredInventions(Configuration::getV2Path() + "\\inventions\\culture_inventions.txt");
	loadRequiredInventions(Configuration::getV2Path() + "\\inventions\\industry_inventions.txt");
	loadRequiredInventions(Configuration::getV2Path() + "\\inventions\\navy_inventions.txt");

	// load factory types
	factoryTypes.clear();
	wiz::load_data::UserType obj;
	
	if (!wiz::load_data::LoadData::LoadDataFromFile3((Configuration::getV2Path() + "\\common\\production_types.txt"), obj, -1, 0))
	{
		LOG(LogLevel::Error) << "Could not parse file " << Configuration::getV2Path() << "\\common\\production_types.txt";
		exit(-1);
	}

	for (long long x = 0; x < obj.GetUserTypeListSize(); ++x) // factoryObjs
	{
		V2FactoryType* ft = new V2FactoryType(obj.GetUserTypeList(x));
		map<string,string>::iterator reqitr = factoryTechReqs.find(ft->name);
		if (reqitr != factoryTechReqs.end())
		{
			ft->requireTech = reqitr->second;
		}
		reqitr = factoryInventionReqs.find(ft->name);
		if (reqitr != factoryInventionReqs.end())
		{
			for (int i = 0; i <= VANILLA_naval_exercises; ++i)
			{
				if (((Configuration::getV2Gametype() == "vanilla") || 
					(Configuration::getV2Gametype() == "AHD")) && (reqitr->second == vanillaInventionNames[i]))
				{
					ft->vanillaRequiredInvention = (vanillaInventionType)i;
					break;
				}
				else if ((Configuration::getV2Gametype() == "HOD") && (reqitr->second == HODInventionNames[i])) 
				{
					ft->HODRequiredInvention = (HODInventionType)i;
					break;
				}
				else if ((Configuration::getV2Gametype() == "HoD-NNM") && (reqitr->second == HODNNMInventionNames[i]))
				{
					ft->HODNNMRequiredInvention = (HODNNMInventionType)i;
					break;
				}
			}
		}
		factoryTypes[ft->name] = ft;
	}

	factoryCounts.clear();
	
	obj.clear();
	if (!wiz::load_data::LoadData::LoadDataFromFile3("starting_factories.txt", obj, -1, 0))
	{
		LOG(LogLevel::Error) << "Could not parse file starting_factories.txt";
		exit(-1);
	}
	std::vector<wiz::load_data::UserType*> top = obj.GetUserTypeItem("starting_factories");
	if (top.size() != 1)
	{
		LOG(LogLevel::Error) << "Could not load starting factory list!";
		exit(-1);
	}

	for (long long x = 0; x < top[0]->GetItemListSize(); ++x) // factories
	{
		auto& itr = top[0]->GetItemList(x);
		string factoryType = itr.GetName().ToString();
		int count = itr.Get(0).ToInt();

		std::map<std::string, V2FactoryType*>::iterator t = factoryTypes.find(factoryType);
		if (t == factoryTypes.end())
		{
			LOG(LogLevel::Error) << "Could not locate V2 factory type for starting factories of type " << factoryType;
			continue;
		}
		factoryCounts.push_back(std::pair<V2FactoryType*, int>(t->second, count));
	}
}


std::deque<V2Factory*> V2FactoryFactory::buildFactories() const
{
	std::deque<V2Factory*> retval;
	for (std::vector< std::pair<V2FactoryType*, int> >::const_iterator itr = factoryCounts.begin(); itr != factoryCounts.end(); ++itr)
	{
		for (int i = 0; i < itr->second; ++i)
		{
			V2Factory* newFactory = new V2Factory(itr->first);
			retval.push_back(newFactory);
		}
	}
	return retval;
}


void V2FactoryFactory::loadRequiredTechs(const string& filename)
{
	wiz::load_data::UserType obj;
	if (!wiz::load_data::LoadData::LoadDataFromFile3(filename.c_str(), obj, -1, 0))
	{
		LOG(LogLevel::Error) << "Could not parse file " << filename;
		exit(-1);
	}

	for (long long x = 0; x < obj.GetUserTypeListSize(); ++x) // techObjs
	{
		auto& itr = obj.GetUserTypeList(x);

		std::vector<wiz::load_data::ItemType<wiz::DataType>> building = itr->GetItem("activate_building");
		for (std::vector<wiz::load_data::ItemType<wiz::DataType>>::iterator bitr = building.begin(); bitr != building.end(); ++bitr)
		{
			factoryTechReqs.insert(std::make_pair((*bitr).Get(0).ToString(), itr->GetName().ToString()));
		}
	}
}


void V2FactoryFactory::loadRequiredInventions(const string& filename)
{
	wiz::load_data::UserType obj;

	if (!wiz::load_data::LoadData::LoadDataFromFile3(filename, obj, -1, 0))
	{
		LOG(LogLevel::Error) << "Could not parse file " << filename;
		exit(-1);
	}

	for (long long x = 0; x < obj.GetUserTypeListSize(); ++x) // invObjs
	{
		auto& itr = obj.GetUserTypeList(x);

		std::vector<wiz::load_data::UserType*> effect = itr->GetUserTypeItem("effect");
		if (effect.size() == 0)
		{
			continue;
		}
		std::vector<wiz::load_data::ItemType<wiz::DataType>> building = effect[0]->GetItem("activate_building");
		for (std::vector<wiz::load_data::ItemType<wiz::DataType>>::iterator bitr = building.begin(); bitr != building.end(); ++bitr)
		{
			factoryInventionReqs.insert(std::make_pair((*bitr).Get(0).ToString(), (itr)->GetName().ToString()));
		}
	}
}
