#pragma once
#include "stdafx.h"

// class contains settings for consiguration of app
class AppSettings {

	// what to do when starting:
		// open new file
		// start empty
		// continue from last file
	int startUpOption = 1;
	// last file opened
	std::string lastFile = "";

	// whether to save backup of project
	bool saveBackup = true;

	void save(std::ofstream *out);
	void load(std::ifstream *in);

public:
	// vector of language file addresses that the application loads
	std::vector<std::string> languageFileAddresses;
	
	void addLanguage(std::string fileLoc, bool echo = true);

	AppSettings();
	AppSettings(std::string fileName);
	~AppSettings();

	int getStartUpOption();
	void setStartUpOption(int newVal);

	std::string getLastFile();
	void setLastFile(std::string str);

	bool getSaveBackup();
	void setSaveBackup(bool newVal);

};

extern AppSettings * settings;
