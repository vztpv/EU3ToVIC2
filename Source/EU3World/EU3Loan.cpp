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

#include "EU3Loan.h"

#include <vector>


EU3Loan::EU3Loan(wiz::load_data::UserType* obj)
{
	std::vector<wiz::load_data::ItemType<wiz::DataType>> moneyObj = obj->GetItem("lender");
	if (moneyObj.size() > 0)
	{
		lender = moneyObj[0].Get(0).ToString();
	}
	else
	{
		lender = "";
	}
	moneyObj = obj->GetItem("interest");
	if (moneyObj.size() > 0)
	{
		interest = moneyObj[0].Get(0).ToFloat();
	}
	else
	{
		interest = 0.0;
	}
	moneyObj = obj->GetItem("amount");
	if (moneyObj.size() > 0)
	{
		amount = moneyObj[0].Get(0).ToFloat();
	}
	else
	{
		amount = 0.0;
	}
}