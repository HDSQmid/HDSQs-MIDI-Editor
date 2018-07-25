// MIDI Editor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "console_io_handler.h"
#include "messageSend.h"
#include "files.h"
#include "Debug.h"
#include "settings.h"
#include "multiLingual.h"

void initialise();

int main()
{
	// for debugging
	// printVariableSizes();
	try {
		//initialise proram
		initialise();
	}
	catch (std::exception &e) {
		// set colour to red
		HANDLE hConsole;
		int colour = 4;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, colour);

		std::cout << "A critical error occurred when attempting to lauch the application." << std::endl;
		std::cout << "Error Code: " << e.what() << std::endl;
		system("PAUSE");
		exit(0);
	}
	catch (...) {
		// set colour to red
		HANDLE hConsole;
		int colour = 4;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, colour);

		std::cout << "A critical error occurred when attempting to lauch the application." << std::endl;
		system("PAUSE");
		exit(0);
	}

	// send launch message
	sendGreeting();



	try {
		while (true) {
			std::string in;
			std::getline(std::cin, in);

			handleConsoleInput(in);
		}
	}

	catch (std::exception &e) {

		sendMessage(STRING_CRITICAL_ERROR_CRASH, (std::string)"\nError Code: " + e.what(), MESSAGE_TYPE_CRITICAL_ERROR);

		if (fileIsOpen()) {
			
			sendMessage(STRING_CRITICAL_ERROR_SAVE, "", MESSAGE_TYPE_MESSAGE);
			currentFile->saveAs("backup" SAVE_FILE_EXTENSION);
		}
		system("PAUSE");
		exit(1);
	}

	catch (...) {
		

		sendMessage(STRING_CRITICAL_ERROR_CRASH, "", MESSAGE_TYPE_CRITICAL_ERROR);

		if (fileIsOpen()) {
			sendMessage(STRING_CRITICAL_ERROR_SAVE, "", MESSAGE_TYPE_MESSAGE);
			currentFile->saveAs("backup" SAVE_FILE_EXTENSION);
		}
		system("PAUSE");
		exit(1);
	}

    return 0;
}

void initialise()
{

	// initialise settings object
	settings = new AppSettings;

	// manually refresh languages
	refreshLanguages();

	// open backup if backup exists from crash
	// backup.hqp
	// skip what to start with


	// determine what to start with
	switch (settings->getStartUpOption())
	{
	case 0: // start empty
		break;
	case 1: // start with new file
		currentFile = new midiFile; 
		break;
	case 2:
		currentFile = new midiFile(settings->getLastFile());
		break;
	default:
		break;
	}

	
	// eventually check user settings

	

}
