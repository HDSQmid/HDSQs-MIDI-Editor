#include "stdafx.h"
#include "multiLingual.h"
#include "messageSend.h"
#include "settings.h"

void language::addTranslation(int ID, std::string translation)
{
	translation = translation.substr(1); // remove space from start of string
	strs.insert(std::pair<int, std::string>(ID, translation));
}

std::string language::translate(int ID)
{
	return strs[ID];
}



language::language(std::string fileName)
{
	std::string fileAddress = ".\\Lang\\" + fileName;

		// attempt to import file
		std::ifstream input;
		  // import file
		input.open(fileAddress, std::ios::in);
		if (input.is_open()) {

			std::string in;
			int id;
			std::string value;
			std::getline(input, in); // get line from file
			languageName = in; // set first line as name of language

			while (!input.eof()) {

				std::getline(input, in); // get line from file
				if (in == "") continue; // if line is blank skip that line
				std::stringstream iss(in); // create stringstream
				iss >> id; // get id as first word of stringstream
				std::stringstream oss;
				oss << iss.rdbuf(); // transfer buffer to other stringstream
				std::string value = oss.str(); // set remainder of string as final value of translation

				//add some error handling here

				addTranslation(id, value); // add to map of translations

			}
			input.close();
		}

		else {

			throw std::exception("Failed to open file");

		}

	


}

std::vector<language> langs;

std::string translate(int ID)
{
	std::string str;
	for (auto & testLang : langs) {
		str = testLang.translate(ID);
		if (str != "") return str;
	}
	
	if (ID == MESSAGE_NO_TRANSLATION_FOUND) // no translation found for the no translation found message
	{
		throw std::exception("Bad Language File", ERROR_CODE_BAD_LANGUAGE);
	}

	if (str == "") str = translate(MESSAGE_NO_TRANSLATION_FOUND); // this could cause unending loop if no translation is found for this error

	return str;
}

int reverseTranslate(std::string translation)
{
	return 0;
}

void refreshLanguages()
{

	// if settings object doesnt exist, return
	if (settings == NULL) return;
	// languages will need to be manually refreshed later

	langs.clear();
	if (settings->languageFileAddresses.size()) {
		std::string fileAddress; // file address of current language being accessed
		for (int i = 0; i < settings->languageFileAddresses.size(); i++) {
			fileAddress = settings->languageFileAddresses[i];
			try{
				langs.push_back(language(fileAddress));
			}
			catch (std::exception &e) {

				std::cout << "An error ocurred while attempting to read the language file: " << fileAddress << std::endl;
				std::cout << "Error: " << e.what() << std::endl;
				
			}

			catch (...) {

				std::cout << "An error ocurred while attempting to read the language file: " << fileAddress << std::endl;
				
			}
		}
	}
}


