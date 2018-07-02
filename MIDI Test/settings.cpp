#include "stdafx.h"
#include "settings.h"
#include "multiLingual.h"
#include "messageSend.h"

void AppSettings::addLanguage(std::string fileLoc, bool echo)
{
	
	languageFileAddresses.insert(languageFileAddresses.begin(), fileLoc);
	refreshLanguages();
	if (echo) sendMessage(MESSAGE_ADDED_LANGUAGE);

	// todo: if language adding fails, remove the language from the list

}

AppSettings::AppSettings()
{
	// load the application's settings from the disk
	// for now just add english as the default language
	addLanguage("en.lang", false);
}

AppSettings settings;
