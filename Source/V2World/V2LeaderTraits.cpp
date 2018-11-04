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


#include "V2LeaderTraits.h"
#include "../Log.h"

#include "wiz/load_data.h"


V2TraitConversion::V2TraitConversion(const wiz::load_data::UserType* obj)
{
	trait = obj->GetName().ToString();

	std::vector<wiz::load_data::ItemType<wiz::DataType>> reqObj = obj->GetItem("fire");
	if (reqObj.size() > 0)
	{
		req_fire = reqObj[0].Get(0).ToInt();
	}
	else
	{
		req_fire = 0;
	}

	reqObj = obj->GetItem("shock");
	if (reqObj.size() > 0)
	{
		req_shock = reqObj[0].Get(0).ToInt();
	}
	else
	{
		req_shock = 0;
	}

	reqObj = obj->GetItem("manuever");
	if (reqObj.size() > 0)
	{
		req_manuever = reqObj[0].Get(0).ToInt();
	}
	else
	{
		req_manuever = 0;
	}

	reqObj = obj->GetItem("siege");
	if (reqObj.size() > 0)
	{
		req_siege = reqObj[0].Get(0).ToInt();
	}
	else
	{
		req_siege = 0;
	}

	reqObj = obj->GetItem("other");
	if (reqObj.size() > 0)
	{
		req_other = reqObj[0].Get(0).ToInt();
	}
	else
	{
		req_other = 0;
	}
}


bool V2TraitConversion::matches(int fire, int shock, int manuever, int siege) const
{
	if ( (fire < req_fire) || (shock < req_shock) || (manuever < req_manuever) || (siege < req_siege) )
	{
		return false;
	}

	// other consists of the sum of all non-required attributes
	if (req_other > 0)
	{
		int other	= (req_fire			!= 0 ? 0 : fire);
		other			+= (req_shock		!= 0 ? 0 : shock);
		other			+= (req_manuever	!= 0 ? 0 : manuever);
		other			+= (req_siege		!= 0 ? 0 : siege);

		if (other < req_other)
		{
			return false;
		}
	}

	return true;
}


V2LeaderTraits::V2LeaderTraits()
{
	wiz::load_data::UserType obj;

	if (!wiz::load_data::LoadData::LoadDataFromFile3("leader_traits.txt", obj, -1, 0))
	{
		LOG(LogLevel::Error) << "Could not parse file leader_traits.txt";
		exit(-1);
	}

	backgrounds.clear();
	std::vector<wiz::load_data::UserType*> traitObjs = obj.GetUserTypeItem("background");
	if (traitObjs.size() > 0)
	{
		for (long long x = 0; x < traitObjs[0]->GetUserTypeListSize(); ++x)
		{
			V2TraitConversion tc(traitObjs[0]->GetUserTypeList(x));
			backgrounds.push_back(std::move(tc));
		}
	}

	personalities.clear();
	traitObjs = obj.GetUserTypeItem("personality");
	if (traitObjs.size() > 0)
	{
		for (long long x= 0; x < traitObjs[0]->GetUserTypeListSize(); ++x)
		{
			V2TraitConversion tc(traitObjs[0]->GetUserTypeList(x));
			personalities.push_back(std::move(tc));
		}
	}

	if (backgrounds.size() == 0 || personalities.size() == 0)
	{
		LOG(LogLevel::Error) << "Trait conversion failed to initialize";
		exit(1);
	}
}


std::string V2LeaderTraits::getBackground(int fire, int shock, int manuever, int siege) const
{
	for (std::vector<V2TraitConversion>::const_iterator itr = backgrounds.begin(); itr != backgrounds.end(); ++itr)
	{
		if (itr->matches(fire, shock, manuever, siege))
		{
			return itr->trait;
		}
	}
	return "";
}

std::string V2LeaderTraits::getPersonality(int fire, int shock, int manuever, int siege) const
{
	for (std::vector<V2TraitConversion>::const_iterator itr = personalities.begin(); itr != personalities.end(); ++itr)
	{
		if (itr->matches(fire, shock, manuever, siege))
		{
			return itr->trait;
		}
	}
	return "";
}
