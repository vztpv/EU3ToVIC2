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

#include "EU3Leader.h"
#include "../Log.h"


EU3Leader::EU3Leader(const wiz::load_data::UserType *obj)
{
	{
		std::vector<wiz::load_data::UserType*> subObj = obj->GetUserTypeItem("name");
		if (subObj.size() > 0)
		{
			name = subObj[0]->GetName().ToString();
		}
		else
		{
			name = "";
		}
	}
	{
		std::vector<wiz::load_data::ItemType<wiz::DataType>> subObj = obj->GetItem("manuever");
		if (subObj.size() > 0)
		{
			manuever = subObj[0].Get(0).ToInt();
		}
		else
		{
			manuever = 0;
		}
		subObj = obj->GetItem("fire");
		if (subObj.size() > 0)
		{
			fire = subObj[0].Get(0).ToInt();
		}
		else
		{
			fire = 0;
		}
		subObj = obj->GetItem("shock");
		if (subObj.size() > 0)
		{
			shock = subObj[0].Get(0).ToInt();
		}
		else
		{
			shock = 0;
		}
		subObj = obj->GetItem("siege");
		if (subObj.size() > 0)
		{
			siege = subObj[0].Get(0).ToInt();
		}
		else
		{
			siege = 0;
		}
		subObj = obj->GetItem("id");
		if (subObj.size() > 0)
		{
			// duplicate? // subObj = subObj[0]->getValue("id");
			id = subObj[0].Get(0).ToInt();
		}
		else
		{
			id = 0;
		}
		subObj = obj->GetItem("type");
		if (subObj.size() > 0)
		{
			type = subObj[0].Get(0).ToString();
		}
		else
		{
			type = "";
		}
		subObj = obj->GetItem("activation");
		if (subObj.size() > 0)
		{
			activationDate = date(subObj[0].Get(0).ToString());
		}
		else
		{
			activationDate = date();
		}
	}
}


bool EU3Leader::isLand() const noexcept
{
	if (type == "general" || type == "conquistador")
		return true;
	else if (type == "explorer" || type == "admiral")
		return false;
	else
	{
		LOG(LogLevel::Warning) << "Unknown leader type " << type;
	}
	return false;
}

