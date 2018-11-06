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

// 2018.11.06 SOUTH KOREA (vztpv@naver.com)

#include "V2TechSchools.h"
#include "../Log.h"

#include "wiz/load_data.h"



std::vector<techSchool> initTechSchools(const wiz::load_data::UserType* obj, const std::vector<std::string>& blockedTechSchools)
{
	std::vector<techSchool> techSchools;

	std::vector<wiz::load_data::UserType*> schoolObj = obj->GetUserTypeItem("schools");
	if (schoolObj.size() < 1)
	{
		LOG(LogLevel::Warning) << "Could not load tech schools";
	}
	
	for (long long x = 0; x < schoolObj[0]->GetUserTypeListSize(); ++x)
	{
		bool isBlocked = false;
		for (unsigned int j = 0; j < blockedTechSchools.size(); j++)
		{
			if(schoolObj[0]->GetUserTypeList(x)->GetName().ToString() == blockedTechSchools[j])
			{
				isBlocked = true;
			}
		}

		if (!isBlocked)
		{
			techSchool newSchool;
			newSchool.name						= schoolObj[0]->GetUserTypeList(x)->GetName().ToString();
			newSchool.armyInvestment = schoolObj[0]->GetUserTypeList(x)->GetItem("army_tech_research_bonus")[0].Get(0).ToFloat();
			newSchool.commerceInvestment	= schoolObj[0]->GetUserTypeList(x)->GetItem("commerce_tech_research_bonus")[0].Get(0).ToFloat();
			newSchool.cultureInvestment	= schoolObj[0]->GetUserTypeList(x)->GetItem("culture_tech_research_bonus")[0].Get(0).ToFloat();
			newSchool.industryInvestment	= schoolObj[0]->GetUserTypeList(x)->GetItem("industry_tech_research_bonus")[0].Get(0).ToFloat();
			newSchool.navyInvestment		= schoolObj[0]->GetUserTypeList(x)->GetItem("navy_tech_research_bonus")[0].Get(0).ToFloat();
			techSchools.push_back(newSchool);
		}
	}

	return techSchools;
}


std::vector<std::string> initBlockedTechSchools(const wiz::load_data::UserType *obj)
{
	std::vector<std::string> blockedTechSchools;

	if (obj->GetUserTypeListSize() <= 0)
	{
		return blockedTechSchools;
	}

	for (long long x=0; x < obj->GetUserTypeList(0)->GetItemListSize(); ++x)
	{
		blockedTechSchools.push_back(obj->GetUserTypeList(0)->GetItemList(x).Get(0).ToString());
	}

	return blockedTechSchools;
}