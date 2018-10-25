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

#ifndef EU3DIPLOMACY_H_
#define EU3DIPLOMACY_H_


#include "../Date.h"
#include <vector>

#include "wiz/load_data_types.h"



struct EU3Agreement
{
	EU3Agreement(const wiz::load_data::UserType* obj);

	std::string	type;
	std::string	country1;
	std::string	country2;
	date		startDate;
};


class EU3Diplomacy
{
	public:
		EU3Diplomacy();
		EU3Diplomacy(const wiz::load_data::UserType* obj);
		std::vector<EU3Agreement>	getAgreements() const noexcept { return agreements; };
	private:
		std::vector<EU3Agreement>	agreements;
};

#endif