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

#ifndef V2PROVINCE_H_
#define V2PROVINCE_H_



#include "../Configuration.h"
#include "../EU3World/EU3World.h"
#include "../EU3World/EU3Country.h"

class V2Pop;
class V2Factory;
class V2Country;



struct V2Demographic
{
	std::string								culture;
	std::string								slaveCulture;
	std::string								religion;
	double								ratio;
	EU3Province*						oldProvince;
	EU3Country*							oldCountry;
};


class V2Province
{
	public:
		V2Province(const std::string& _filename);
		void output() const;
		void outputPops(FILE*) const;
		void convertFromOldProvince(const EU3Province* oldProvince);
		void determineColonial();
		void addCore(const std::string&);
		void addOldPop(const V2Pop*);
		void addMinorityPop(V2Pop*);
		void doCreatePops(WorldType game, double popWeightRatio, V2Country* _owner);
		void addFactory(V2Factory* factory);
		void addPopDemographic(V2Demographic d);

		int				getTotalPopulation() const;

		std::vector<V2Pop*>	getPops(const std::string& type) const;
		V2Pop*			getSoldierPopForArmy(bool force = false);
		std::pair<int, int>	getAvailableSoldierCapacity() const;
		std::string			getRegimentName(RegimentCategory rc);
		bool				hasCulture(const std::string& culture, float percentOfPopulation) const;
		
		void				clearCores()									{ cores.clear(); }
		void				setCoastal(bool _coastal)		noexcept			{ coastal = _coastal; }
		void				setName(const std::string& _name)				noexcept { name = _name; }
		void				setOwner(const std::string& _owner)				noexcept { owner = _owner; }
		void				setLandConnection(bool _connection)	noexcept { landConnection = _connection; }
		void				setSameContinent(bool _same)		noexcept { sameContinent = _same; }
		void				setFortLevel(int level)				noexcept { fortLevel = level; }
		void				setNavalBaseLevel(int level)		noexcept { navalBaseLevel = level; }
		void				setRailLevel(int level)				noexcept { railLevel = level; }
		void				setResettable(const bool _resettable)	noexcept { resettable = _resettable; }
		void				setSlaveProportion(const double _pro)	noexcept { slaveProportion = _pro; }

		const EU3Province*	getSrcProvince()		const noexcept  { return srcProvince; };
		int						getOldPopulation()	const	noexcept { return oldPopulation; };
		bool						getCOT()					const noexcept { return COT; };
		bool						wasInfidelConquest()	const noexcept { return originallyInfidel; };
		bool						wasColony()				const noexcept { return wasColonised; };
		bool						isColonial()			const noexcept { return colonial != 0; };
		std::string					getRgoType()			const noexcept { return rgoType; };
		std::string					getOwner()				const noexcept { return owner; };
		int						getNum()					const noexcept { return num; };
		std::string					getName()				const noexcept { return name; };
		bool						isCoastal()				const noexcept { return coastal; };
		bool						hasNavalBase()			const noexcept { return (navalBaseLevel > 0); };
		bool						hasLandConnection()	const noexcept { return landConnection; }
		std::vector<V2Pop*>			getPops()				const noexcept { return pops; }
	private:
		void outputUnits(FILE*) const;
		void createPops(WorldType game, const V2Demographic& d, double popWeightRatio, V2Country* _owner);
		void combinePops();
		bool growSoldierPop(V2Pop* pop);

		const EU3Province*		srcProvince;

		std::string						filename;
		bool							coastal;
		int							num;
		std::string						name;
		std::string						owner;
		std::vector<std::string>				cores;
		int							colonyLevel;
		int							colonial;
		bool							wasColonised;
		bool							landConnection;
		bool							sameContinent;
		bool							COT;
		bool							originallyInfidel;
		int							oldPopulation;
		std::vector<V2Demographic>	demographics;
		std::vector<const V2Pop*>		oldPops;
		std::vector<V2Pop*>				minorityPops;
		std::vector<V2Pop*>				pops;
		double						slaveProportion;
		std::string						rgoType;
		std::string						terrain;
		int							lifeRating;
		bool							slaveState;
		int							unitNameCount[num_reg_categories];
		int							fortLevel;
		int							navalBaseLevel;
		int							railLevel;
		std::map<std::string, V2Factory*>	factories;

		bool							resettable;
};



#endif // V2PROVINCE_H_