#include "stdafx.h"
#include "settings.h"
#include "multiLingual.h"
#include "messageSend.h"

void AppSettings::addLanguage(std::string fileLoc, bool echo)
{
	
	languageFileAddresses.push_back(fileLoc);
	refreshLanguages(); // this function accesses the settings object. 
						// The settings object must be initialised first
	if (echo) sendMessage(MESSAGE_ADDED_LANGUAGE);

	// todo: if language adding fails, remove the language from the list

}

AppSettings::AppSettings()
{
	// load the application's settings from the disk
	// for now just add english as the default language
	addLanguage("en.lang", false);
}

int AppSettings::getStartUpOption()
{
	return startUpOption;
}

void AppSettings::setStartUpOption(int newVal)
{
	switch (newVal) {

	case 0: // start empty
		startUpOption = newVal;
		break;
	case 1: // start with new file
		startUpOption = newVal;
		break;
	case 2: // start with most recent file
		startUpOption = newVal;
		break;
	default:
		break;

	}

	return;

}

std::string AppSettings::getLastFile()
{
	return lastFile;
}

void AppSettings::setLastFile(std::string str)
{
	lastFile = str;
}

AppSettings * settings;
