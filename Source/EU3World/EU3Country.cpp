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

// 2018.10.25 SOUTH KOREA (vztpv@naver.com)


#include "EU3Country.h"
#include "../Log.h"
#include "EU3Province.h"
#include "EU3Relations.h"
#include "EU3Loan.h"
#include "EU3Leader.h"
#include <algorithm>



EU3Country::EU3Country(const wiz::load_data::UserType* obj)
{
	tag = obj->GetName().ToString();

	provinces.clear();
	cores.clear();

	std::vector<wiz::load_data::ItemType<wiz::DataType>> nameObj = obj->GetItem("name");
	if (!nameObj.empty())
	{
		name = nameObj[0].Get(0).ToString();
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> adjectiveObj = obj->GetItem("adjective");
	if (!adjectiveObj.empty())
	{
		adjective = adjectiveObj[0].Get(0).ToString();
	}

	std::vector<wiz::load_data::UserType*> colorObj = obj->GetUserTypeItem("map_color");
	if (!colorObj.empty())
	{
		color = Color(colorObj[0]);
		// Countries whose colors are included in the object here tend to be generated countries,
		// i.e. colonial nations which take on the color of their parent. To help distinguish 
		// these countries from their parent's other colonies we randomly adjust the color.
		color.RandomlyFlunctuate(30);
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> capitalObj = obj->GetItem("capital");
	if (capitalObj.size() > 0)
	{
		capital = capitalObj[0].Get(0).ToInt();
	}
	else
	{
		capital = 0;
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> nfObj = obj->GetItem("national_focus");
	if (nfObj.size() > 0)
	{
		nationalFocus = nfObj[0].Get(0).ToInt();
	}
	else
	{
		nationalFocus = 0;
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> techGroupObj = obj->GetItem("technology_group");
	if (techGroupObj.size() > 0)
	{
		techGroup = techGroupObj[0].Get(0).ToString();
	}
	else
	{
		techGroup = "";
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> primaryCultureObj = obj->GetItem("primary_culture");
	if (primaryCultureObj.size() > 0)
	{
		primaryCulture = primaryCultureObj[0].Get(0).ToString();
	}
	else
	{
		primaryCulture = "";
	}

	acceptedCultures.clear();
	std::vector<wiz::load_data::ItemType<wiz::DataType>> acceptedCultureObj = obj->GetItem("accepted_culture");
	for (unsigned int i = 0; i < acceptedCultureObj.size(); i++)
	{
		acceptedCultures.push_back(acceptedCultureObj[i].Get(0).ToString());
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> religionObj = obj->GetItem("religion");
	if (religionObj.size() > 0)
	{
		religion = religionObj[0].Get(0).ToString();
	}
	else
	{
		religion = "";
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> prestigeObj = obj->GetItem("prestige");
	if (prestigeObj.size() > 0)
	{
		prestige = 100 * prestigeObj[0].Get(0).ToFloat();
	}
	else
	{
		prestige = -100.0;
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> cultureObj = obj->GetItem("cultural_tradition");
	if (cultureObj.size() > 0)
	{
		culture = 100 * cultureObj[0].Get(0).ToFloat();
	}
	else
	{
		culture = 0.0;
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> armyTraditionObj = obj->GetItem("army_tradition");
	if (armyTraditionObj.size() > 0)
	{
		armyTradition = 100 * armyTraditionObj[0].Get(0).ToFloat();
	}
	else
	{
		armyTradition = 0.0;
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> navyTraditionObj = obj->GetItem("navy_tradition");
	if (navyTraditionObj.size() > 0)
	{
		navyTradition = 100 * navyTraditionObj[0].Get(0).ToFloat();
	}
	else
	{
		navyTradition = 0.0;
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> stabilityObj = obj->GetItem("stability");
	if (stabilityObj.size() > 0)
	{
		stability = stabilityObj[0].Get(0).ToFloat();
	}
	else
	{
		stability = -3.0;
	}

	std::vector<wiz::load_data::UserType*> techsObj = obj->GetUserTypeItem("technology");
	if (techsObj.size() > 0)
	{
		std::vector<wiz::load_data::UserType*> techObj = techsObj[0]->GetUserTypeItem("land_tech");
		landTech = techObj[0]->GetItemList(0).Get(0).ToFloat();

		techObj = techsObj[0]->GetUserTypeItem("naval_tech");
		navalTech = techObj[0]->GetItemList(0).Get(0).ToFloat();

		techObj = techsObj[0]->GetUserTypeItem("trade_tech");
		tradeTech = techObj[0]->GetItemList(0).Get(0).ToFloat();

		techObj = techsObj[0]->GetUserTypeItem("production_tech");
		productionTech = techObj[0]->GetItemList(0).Get(0).ToFloat();

		techObj = techsObj[0]->GetUserTypeItem("government_tech");
		governmentTech = techObj[0]->GetItemList(0).Get(0).ToFloat();
	}
	else
	{
		landTech		= 0.0;
		navalTech		= 0.0;
		tradeTech		= 0.0;
		productionTech	= 0.0;
		governmentTech	= 0.0;
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> incomeObj = obj->GetItem("estimated_monthly_income");
	if (incomeObj.size() > 0)
	{
		estMonthlyIncome = incomeObj[0].Get(0).ToFloat();
	}
	else
	{
		estMonthlyIncome = 0.0;
	}

	std::vector<wiz::load_data::UserType*> investmentObj = obj->GetUserTypeItem("distribution");
	if (investmentObj.size() > 0)
	{
		armyInvestment			= investmentObj[0]->GetItemList(2).Get(0).ToFloat() * estMonthlyIncome;
		navyInvestment			= investmentObj[0]->GetItemList(3).Get(0).ToFloat() * estMonthlyIncome;
		commerceInvestment	= investmentObj[0]->GetItemList(4).Get(0).ToFloat() * estMonthlyIncome;
		industryInvestment	= investmentObj[0]->GetItemList(5).Get(0).ToFloat() * estMonthlyIncome;
		cultureInvestment		= investmentObj[0]->GetItemList(6).Get(0).ToFloat() * estMonthlyIncome;
	}
	else
	{
		armyInvestment			= 0.0;
		navyInvestment			= 0.0;
		commerceInvestment		= 0.0;
		industryInvestment		= 0.0;
		cultureInvestment		= 0.0;
	}

	flags.clear();
	std::vector<wiz::load_data::UserType*> flagObject = obj->GetUserTypeItem("flags");
	if (flagObject.size() > 0)
	{
		for (int i = 0; i < flagObject[0]->GetUserTypeListSize(); i++)
		{
			flags[flagObject[0]->GetUserTypeList(i)->GetName().ToString()] = true;
		}
	}
	flagObject	= obj->GetUserTypeItem("hidden_flags");
	if (flagObject.size() > 0)
	{
		for (int i = 0; i < flagObject[0]->GetUserTypeListSize(); i++)
		{
			flags[flagObject[0]->GetUserTypeList(i)->GetName().ToString()] = true;
		}
	}

	modifiers.clear();
	std::vector<wiz::load_data::UserType*> modifierObject = obj->GetUserTypeItem("modifier");
	for (unsigned int i = 0; i < modifierObject.size(); i++)
	{
		std::vector<wiz::load_data::ItemType<wiz::DataType>> nameObject = modifierObject[i]->GetItem("modifier"); 
		//cf) getLeaves(); -> also date is included..?
		if (nameObject.size() > 0)
		{
			modifiers[nameObject[0].Get(0).ToString()] = true;
		}
	}

	possibleDaimyo = false;
	leaders.clear();
	std::vector<wiz::load_data::UserType*> historyObj	= obj->GetUserTypeItem("history");
	if (historyObj.size() > 0)
	{
		std::vector<wiz::load_data::ItemType<wiz::DataType>> daimyoObj = historyObj[0]->GetItem("daimyo");
		if (daimyoObj.size() > 0)
		{
			possibleDaimyo = true;
		}

		date hundredYearsOld = date("1740.1.1");
		for (int i=0; i < historyObj[0]->GetUserTypeListSize(); ++i)
		{
			auto x = historyObj[0]->GetUserTypeList(i);
			// grab leaders from history, ignoring those that are more than 100 years old...
			if (date(x->GetName().ToString()) > hundredYearsOld)
			{
				std::vector<wiz::load_data::UserType*> leaderObjs = (x)->GetUserTypeItem("leader");
				for (std::vector<wiz::load_data::UserType*>::iterator litr = leaderObjs.begin(); litr != leaderObjs.end(); ++litr)
				{
					EU3Leader* leader = new EU3Leader(*litr);
					leaders.push_back(leader);
				}
			}
		}
	}

	// figure out which leaders are active, and ditch the rest
	std::vector<wiz::load_data::UserType*> activeLeaderObj = obj->GetUserTypeItem("leader");
	std::vector<int> activeIds;
	std::vector<EU3Leader*> activeLeaders;
	for (std::vector<wiz::load_data::UserType*>::iterator itr = activeLeaderObj.begin(); itr != activeLeaderObj.end(); ++itr)
	{
		activeIds.push_back((*itr)->GetItem("id")[0].Get(0).ToInt());
	}
	for (std::vector<EU3Leader*>::iterator itr = leaders.begin(); itr != leaders.end(); ++itr)
	{
		if (find(activeIds.begin(), activeIds.end(), (*itr)->getID()) != activeIds.end()) {
			activeLeaders.push_back(*itr);
		}
	}
	leaders.swap(activeLeaders);

	std::vector<wiz::load_data::ItemType<wiz::DataType>> governmentObj = obj->GetItem("government");
	if (governmentObj.size() > 0)
	{
		government = governmentObj[0].Get(0).ToString();
	}
	else
	{
		government = "";
	}

	// Read international relations leaves
	for (unsigned int i = 0; i < obj->GetUserTypeListSize(); ++i)
	{
		auto x = obj->GetUserTypeList(i);
		std::string key = x->GetName().ToString();

		if ((key.size() == 3) &&
			 (key.c_str()[0] >= 'A') && (key.c_str()[0] <= 'Z') &&
			 (key.c_str()[1] >= 'A') && (key.c_str()[1] <= 'Z') &&
			 (key.c_str()[2] >= 'A') && (key.c_str()[2] <= 'Z'))
		{
			EU3Relations* rel = new EU3Relations(x);
			relations.push_back(rel);
		}
	}

	armies.clear();
	std::vector<wiz::load_data::UserType*> armyObj = obj->GetUserTypeItem("army");
	for (std::vector<wiz::load_data::UserType*>::iterator itr = armyObj.begin(); itr != armyObj.end(); ++itr)
	{
		EU3Army* army = new EU3Army(*itr);
		armies.push_back(army);
	}
	std::vector<wiz::load_data::UserType*> navyObj = obj->GetUserTypeItem("navy");
	for (std::vector<wiz::load_data::UserType*>::iterator itr = navyObj.begin(); itr != navyObj.end(); ++itr)
	{
		EU3Army* navy = new EU3Army(*itr);
		armies.push_back(navy);
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> sliderObj = obj->GetItem("centralization_decentralization");
	if (sliderObj.size() > 0)
	{
		centralization_decentralization = sliderObj[0].Get(0).ToInt();
	}
	else
	{
		centralization_decentralization = 0;
	}
	sliderObj = obj->GetItem("aristocracy_plutocracy");
	if (sliderObj.size() > 0)
	{
		aristocracy_plutocracy = sliderObj[0].Get(0).ToInt();
	}
	else
	{
		aristocracy_plutocracy = 0;
	}
	sliderObj = obj->GetItem("serfdom_freesubjects");
	if (sliderObj.size() > 0)
	{
		serfdom_freesubjects = sliderObj[0].Get(0).ToInt();
	}
	else
	{
		serfdom_freesubjects = 0;
	}
	sliderObj = obj->GetItem("innovative_narrowminded");
	if (sliderObj.size() > 0)
	{
		innovative_narrowminded = sliderObj[0].Get(0).ToInt();
	}
	else
	{
		innovative_narrowminded = 0;
	}
	sliderObj = obj->GetItem("mercantilism_freetrade");
	if (sliderObj.size() > 0)
	{
		mercantilism_freetrade = sliderObj[0].Get(0).ToInt();
	}
	else
	{
		mercantilism_freetrade = 0;
	}
	sliderObj = obj->GetItem("offensive_defensive");
	if (sliderObj.size() > 0)
	{
		offensive_defensive = sliderObj[0].Get(0).ToInt();
	}
	else
	{
		offensive_defensive = 0;
	}
	sliderObj = obj->GetItem("land_naval");
	if (sliderObj.size() > 0)
	{
		land_naval = sliderObj[0].Get(0).ToInt();
	}
	else
	{
		land_naval = 0;
	}
	sliderObj = obj->GetItem("quality_quantity");
	if (sliderObj.size() > 0)
	{
		quality_quantity = sliderObj[0].Get(0).ToInt();
	}
	else
	{
		quality_quantity = 0;
	}

	nationalIdeas.clear();
	checkIdea(obj, "press_gangs");
	checkIdea(obj, "grand_navy");
	checkIdea(obj, "sea_hawks");
	checkIdea(obj, "superior_seamanship");
	checkIdea(obj, "naval_glory");
	checkIdea(obj, "excellent_shipwrights");
	checkIdea(obj, "naval_fighting_instruction");
	checkIdea(obj, "naval_provisioning");
	checkIdea(obj, "grand_army");
	checkIdea(obj, "military_drill");
	checkIdea(obj, "engineer_corps");
	checkIdea(obj, "battlefield_commisions");
	checkIdea(obj, "glorious_arms");
	checkIdea(obj, "national_conscripts");
	checkIdea(obj, "regimental_system");
	checkIdea(obj, "napoleonic_warfare");
	checkIdea(obj, "land_of_opportunity");
	checkIdea(obj, "merchant_adventures");
	checkIdea(obj, "colonial_ventures");
	checkIdea(obj, "shrewd_commerce_practise");
	checkIdea(obj, "vice_roys");
	checkIdea(obj, "quest_for_the_new_world");
	checkIdea(obj, "scientific_revolution");
	checkIdea(obj, "improved_foraging");
	checkIdea(obj, "vetting");
	checkIdea(obj, "bureaucracy");
	checkIdea(obj, "national_bank");
	checkIdea(obj, "national_trade_policy");
	checkIdea(obj, "espionage");
	checkIdea(obj, "bill_of_rights");
	checkIdea(obj, "smithian_economics");
	checkIdea(obj, "liberty_egalite_fraternity");
	checkIdea(obj, "ecumenism");
	checkIdea(obj, "church_attendance_duty");
	checkIdea(obj, "divine_supremacy");
	checkIdea(obj, "patron_of_art");
	checkIdea(obj, "deus_vult");
	checkIdea(obj, "humanist_tolerance");
	checkIdea(obj, "cabinet");
	checkIdea(obj, "revolution_and_counter");

	{
		std::vector<wiz::load_data::ItemType<wiz::DataType>> moneyObj = obj->GetItem("treasury");
		if (moneyObj.size() > 0)
		{
			treasury = moneyObj[0].Get(0).ToFloat();
		}
		else
		{
			treasury = 0.0;
		}

		moneyObj = obj->GetItem("last_bankrupt");
		if (moneyObj.size() > 0)
		{
			last_bankrupt = date(moneyObj[0].Get(0).ToString());
		}
		else
		{
			last_bankrupt = date();
		}
	}
	{
		loans.clear();
		std::vector<wiz::load_data::UserType*> moneyObj = obj->GetUserTypeItem("loan");
		for (std::vector<wiz::load_data::UserType*>::iterator itr = moneyObj.begin(); itr != moneyObj.end(); ++itr)
		{
			EU3Loan* loan = new EU3Loan(*itr);
			loans.push_back(loan);
		}
	}
	std::vector<wiz::load_data::ItemType<wiz::DataType>> diploObj = obj->GetItem("diplomats");
	if (diploObj.size() > 0)
	{
		diplomats = diploObj[0].Get(0).ToInt();
	}
	else
	{
		diplomats = 0;
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> badboyObj = obj->GetItem("badboy");
	if (badboyObj.size() > 0)
	{
		badboy = badboyObj[0].Get(0).ToFloat();
	}
	else
	{
		badboy = 0.0;
	}

	std::vector<wiz::load_data::ItemType<wiz::DataType>> legitObj = obj->GetItem("legitimacy");
	if (legitObj.size() > 0)
	{
		legitimacy = legitObj[0].Get(0).ToFloat();
	}
	else
	{
		legitimacy = 1.0;
	}
	{
		std::vector<wiz::load_data::ItemType<wiz::DataType>> moneyObj = obj->GetItem("inflation");
		if (moneyObj.size() > 0)
		{
			inflation = moneyObj[0].Get(0).ToFloat();
		}
		else
		{
			inflation = 0.0;
		}
	}
}


void EU3Country::readFromCommonCountry(const std::string& fileName, wiz::load_data::UserType* obj)
{
	if (name.empty())
	{
		// For this country's name we will use the stem of the file name.
		size_t extPos = fileName.find_last_of('.');
		name = fileName.substr(0, extPos);
	}

	if (!color)
	{
		// Read country color.
		auto colorObj = obj->GetUserTypeItem("color");
		if (colorObj[0])
		{
			color = Color(colorObj[0]);
		}
	}
}


void EU3Country::setLocalisationName(const unsigned int language, const std::string& name)
{
	namesByLanguage[language] = name;
}


void EU3Country::setLocalisationAdjective(const unsigned int language, const std::string& adjective)
{
	adjectivesByLanguage[language] = adjective;
}


void EU3Country::addProvince(EU3Province* province)
{
	provinces.push_back(province);
}


void EU3Country::addCore(EU3Province* core)
{
	cores.push_back(core);
}


bool EU3Country::hasModifier(const std::string& modifier) const
{
	std::map<std::string, bool>::const_iterator itr = modifiers.find(modifier);
	return (itr != modifiers.end());
}


bool EU3Country::hasNationalIdea(const std::string& ni) const
{
	std::set<std::string>::const_iterator itr = nationalIdeas.find(ni);
	return (itr != nationalIdeas.end());
}


bool EU3Country::hasFlag(const std::string& flag) const
{
	std::map<std::string, bool>::const_iterator itr = flags.find(flag);
	return (itr != flags.end());
}


void EU3Country::resolveRegimentTypes(const RegimentTypeMap& map)
{
	for (std::vector<EU3Army*>::iterator itr = armies.begin(); itr != armies.end(); ++itr)
	{
		(*itr)->resolveRegimentTypes(map);
	}
}


int EU3Country::getManufactoryCount() const
{
	int retval = 0;
	for (std::vector<EU3Province*>::const_iterator itr = provinces.begin(); itr != provinces.end(); ++itr)
	{
		if ((*itr)->hasBuilding("weapons"))
			++retval;
		if ((*itr)->hasBuilding("wharf"))
			++retval;
		if ((*itr)->hasBuilding("textile"))
			++retval;
		if ((*itr)->hasBuilding("refinery"))
			++retval;
	}
	return retval;
}


double EU3Country::inflationAdjust(double input) const
{
	return (input / (1.0 + (inflation / 100.0)));
}


double EU3Country::getBadboyLimit() const
{
	double badboyLimit = 30.0;

	// gov effects
	if (government == "despotic_monarchy" || government == "tribal_despotism")
		badboyLimit += 10.0;

	// modifier effects
	if (hasModifier("the_licensing_of_the_press_act"))
		badboyLimit -= 3.0;
	if (hasModifier("the_witchcraft_act"))
		badboyLimit -= 2.0;
	if (hasModifier("the_education_act"))
		badboyLimit -= 2.0;
	if (hasModifier("revocation_of_restraint_of_appeals"))
		badboyLimit -= 2.0;
	if (hasModifier("colonial_expansions"))
		badboyLimit -= 3.0;
	if (hasModifier("hire_privateers"))
		badboyLimit -= 3.0;
	if (hasModifier("the_anti_piracy_act"))
		badboyLimit -= 3.0;

	// ruler effects (DIP, tribal MIL) not taken into account - assume the best (DIP 8/MIL 8)
	badboyLimit += 8.0;

	// legitimacy effect (-5 at 0, +5 at 100)
	badboyLimit += 10 * (legitimacy - 0.5);

	return badboyLimit;
}


void EU3Country::eatCountry(EU3Country* target)
{
	// autocannibalism is forbidden
	if (target->getTag() == tag)
		return;

	// for calculation of weighted averages
	int totalProvinces = target->provinces.size() + provinces.size();
	if (totalProvinces == 0)
		totalProvinces = 1;
	double myWeight = (double)provinces.size() / (double)totalProvinces;
	double targetWeight = (double)target->provinces.size() / (double)totalProvinces;

	// acquire target's cores (always)
	for (unsigned int j = 0; j < target->cores.size(); j++)
	{
		addCore(target->cores[j]);
		target->cores[j]->addCore(tag);
		target->cores[j]->removeCore(target->tag);
	}

	// everything else, do only if this country actually currently exists
	if (target->provinces.size() > 0)
	{
		// acquire target's provinces
		for (unsigned int j = 0; j < target->provinces.size(); j++)
		{
			addProvince(target->provinces[j]);
			target->provinces[j]->setOwner(this);
		}

		// acquire target's armies, navies, admirals, and generals
		armies.insert(armies.end(), target->armies.begin(), target->armies.end());
		leaders.insert(leaders.end(), target->leaders.begin(), target->leaders.end());

		// acquire the target's treasury and income, as well as their liabilities
		treasury += target->treasury;
		estMonthlyIncome += target->estMonthlyIncome;
		loans.insert(loans.end(), target->loans.begin(), target->loans.end());

		// rebalance prestige, badboy, inflation and techs from weighted average
		prestige					= myWeight * prestige					+ targetWeight * target->prestige;
		badboy					= myWeight * badboy						+ targetWeight * target->badboy * (getBadboyLimit() / target->getBadboyLimit());
		inflation				= myWeight * inflation					+ targetWeight * target->inflation;
		landTech					= myWeight * landTech					+ targetWeight * target->landTech;
		navalTech				= myWeight * navalTech					+ targetWeight * target->navalTech;
		tradeTech				= myWeight * tradeTech					+ targetWeight * target->tradeTech;
		productionTech			= myWeight * productionTech			+ targetWeight * target->productionTech;
		governmentTech			= myWeight * governmentTech			+ targetWeight * target->governmentTech;
		armyInvestment			= myWeight * armyInvestment			+ targetWeight * target->armyInvestment;
		navyInvestment			= myWeight * navyInvestment			+ targetWeight * target->navyInvestment;
		commerceInvestment	= myWeight * commerceInvestment		+ targetWeight * target->commerceInvestment;
		industryInvestment	= myWeight * industryInvestment		+ targetWeight * target->industryInvestment;
		cultureInvestment		= myWeight * cultureInvestment		+ targetWeight * target->cultureInvestment;
		estMonthlyIncome		= myWeight * estMonthlyIncome			+ targetWeight * target->estMonthlyIncome;
	}

	// coreless, landless countries will be cleaned up automatically
	target->clearProvinces();
	target->clearCores();

	LOG(LogLevel::Debug) << "Merged " << target->tag << " into " << tag;
}


std::string EU3Country::getName(const unsigned int language) const
{
	if (namesByLanguage.empty() && language == 1) // english
	{
		return name;
	}

	std::map<int, std::string>::const_iterator findIter = namesByLanguage.find(language);
	if (findIter != namesByLanguage.end())
	{
		return findIter->second;
	}
	else
	{
		return "";
	}
}


std::string EU3Country::getAdjective(const unsigned int language) const
{
	if (adjectivesByLanguage.empty() && language == 1)	// english
	{
		return adjective;
	}

	std::map<int, std::string>::const_iterator findIter = adjectivesByLanguage.find(language);
	if (findIter != adjectivesByLanguage.end())
	{
		return findIter->second;
	}
	else
	{
		return "";
	}
}


void EU3Country::checkIdea(const wiz::load_data::UserType* countryObj, const std::string idea)
{
	std::vector<wiz::load_data::ItemType<wiz::DataType>> niObj;
	niObj = countryObj->GetItem(idea);
	if ((niObj.size() > 0) && (niObj[0].Get(0).ToString() == "yes"))
	{
		nationalIdeas.insert(idea);
	}
}


void EU3Country::clearProvinces()
{
	provinces.clear();
}


void EU3Country::clearCores()
{
	cores.clear();
}