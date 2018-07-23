#pragma once
#include "stdafx.h"

// class contains settings for consiguration of app
class AppSettings {


	int startUpOption = 1;
	std::string lastFile = "";

public:
	// vector of language file addresses that the application loads
	std::vector<std::string> languageFileAddresses;
	
	void addLanguage(std::string fileLoc, bool echo = true);

	AppSettings();

	int getStartUpOption();
	void setStartUpOption(int newVal);

	std::string getLastFile();
	void setLastFile(std::string str);

};

extern AppSettings settings;
