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

// 2018.10.25 SOUTH KOREA (vztpv@naver.com)

#ifndef EU3RELATIONS_H_
#define EU3RELATIONS_H_


#include "../Date.h"
#include <string>

#include "wiz/load_data_types.h"

class EU3Relations
{
	public:
		EU3Relations(const wiz::load_data::UserType* obj);
		std::string	getCountry() const noexcept { return tag; };
		int		getRelations() const noexcept { return value; };
		bool	hasMilitaryAccess() const noexcept { return military_access; };
		date	getDiplomatLastSent() const noexcept { return last_send_diplomat; };
		date	getLastWar() const noexcept { return last_war; };
	private:
		std::string	tag;
		int		value;
		bool	military_access;
		date	last_send_diplomat;
		date	last_war;
};

#endif