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

#ifndef EU3PROVINCE_H_
#define EU3PROVINCE_H_


#include "../Date.h"
#include <string>
#include <vector>
#include <map>

#include "wiz/load_data_types.h"

class Object;
class EU3Country;



struct EU3PopRatio {
	std::string culture;
	std::string religion;
	double popRatio;
};


class EU3Province {
	public:
		EU3Province(const wiz::load_data::UserType* obj);

		void						addCore(const std::string& tag);
		void						removeCore(const std::string& tag);
		void						determineProvinceWeight();

		bool						wasColonised() const;
		bool						wasInfidelConquest() const;
		bool						hasBuilding(const std::string& building) const;

		std::vector<EU3Country*>	getCores(const std::map<std::string, EU3Country*>& countries) const;
		date						getLastPossessedDate(const std::string& tag) const;

		int						getNum()					const noexcept { return num; };
		double					getBaseTax()			const noexcept { return baseTax; }
		std::string					getOwnerString()		const noexcept { return ownerString; };
		EU3Country*				getOwner()				const noexcept { return owner; };
		int						getPopulation()		const noexcept { return population; };
		bool						isColony()				const noexcept { return colony; };
		bool						isCOT()					const noexcept { return centerOfTrade; };
		std::vector<EU3PopRatio>	getPopRatios()			const noexcept { return popRatios; };
		double					getTotalWeight()		const noexcept { return totalWeight; }
		int						getNumDestV2Provs()	const noexcept { return numV2Provs; };

		void						setTotalWeight(double totalWeight);
		void						checkManpower(const wiz::load_data::UserType* provinceObj);
		void						checkTradeGoods(const wiz::load_data::UserType* provinceObj);

		void						setOwner(EU3Country* newOwner)	noexcept { owner = newOwner; }
		void						setNumDestV2Provs(int _numV2Provs) noexcept { numV2Provs = _numV2Provs; }
		std::string					getProvName() const		noexcept				{ return provName; }

		// getters for weight attributes
		double						getProvTaxIncome()				const	noexcept { return provTaxIncome; }
		double						getProvProdIncome()				const	noexcept { return provProdIncome; }
		double						getProvMPWeight()					const	noexcept { return provMPWeight; }
		double						getProvTotalBuildingWeight()	const	noexcept { return provBuildingWeight; }
		double						getCurrTradeGoodWeight()		const	noexcept { return provTradeGoodWeight; }
		std::vector<double>		getProvProductionVec()			const	noexcept { return provProductionVec; }
		std::string						getTradeGoods()					const noexcept { return tradeGoods; }

		void						setCOT(bool isCOT)	noexcept				{ centerOfTrade = isCOT; };
	private:
		void	checkBuilding(const wiz::load_data::UserType* provinceObj, const std::string& building);
		void	buildPopRatios();
		void	decayPopRatios(date olddate, date newdate, EU3PopRatio& currentPop);

		std::vector<double>	getProvBuildingWeight()	const;
		double			getTradeGoodWeight()		const;
		double			getTradeGoodPrice()		const;

		int									num;
		double								baseTax;
		double								totalWeight;
		std::string								ownerString;
		std::string								provName;
		EU3Country*							owner;
		std::vector<std::string>						cores;
		int									population;
		bool									colony;
		bool									centerOfTrade;
		std::vector< std::pair<date, std::string> >	ownershipHistory;
		std::map<std::string, date>					lastPossessedDate;
		std::vector< std::pair<date, std::string> >	religionHistory;
		std::vector< std::pair<date, std::string> >	cultureHistory;
		std::vector<EU3PopRatio>				popRatios;
		std::map<std::string, bool>					buildings;
		double								manpower;
		std::string								tradeGoods;
		int									numV2Provs;

		// province attributes for weights
		double								provTaxIncome;
		double								provProdIncome;
		double								provMPWeight;
		double								provBuildingWeight;
		double								provTradeGoodWeight;

		std::vector<double>					provProductionVec;
};


#endif // EU3PROVINCE_H_