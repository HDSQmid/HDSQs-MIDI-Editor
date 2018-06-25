#pragma once
#include "stdafx.h"


class language {

	std::map<int, std::string> strs;

	void addTranslation(int ID, std::string translation);
	
public:

	std::string languageName;

	std::string translate(int ID); // returns string translation of provided integer

	int reverseTranslate(std::string translation); // returns integer value of provided string

	language(std::string fileAddress);

	

};

std::string translate(int ID);

int reverseTranslate(std::string translation);

extern language defaultLn;
