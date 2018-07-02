// MIDI Editor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "console_io_handler.h"
#include "messageSend.h"
#include "files.h"

void initialise();

int main()
{
	// send launch message
	sendGreeting();


	//import settings

	//check for backup files

	//initialise proram
	initialise();

	try {
		while (true) {
			std::string in;
			std::getline(std::cin, in);

			handleConsoleInput(in);
		}
	}

	catch (std::exception &e) {

		sendMessage(STRING_CRITICAL_ERROR_CRASH, (std::string)"\nError: " + e.what(), MESSAGE_TYPE_CRITICAL_ERROR);

		if (fileIsOpen()) {
			
			sendMessage(STRING_CRITICAL_ERROR_SAVE, "", MESSAGE_TYPE_CRITICAL_ERROR);
			currentFile->saveAs("backup" SAVE_FILE_EXTENSION);
		}
		system("PAUSE");
		exit(1);
	}

	catch (...) {
		

		sendMessage(STRING_CRITICAL_ERROR_CRASH, "", MESSAGE_TYPE_CRITICAL_ERROR);

		if (fileIsOpen()) {
			sendMessage(STRING_CRITICAL_ERROR_SAVE, "", MESSAGE_TYPE_CRITICAL_ERROR);
			currentFile->saveAs("backup" SAVE_FILE_EXTENSION);
		}
		system("PAUSE");
		exit(1);
	}

    return 0;
}

void initialise()
{
	currentFile = new midiFile; // create new file
	// eventually check user settings


}
