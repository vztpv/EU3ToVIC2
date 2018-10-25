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

// 2018.10.24 SOUTH KOREA (vztpv@naver.com) // todo - const? noexcept?

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_


#include <string>
#include "Date.h"



class Configuration // Singleton
{
	public:
		Configuration();

		static date		getFirstEU3Date()							{ return getInstance()->firstEU3Date; }
		static void		setFirstEU3Date(date _firstDate)		{ getInstance()->firstEU3Date = _firstDate; }
		static date		getLastEU3Date()							{ return getInstance()->lastEU3Date; }
		static void		setLastEU3Date(date _lastDate)		{ getInstance()->lastEU3Date = _lastDate;	}
		static std::string	getResetProvinces()						{ return getInstance()->resetProvinces; }
		static double	getMaxLiteracy()							{ return getInstance()->MaxLiteracy; }
		static std::string	getV2Path()									{ return getInstance()->V2Path; }
		static std::string	getEU3Path()								{ return getInstance()->EU3Path; }
		static std::string	getEU3Mod()									{ return getInstance()->EU3Mod; }
		static std::string	getV2DocumentsPath()						{ return getInstance()->V2DocumentsPath; }
		static std::string	getEU3Gametype()							{ return getInstance()->EU3gametype; }
		static std::string	getV2Gametype()							{ return getInstance()->V2Gametype; }
		static std::string	getRemovetype()							{ return getInstance()->Removetype; }
		static std::string	getOutputName()							{ return getInstance()->outputName; }
		static bool		getConvertPopTotals()						{ return getInstance()->convertPopTotals; }
		static void		setOutputName(std::string _outputName)	{ getInstance()->outputName = _outputName; }

		static Configuration* getInstance()
		{
			if (instance == nullptr)
			{
				instance = new Configuration();
			}
			return instance;
		}

	private:
		static Configuration* instance;

		// options from configuration.txt
		std::string	EU3Path;					// the install directory for EU3
		std::string	EU3Mod;					// the name of the EU3 mod to use for conversion
		std::string	V2Path;					// the install directory for V2
		std::string	V2DocumentsPath;		// V2's directory under My Documents
		std::string	V2Gametype;				// whether V2 is vanilla, AHD, or HoD
		std::string	resetProvinces;		// whether or not to reset allowed provinces back to V2 defaults
		double	MaxLiteracy;			// the maximum literacy allowed
		std::string	Removetype;				// the rule to use for removing excess EU3 nations
		bool	convertPopTotals;		// whether or not to convert pop totals

		// items set during conversion
		date	firstEU3Date;
		date	lastEU3Date;			// the date EU3 ended
		std::string	EU3gametype;
		std::string	outputName;
};

#endif // CONFIGURATION_H_