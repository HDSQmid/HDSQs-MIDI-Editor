#pragma once
#include "stdafx.h"

// class contains settings for consiguration of app
class AppSettings {
public:
	// vector of language files that the application loads
	std::vector<std::string> languageFileAddresses;
	
	void addLanguage(std::string fileLoc, bool echo = true);

	AppSettings();

};

extern AppSettings settings;
