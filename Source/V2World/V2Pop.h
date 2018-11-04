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

// 2018.11.04 SOUTH KOREA (vztpv@naver.com)


#ifndef V2POP_H_
#define V2POP_H_



#include <string>
#include <vector>


class V2Pop
{
	public:
		V2Pop(const std::string& type, int size, const std::string& culture, const std::string& religion);
		void output(FILE*) const;
		bool combine(const V2Pop& rhs);

		void	changeSize(int delta)				noexcept	{ size += delta; }
		void	incrementSupportedRegimentCount() noexcept { supportedRegiments++; }
		void	setCulture(std::string _culture)		noexcept { culture = _culture; }
		void	setReligion(std::string _religion)		noexcept { religion = _religion; }

		int		getSize()							const	noexcept { return size; }
		std::string	getType()							const	noexcept { return type; }
		std::string	getCulture()						const	noexcept { return culture; }
		std::string	getReligion()						const	noexcept { return religion; }
		int		getSupportedRegimentCount()	const noexcept { return supportedRegiments; }
	private:
		std::string	type;
		int		size;
		std::string	culture;
		std::string	religion;
		int		supportedRegiments;
};


int getNextPopId(); // ?



#endif