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

#ifndef V2Province_H_
#define V2Province_H_



#include "../EU3World/EU3World.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <set>

class V2Province;
class V2Factory;
class EU3World;



class V2State
{
	public:
		V2State(int newId, V2Province* firstProvince);

		void		addRailroads();
		void		addFactory(V2Factory* factory);

		bool		isCoastal() const;
		bool		hasLocalSupply(const std::string& product) const;
		double	getSuppliedInputs(const V2Factory* factory)	const;
		bool		provInState(int id) const;
		bool		hasLandConnection()	const;
		double	getManuRatio() const;

		void		addProvince(V2Province* newProvince)	{ provinces.push_back(newProvince); };
		void		setColonial(bool isIt)						{ colonial = isIt; };

		bool						isColonial()		const noexcept { return colonial; };
		int						getFactoryCount()	const noexcept { return factories.size(); };
		int						getID()				const noexcept { return id; };
		std::vector<V2Province*>	getProvinces()		const noexcept { return provinces; };
	private:
		bool	hasCOT();
		int								id;
		bool								colonial;
		std::vector<V2Province*>			provinces;
		std::vector<const V2Factory*>	factories;
};


#endif	// V2Province_H_