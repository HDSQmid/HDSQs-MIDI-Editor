#pragma once
#include "stdafx.h"

// class contains settings for consiguration of app
class AppSettings {
	// vector of language files that the application loads
	std::vector<std::string> languageFileAddresses;
	
	void addLanguage(std::string fileLoc);

};