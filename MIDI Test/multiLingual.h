#pragma once
#include "stdafx.h"

typedef std::map<int, std::string> TStrStrMap;
typedef std::pair<int, std::string> TStrStrPair;

class language {

	TStrStrMap strs;

	void addTranslation(int ID, std::string translation);
	
public:

	std::string getTranslation(int ID); // returns translation of provided string

	void importLang(std::string fileName);

};


