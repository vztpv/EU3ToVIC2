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

#ifndef V2_TECH_SCHOOLS
#define V2_TECH_SCHOOLS



#include <string>
#include <vector>


#include "wiz/load_data_types.h"



typedef struct V2TechSchool
{
	std::string name;
	double armyInvestment;
	double commerceInvestment;
	double cultureInvestment;
	double industryInvestment;
	double navyInvestment;
} techSchool;


std::vector<V2TechSchool>	initTechSchools(const wiz::load_data::UserType *obj, const std::vector<std::string>& blockedTechSchools);
std::vector<std::string>			initBlockedTechSchools(const wiz::load_data::UserType*);



#endif // V2_TECH_SCHOOLS