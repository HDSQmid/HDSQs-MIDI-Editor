#include "multiLingual.h"
#include "messageSend.h"

void language::addTranslation(int ID, std::string translation)
{
	strs.insert(TStrStrPair(ID, translation));
}

std::string language::getTranslation(int ID)
{
	return strs[ID];
}

void language::importLang(std::string fileName)
{
	try { // attempt to import file

		// import file


	}

	catch (...) {

		sendMessage(MESSAGE_CANT_READ_LANG_FILE, ERROR);

	}

}
