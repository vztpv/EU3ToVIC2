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


// 2018.11.04 SOUTH KOREA (vztpv@naver.com)


#include "V2Party.h"

#include "..\Log.h"



V2Party::V2Party(const wiz::load_data::UserType* party_obj)
{
	name = party_obj->GetItem("name")[0].Get(0).ToString();
	ideology = party_obj->GetItem("ideology")[0].Get(0).ToString();

	start_date = date(party_obj->GetItem("start_date")[0].Get(0).ToString());
	end_date = date(party_obj->GetItem("end_date")[0].Get(0).ToString());

	economic_policy = party_obj->GetItem("economic_policy")[0].Get(0).ToString();
	trade_policy = party_obj->GetItem("trade_policy")[0].Get(0).ToString();
	religious_policy = party_obj->GetItem("religious_policy")[0].Get(0).ToString();
	citizenship_policy = party_obj->GetItem("citizenship_policy")[0].Get(0).ToString();
	war_policy = party_obj->GetItem("war_policy")[0].Get(0).ToString();
}


V2Party::V2Party(const std::string& name, const std::string& ideology)
: name(name), ideology(ideology)
{
	if (ideology == "conservative")
	{
		start_date = date("1820.1.1");
		end_date = date("2000.1.1", false);
		economic_policy = "interventionism";
		trade_policy = "protectionism";
		religious_policy = "moralism";
		citizenship_policy = "limited_citizenship";
		war_policy = "pro_military";
	}
	else if (ideology == "liberal")
	{
		start_date = date("1820.1.1");
		end_date = date("2000.1.1", false);
		economic_policy = "laissez_faire";
		trade_policy = "free_trade";
		religious_policy = "pluralism";
		citizenship_policy = "limited_citizenship";
		war_policy = "anti_military";
	}
	else if (ideology == "reactionary")
	{
		start_date = date("1820.1.1");
		end_date = date("2000.1.1", false);
		economic_policy = "state_capitalism";
		trade_policy = "protectionism";
		religious_policy = "moralism";
		citizenship_policy = "residency";
		war_policy = "jingoism";
	}
	else if (ideology == "socialist")
	{
		start_date = date("1849.1.1", false);
		end_date = date("2000.1.1", false);
		economic_policy = "state_capitalism";
		trade_policy = "free_trade";
		religious_policy = "secularized";
		citizenship_policy = "full_citizenship";
		war_policy = "anti_military";
	}
	else if (ideology == "communist")
	{
		start_date = date("1849.1.1", false);
		end_date = date("2000.1.1", false);
		economic_policy = "planned_economy";
		trade_policy = "protectionism";
		religious_policy = "pro_atheism";
		citizenship_policy = "full_citizenship";
		war_policy = "pro_military";
	}
	else if (ideology == "anarcho_liberal")
	{
		start_date = date("1830.1.1");
		end_date = date("2000.1.1", false);
		economic_policy = "laissez_faire";
		trade_policy = "free_trade";
		religious_policy = "pro_atheism";
		citizenship_policy = "full_citizenship";
		war_policy = "pro_military";
	}
	else if (ideology == "fascist")
	{
		start_date = date("1905.1.1", false);
		end_date = date("2000.1.1", false);
		economic_policy = "state_capitalism";
		trade_policy = "protectionism";
		religious_policy = "moralism";
		citizenship_policy = "residency";
		war_policy = "jingoism";
	}
	else
	{
		LOG(LogLevel::Warning) << "Unknown party ideology \"" << ideology << "\" for party \"" << name << '"';
	}
}