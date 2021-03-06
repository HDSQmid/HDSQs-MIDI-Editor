// MIDI Editor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "console_io_handler.h"
#include "messageSend.h"
#include "files.h"
#include "Debug.h"
#include "settings.h"
#include "multiLingual.h"

std::string programLocation;

void handleStartupArgument(std::string arg);

void initialise(int nNumberofArgs, char*pszArgs[]);

void quit();


int main(int nNumberofArgs, char*pszArgs[])
{
	// set console window title
	updateWindowTitle();

	// for debugging
	// printVariableSizes();
	// printStdVarSizes();


	try {
		//initialise proram
		initialise(nNumberofArgs, pszArgs);
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

	// main section of application
	try {

		while (true) {
			std::string in;
			std::getline(std::cin, in);

			handleConsoleInput(in);
		}
	}

	catch (std::exception &e) {
		//reenable output
		setOutputEcho(true);
		sendMessage(STRING_CRITICAL_ERROR_CRASH, (std::string)"\n" + translate(STRING_ERROR_CODE) + (std::string) ": " + e.what(), MESSAGE_TYPE_CRITICAL_ERROR);

		if (fileIsOpen()) {
			
			sendMessage(STRING_CRITICAL_ERROR_SAVE, "", MESSAGE_TYPE_MESSAGE);
			currentFile->saveAs("backup" SAVE_FILE_EXTENSION);
		}
		system("PAUSE");
		exit(1);
	}

	catch (...) {
		//reenable output
		setOutputEcho(true);
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

void handleStartupArgument(std::string arg)
{
	// reset settings
	if (arg == "/reset")
	{
		// delete config file
		return;
	}
	
}

void initialise(int nNumberofArgs, char*pszArgs[])
{
	// disable console output
	setOutputEcho(false);

	// use arguments
	programLocation = (std::string) pszArgs[0];

	std::string fileToOpen = "";

	for (int i = 1; i < nNumberofArgs; i++) {

		if (pszArgs[i][0] == '/') handleStartupArgument(pszArgs[i]);
		else
		{
			// check if string is a file before this
			fileToOpen = pszArgs[i];
			break;
		}

	}
	
	// initialise settings object
	try {
		settings = new AppSettings(APP_SETTINGS_FILE_NAME);
	}
	catch (...) {

		settings = new AppSettings;

	}


	// manual refresh of languages must be called to load languages
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

	// reenable output
	setOutputEcho(true);

}



