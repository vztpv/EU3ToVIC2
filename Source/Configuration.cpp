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

// 2018.10.24 SOUTH KOREA (vztpv@naver.com)

#include "Configuration.h"

// remove - #include "Parsers/Parser.h"
#include "wiz/load_data.h"
#include "wiz/load_data_types.h"

#include "Log.h"

Configuration* Configuration::instance = nullptr;

Configuration::Configuration()
{
	LOG(LogLevel::Info) << "Reading configuration file.";

	wiz::load_data::UserType tempObj;
	
	bool ok = wiz::load_data::LoadData::LoadDataFromFile3("configuration.txt", tempObj, -1, 0); // use maybe total thread in cpu
		// doParseFile("configuration.txt");	// the parsed configuration file

	if (!ok)
	{
		LOG(LogLevel::Error) << "Could not parse file configuration.txt";
		exit(-1);
	}
	std::vector<wiz::load_data::UserType*> obj = tempObj.GetUserTypeItem("configuration");	// the configuration section

	if (obj.size() != 1)
	{
		LOG(LogLevel::Error) << "Configuration file must contain exactly one configuration section.";
		exit (-1);
	}

	MaxLiteracy			= obj[0]->GetItem("max_literacy")[0].Get(0).ToFloat();
	resetProvinces		= obj[0]->GetItem("resetProvinces")[0].Get(0).ToString();
	V2Path				= obj[0]->GetItem("v2directory")[0].Get(0).ToString();
	V2DocumentsPath		= obj[0]->GetItem("V2Documentsdirectory")[0].Get(0).ToString();
	EU3Path				= obj[0]->GetItem("EU3directory")[0].Get(0).ToString();
	EU3gametype			= obj[0]->GetItem("EU3gametype")[0].Get(0).ToString();
	V2Gametype			= obj[0]->GetItem("V2gametype")[0].Get(0).ToString();
	EU3Mod				= obj[0]->GetItem("EU3Mod")[0].Get(0).ToString();
	Removetype			= obj[0]->GetItem("removetype")[0].Get(0).ToString();
	convertPopTotals	= (obj[0]->GetItem("convertPopTotals")[0].Get(0).ToString() == "yes");
	outputName			= "";
}