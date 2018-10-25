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

// 2018.10.23 SOUTH KOREA (vztpv@naver.com)

#ifndef EU3LEADER_H_
#define EU3LEADER_H_


#include "wiz/load_data_types.h"
#include "../date.h"


class EU3Leader
{
public:
	EU3Leader(const wiz::load_data::UserType* obj);
	std::string	getName() const noexcept { return name; };
	int		getFire() const noexcept { return fire; };
	int		getShock() const noexcept { return shock; };
	int		getManuever() const noexcept { return manuever; };
	int		getSiege() const noexcept { return siege; };
	int		getID() const noexcept { return id; };
	bool	isLand() const noexcept;
	date	getActivationDate() const noexcept { return activationDate; }
private:
	std::string	name;
	int		fire;
	int		shock;
	int		manuever;
	int		siege;
	int		id;
	std::string	type;
	date	activationDate;
};


#endif // EU3LEADER_H_