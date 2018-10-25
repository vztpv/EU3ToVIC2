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

#ifndef EU3COUNTRY_H_
#define EU3COUNTRY_H_



#include <set>
#include "EU3Army.h"
#include "../Color.h"
#include "../Date.h"

class EU3Province;
class EU3Relations;
class EU3Loan;
class EU3Leader;

#include "wiz/load_data_types.h"

class EU3Country
{
	public:
		EU3Country(const wiz::load_data::UserType* obj);

		// Add any additional information available from the specified country file.
		void readFromCommonCountry(const std::string& fileName, wiz::load_data::UserType*);

		void setLocalisationName(const unsigned int language, const std::string& name);
		void setLocalisationAdjective(const unsigned int language, const std::string& adjective);

		void							addProvince(EU3Province*);
		void							addCore(EU3Province*);
		bool							hasModifier(const std::string&) const;
		bool							hasNationalIdea(const std::string&) const;
		bool							hasFlag(const std::string&) const ;
		void							resolveRegimentTypes(const RegimentTypeMap& map);
		int							getManufactoryCount() const;
		double						inflationAdjust(double input) const;
		double						getBadboyLimit() const;
		void							eatCountry(EU3Country* target);

		std::string						getTag()										const noexcept { return tag; };
		std::vector<EU3Province*>		getProvinces()								const noexcept { return provinces; };
		std::vector<EU3Province*>		getCores()									const noexcept { return cores; };
		int							getCapital()								const noexcept { return capital; };
		int							getNationalFocus()						const noexcept { return nationalFocus; };
		std::string						getTechGroup()								const noexcept { return techGroup; };
		std::string						getPrimaryCulture()						const noexcept { return primaryCulture; };
		std::vector<std::string>				getAcceptedCultures()					const noexcept { return acceptedCultures; };
		std::string						getReligion()								const noexcept { return religion; };
		double						getPrestige()								const noexcept { return prestige; };
		double						getCulture()								const noexcept { return culture; };
		double						getArmyTradition()						const noexcept { return armyTradition; };
		double						getNavyTradition()						const noexcept { return navyTradition; };
		double						getStability()								const noexcept { return stability; };
		double						getLandTech()								const noexcept { return landTech; };
		double						getNavalTech()								const noexcept { return navalTech; };
		double						getTradeTech()								const noexcept { return tradeTech; };
		double						getProductionTech()						const noexcept { return productionTech; };
		double						getGovernmentTech()						const noexcept { return governmentTech; };
		double						getEstimatedMonthlyIncome()			const noexcept { return estMonthlyIncome; };
		double						getArmyInvestment()						const noexcept { return armyInvestment; };
		double						getNavyInvestment()						const noexcept { return navyInvestment; };
		double						getCommerceInvestment()					const noexcept { return commerceInvestment; };
		double						getIndustryInvestment()					const noexcept { return industryInvestment; };
		double						getCultureInvestment()					const noexcept { return cultureInvestment; };
		bool							getPossibleDaimyo()						const noexcept { return possibleDaimyo; };
		std::string						getGovernment()							const noexcept { return government; };
		std::vector<EU3Relations*>	getRelations()								const noexcept { return relations; };
		std::vector<EU3Army*>			getArmies()									const noexcept { return armies; };
		int							getCentralizationDecentralization()	const noexcept { return centralization_decentralization; };
		int							getAristocracyPlutocracy()				const noexcept { return aristocracy_plutocracy; };
		int							getSerfdomFreesubjects()				const noexcept { return serfdom_freesubjects; };
		int							getInnovativeNarrowminded()			const noexcept { return innovative_narrowminded; };
		int							getMercantilismFreetrade()				const noexcept { return mercantilism_freetrade; };
		int							getOffensiveDefensive()					const noexcept { return offensive_defensive; };
		int							getLandNaval()								const noexcept { return land_naval; };
		int							getQualityQuantity()						const noexcept { return quality_quantity; };
		date							getLastBankrupt()							const noexcept { return last_bankrupt; };
		std::vector<EU3Loan*>			getLoans()									const noexcept { return loans; };
		double						getDiplomats()								const noexcept { return diplomats; };
		double						getBadboy()									const noexcept { return badboy; };
		std::vector<EU3Leader*>		getLeaders()								const noexcept { return leaders; };

		double						getTreasury()								const noexcept { return inflationAdjust(treasury); };

		std::string	getName() const noexcept  { return name; }
		std::string	getName(const unsigned int language) const;
		std::string	getAdjective(const unsigned int language) const;
		Color		getColor() const noexcept { return color; }

	private:
		void						checkIdea(const wiz::load_data::UserType*, const std::string);
		void						clearProvinces();
		void						clearCores();

		std::string					tag;
		std::vector<EU3Province*>	provinces;
		std::vector<EU3Province*>	cores;
		int							capital;
		int							nationalFocus;
		std::string					techGroup;
		std::string					primaryCulture;
		std::vector<std::string>	acceptedCultures;
		std::string					religion;
		double						prestige;
		double						culture;
		double						armyTradition;
		double						navyTradition;
		double						stability;
		double						landTech;
		double						navalTech;
		double						tradeTech;
		double						productionTech;
		double						governmentTech;
		double						estMonthlyIncome;
		double						armyInvestment;
		double						navyInvestment;
		double						commerceInvestment;
		double						industryInvestment;
		double						cultureInvestment;
		std::map<std::string, bool>	flags;
		std::map<std::string, bool>	modifiers;
		bool						possibleDaimyo;
		std::vector<EU3Leader*>		leaders;
		std::string					government;
		std::vector<EU3Relations*>	relations;
		std::vector<EU3Army*>		armies; // and navies...
		int							centralization_decentralization;
		int							aristocracy_plutocracy;
		int							serfdom_freesubjects;
		int							innovative_narrowminded;
		int							mercantilism_freetrade;
		int							offensive_defensive;
		int							land_naval;
		int							quality_quantity;
		std::set<std::string>		nationalIdeas;
		double						treasury;
		date						last_bankrupt;
		std::vector<EU3Loan*>		loans;
		double						diplomats;
		double						badboy;

		double						legitimacy;
		double						inflation;

		std::string	name;
		std::string	adjective;
		Color		color;

		// Localisation attributes
		std::map<int, std::string> namesByLanguage;
		std::map<int, std::string> adjectivesByLanguage;
};


#endif // EU3COUNTRY_H_