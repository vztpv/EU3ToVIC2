﻿/*Copyright (c) 2014 The Paradox Game Converters Project

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


#ifndef V2FACTORY_H_
#define V2FACTORY_H_



#include "V2Inventions.h"
#include <deque>
#include <vector>
#include <map>


#include "wiz/load_data_types.h"


struct V2FactoryType
{
	V2FactoryType(const wiz::load_data::UserType* factory);

	std::string						name;
	bool							requireCoastal;
	std::string						requireTech;
	vanillaInventionType		vanillaRequiredInvention;
	HODInventionType			HODRequiredInvention;
	HODNNMInventionType		HODNNMRequiredInvention;
	bool							requireLocalInput;
	std::map<std::string,float>			inputs;
	std::string						outputGoods;
};


class V2Factory
{
	public:
		V2Factory(const V2FactoryType* _type) : type(_type) { level = 1; };
		void					output(FILE* output) const;
		std::map<std::string,float>	getRequiredRGO() const;
		void					increaseLevel();

		bool						requiresCoastal()					const noexcept { return type->requireCoastal; }
		std::string						getRequiredTech()					const noexcept { return type->requireTech; }
		vanillaInventionType	getVanillaRequiredInvention()	const noexcept { return type->vanillaRequiredInvention; }
		HODInventionType		getHODRequiredInvention()		const noexcept { return type->HODRequiredInvention; }
		HODNNMInventionType	getHODNNMRequiredInvention()	const noexcept { return type->HODNNMRequiredInvention; }
		std::string						getTypeName()						const noexcept { return type->name; }
		std::map<std::string,float>		getInputs()							const noexcept { return type->inputs; };
		std::string					getOutputGoods()					const noexcept { return type->outputGoods; };
	private:
		const V2FactoryType* type;
		int						level;
};


class V2FactoryFactory
{
	public:
		V2FactoryFactory();
		std::deque<V2Factory*>	buildFactories() const;
	private:
		void					loadRequiredTechs(const std::string& filename);
		void					loadRequiredInventions(const std::string& filename);
		std::vector<std::pair<V2FactoryType*, int>>	factoryCounts;
		std::map<std::string, V2FactoryType*>			factoryTypes;
		std::map<std::string, std::string>						factoryTechReqs;
		std::map<std::string, std::string>						factoryInventionReqs;
};



#endif // V2FACTORY_H_