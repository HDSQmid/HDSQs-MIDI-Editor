#include "stdafx.h"
#include "multiLingual.h"
#include "messageSend.h"

void language::addTranslation(int ID, std::string translation)
{
	strs.insert(std::pair<int, std::string>(ID, translation));
}

std::string language::translate(int ID)
{
	return strs[ID];
}



language::language(std::string fileName)
{
	std::string fileAddress = ".\\Lang\\" + fileName;

	try { // attempt to import file
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
				std::stringstream iss(in); // create stringstream
				iss >> id; // get id as first word of stringstream
				std::stringstream oss;
				oss << iss.rdbuf(); // transfer buffer to other stringstream
				std::string value = oss.str(); // set remainder of string as final value of translation

				//add some error handling here

				addTranslation(id, value); // add to map of translations

			}

		}


	}

	catch (...) {

		std::cout << "An error ocurred while attempting to read the language file: " << fileAddress << std::endl;

	}
}

std::string translate(int ID)
{
	return defaultLn.translate(ID);
}

int reverseTranslate(std::string translation)
{
	return 0;
}

language defaultLn("en.lang");

