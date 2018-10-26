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


#ifndef MAPPER_H
#define MAPPER_H


#include <map>
#include <set>
#include <vector>
#include <unordered_set>


#include "wiz/load_data_types.h"

class V2World;
class EU3World;
enum WorldType;



// Province Mappings
typedef std::map< int, std::vector<int> >	provinceMapping;			// < destProvince, sourceProvinces >
typedef std::map< int, std::vector<int> >	inverseProvinceMapping;	// < sourceProvince, destProvinces >
typedef std::unordered_set<int>			resettableMap;

void initProvinceMap(const wiz::load_data::UserType* obj, WorldType worldType, provinceMapping& provinceMap, inverseProvinceMapping& inverseProvinceMap, resettableMap& resettableProvinces);
const std::vector<int>& getV2ProvinceNums(const inverseProvinceMapping& invProvMap, int eu3ProvinceNum);

typedef std::vector< std::vector<int> > adjacencyMapping;
adjacencyMapping initAdjacencyMap();


typedef std::map<int, std::string>	continentMapping;	// <province, continent>
void initContinentMap(const wiz::load_data::UserType* obj, continentMapping& continentMap);


void mergeNations(EU3World&, const wiz::load_data::UserType* mergeObj);
void uniteJapan(EU3World&);
void removeEmptyNations(EU3World&);
void removeDeadLandlessNations(EU3World&);
void removeLandlessNations(EU3World&);


// State Mappings
typedef std::map< int, std::vector<int> >	stateMapping;	// < province, all other provinces in state >
typedef std::map< int, int >				stateIndexMapping; // < province, state index >
void initStateMap(const wiz::load_data::UserType* obj, stateMapping& stateMap, stateIndexMapping& stateIndexMap);


// Culture Mappings
enum distinguisherType
{
	DTOwner,
	DTReligion,
	DTRegion
};
typedef std::pair<distinguisherType, std::string> distinguisher;
typedef struct {
	std::string srcCulture;
	std::string dstCulture;
	std::vector<distinguisher> distinguishers;
} cultureStruct;
typedef std::vector<cultureStruct> cultureMapping;
cultureMapping initCultureMap(const wiz::load_data::UserType* obj);


// Religion Mappings
typedef std::map<std::string, std::string> religionMapping;		// <srcReligion, destReligion>
religionMapping initReligionMap(const wiz::load_data::UserType* obj);


// Union Mappings
typedef std::vector< std::pair<std::string, std::string> > unionMapping;	// <cultures, tag>
unionMapping initUnionMap(const wiz::load_data::UserType* obj);


// Government Mappings
typedef std::map<std::string, std::string> governmentMapping;	// <srcGov, dstGov>
governmentMapping initGovernmentMap(const wiz::load_data::UserType* obj);


// Cultural Union Nation mappings
typedef std::map< std::string, std::vector<std::string> > unionCulturesMap;	// <culture group, cultures>
typedef std::map< std::string, std::string > inverseUnionCulturesMap;	// <culture, culture group>
void initUnionCultures(const wiz::load_data::UserType* obj, unionCulturesMap& unionCultures, inverseUnionCulturesMap& inverseUnionCultures);


// EU4 regions
typedef std::map<int, std::set<std::string>>	EU3RegionsMapping;		// the regions in EU3
void initEU3RegionMap(const wiz::load_data::UserType *obj, EU3RegionsMapping& regions);


// utility functions
std::string CardinalToOrdinal(int cardinal);


#endif // MAPPER_H
