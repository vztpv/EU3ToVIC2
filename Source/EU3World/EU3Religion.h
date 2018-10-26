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


// 2018.10.26 SOUTH KOREA (vztpv@naver.com)


#ifndef EU3RELIGION_H_
#define EU3RELIGION_H_

#include <string>
#include <map>

#include "wiz/load_data_types.h"

class EU3Religion
{
public:
	EU3Religion(wiz::load_data::UserType*, const std::string& group);

	// exactly one of these four functions should return true for any given pairing
	bool isSameReligion(const EU3Religion* other) const;	// e.g. catholic <-> catholic
	bool isRelatedTo(const EU3Religion* other) const;		// e.g. orthodox <-> catholic
	bool isInfidelTo(const EU3Religion* other) const;		// e.g. sunni <-> catholic

	std::string getName() const noexcept { return name; }
	std::string getGroup() const noexcept { return group; }

	static void parseReligions(wiz::load_data::UserType* obj);
	static EU3Religion* getReligion(const std::string& name);

	static std::map<std::string, EU3Religion*> getAllReligions() noexcept { return all_religions; }

private:
	std::string name;
	std::string group;

	static std::map<std::string, EU3Religion*> all_religions;
};

#endif // EU3RELIGION_H_