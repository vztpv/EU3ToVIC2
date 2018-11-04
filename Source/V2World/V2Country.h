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

#ifndef V2COUNTRY_H_
#define V2COUNTRY_H_



#include "../CountryMapping.h"
#include "../Mapper.h"
#include "../Color.h"
#include "../Date.h"
#include "../EU3World/EU3Army.h"
#include "V2Localisation.h"
#include "V2Inventions.h"
#include "V2TechSchools.h"
#include <vector>
#include <set>

class EU3World;
class EU3Country;
class V2World;
class V2State;
class V2Province;
class V2Relations;
class V2Army;
class V2Reforms;
class V2UncivReforms;
class V2Factory;
class V2Creditor;
class V2Leader;
class V2LeaderTraits;
struct V2Party;



class V2Country
{
	public:
		V2Country(const std:: string& _tag, const string& _commonCountryFile, const vector<V2Party*>& _parties, V2World* _theWorld, bool _newCountry = false, bool _dynamicCountry = false);
		void								output() const;
		void								outputToCommonCountriesFile(FILE*) const;
		void								outputLocalisation(FILE*) const;
		void								outputOOB() const;
		void								initFromEU3Country(const EU3Country* _srcCountry, const std::vector<std::string>& outputOrder,
			const CountryMapping& countryMap, const cultureMapping& cultureMap, const religionMapping& religionMap, const unionCulturesMap& unionCultures,
			const governmentMapping& governmentMap, const inverseProvinceMapping& inverseProvinceMap, const std::vector<V2TechSchool>& techSchools, 
			const std::map<int, int>& leaderMap, const V2LeaderTraits& lt, const EU3RegionsMapping& regionsMap);
		void								initFromHistory();
		void								addProvince(V2Province* _province);
		void								addState(V2State* newState);
		void								convertArmies(const std::map<int,int>& leaderIDMap, double cost_per_regiment[num_reg_categories],
			const inverseProvinceMapping& inverseProvinceMap, const std::map<int, V2Province*>& allProvinces, const std::vector<int>& port_whitelist,
			const adjacencyMapping& adjacencyMap);
		bool								addFactory(V2Factory* factory);
		void								addRailroadtoCapitalState();
		void								convertUncivReforms();
		void								setupPops(EU3World& sourceWorld, double popWeightRatio);
		void								setArmyTech(double mean, double highest);
		void								setNavyTech(double mean, double highest);
		void								setCommerceTech(double mean, double highest);
		void								setIndustryTech(double mean, double highest);
		void								setCultureTech(double mean, double highest);
		void								addRelation(V2Relations* newRelation);

		V2Relations*					getRelations(const std::string& withWhom) const;
		void								getNationalValueScores(int& liberty, int& equality, int& order);

		void								addResearchPoints(double newPoints)	noexcept	{ researchPoints += newPoints; }
		void								addTech(const std::string& newTech)				noexcept { techs.push_back(newTech); }
		void								setNationalValue(const std::string& NV)			noexcept { nationalValue = NV; }
		void								isANewCountry(void)					noexcept { newCountry = true; }
		void								scalePrestige(double scale)			noexcept { prestige *= scale; }

		map<int, V2Province*>		getProvinces()													const noexcept { return provinces; }
		string							getTag()															const noexcept { return tag; };
		bool								isCivilized()													const noexcept { return civilized; };
		string							getPrimaryCulture()											const noexcept { return primaryCulture; };
		set<string>						getAcceptedCultures()										const noexcept { return acceptedCultures; };
		const EU3Country*				getSourceCountry()											const noexcept { return srcCountry; };
		inventionStatus				getInventionState(vanillaInventionType invention)	const { return vanillaInventions[invention]; };
		inventionStatus				getInventionState(HODInventionType invention)		const { return HODInventions[invention]; };
		inventionStatus				getInventionState(HODNNMInventionType invention)	const { return HODNNMInventions[invention]; };
		double							getReactionary()												const noexcept { return upperHouseReactionary; };
		double							getConservative()												const noexcept { return upperHouseConservative; };
		double							getLiberal()													const noexcept { return upperHouseLiberal; };
		string							getGovernment()												const noexcept { return government; };
		vector< pair<int, int> >	getReactionaryIssues()										const noexcept { return reactionaryIssues; };
		vector< pair<int, int> >	getConservativeIssues()										const noexcept { return conservativeIssues; };
		vector< pair<int, int> >	getLiberalIssues()											const noexcept { return liberalIssues; };
		double							getLiteracy()													const noexcept { return literacy; };
		int								getCapital()													const noexcept { return capital; };
		bool								isNewCountry()													const noexcept { return newCountry; };
		int								getNumFactories()												const noexcept { return numFactories; }
		double							getPrestige()													const noexcept { return prestige; };
	private:
		void			outputTech(FILE*) const ;
		void			outputElection(FILE*) const;
		void			addLoan(const std::string& creditor, double size, double interest);
		int			addRegimentToArmy(V2Army* army, RegimentCategory rc, const inverseProvinceMapping& inverseProvinceMap,
			const std::map<int, V2Province*>& allProvinces, const adjacencyMapping& adjacencyMap);
		std::vector<int>	getPortProvinces(std::vector<int> locationCandidates, const std::map<int, V2Province*>& allProvinces);
		V2Army*		getArmyForRemainder(RegimentCategory rc);
		V2Province*	getProvinceForExpeditionaryArmy();
		std::string		getRegimentName(RegimentCategory rc);

		V2World*							theWorld;
		const EU3Country*				srcCountry;
		std::string							filename;
		bool								newCountry;			// true if this country is being added by the converter, i.e. doesn't already exist in Vic2
		bool								dynamicCountry;	// true if this country is a Vic2 dynamic country
		std::string							tag;
		std::vector<V2State*>				states;
		std::map<int, V2Province*>		provinces;
		int								capital;
		bool								civilized;
		std::string							primaryCulture;
		std::set<std::string>						acceptedCultures;
		std::string							religion;
		std::vector<V2Party*>				parties;
		std::string							rulingParty;
		std::string							commonCountryFile;
		double							prestige;
		double							leadership;
		double							plurality;
		std::vector<std::string>					techs;
		inventionStatus				vanillaInventions[VANILLA_naval_exercises];
		inventionStatus				HODInventions[HOD_naval_exercises];
		inventionStatus				HODNNMInventions[HOD_NNM_naval_exercises];
		V2UncivReforms*				uncivReforms;
		double							researchPoints;
		std::string							techSchool;
		std::string							government;
		int								upperHouseReactionary;
		int								upperHouseConservative;
		int								upperHouseLiberal;
		std::vector< std::pair<int, int> >	reactionaryIssues;
		std::vector< std::pair<int, int> >	conservativeIssues;
		std::vector< std::pair<int, int> >	liberalIssues;
		std::map<std::string,V2Relations*>	relations;
		std::vector<V2Army*>				armies;
		V2Reforms*						reforms;
		std::string							nationalValue;
		double							money;
		date								lastBankrupt;
		std::map<std::string, V2Creditor*>	creditors;
		double							bankReserves;
		double							diploPoints;
		double							badboy;
		std::vector<V2Leader*>				leaders;
		double							literacy;
		V2Localisation					localisation;
		Color								color;
		int								unitNameCount[num_reg_categories];
		int								numFactories;
};

bool ProvinceRegimentCapacityPredicate(V2Province* prov1, V2Province* prov2);


#endif	// V2COUNTRY_H_