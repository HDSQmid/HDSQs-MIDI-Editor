#include "stdafx.h"
#include "console_io_handler.h"
#include "messageSend.h"

#define NUM_HANDLERS 7
ConsoleQuit quit;
ConsoleHelp help;
ConsoleFileOpen openFile;
ConsoleFileClose closeFile;
ConsoleFileSave saveFile;
ConsoleFileSaveAs saveFileAs;
ConsoleCrash crash;

consoleInputHandler* input_handlers[NUM_HANDLERS] = { &help, &quit, &openFile, &closeFile, &saveFile, &saveFileAs, &crash };

void handleConsoleInput(std::string input)
{

	std::string test;
	std::istringstream iss{ input };
	iss >> test;

	std::ostringstream oss;
	oss << iss.rdbuf();

	std::string args = oss.str();
	if(args != "") args = args.substr(1);

	//remove command from rest of arguments for easier processing

	bool foundCall = false; // bool for whether a handler was found
	for (int i = 0; i < NUM_HANDLERS; i++) {
		if (input_handlers[i]->getIdentifier() == test) {
			input_handlers[i]->call(args);
			foundCall = 1;
			break;
		}
	}

	if (!foundCall) sendMessage("Didn't find a matching command", MESSAGE_ERROR);

}

/***************************************/


consoleInputHandler::consoleInputHandler()
{
	identifier = "NULL";
	description = "Does nothing";
	help = "You don't need it";
}

void consoleInputHandler::call(std::string args)
{

	std::cout << "Test" << std::endl;

}

std::string consoleInputHandler::getIdentifier()
{
	return identifier;
}

std::string consoleInputHandler::getDescription()
{
	return description;
}

std::string consoleInputHandler::getHelp()
{
	return help;
}

/***************************************/

ConsoleFileOpen::ConsoleFileOpen()
{
	identifier = "open";
	description = "opens a file";
	help = "arguments: fileName \nexample usage: open example.mid";
}

void ConsoleFileOpen::call(std::string args)
{
	if (args == "") {

		sendMessage("Expected a file name", MESSAGE_ERROR);
		return;

	}
	
	fileOpen(args);

	return;
}

ConsoleFileClose::ConsoleFileClose()
{
	identifier = "close";
	description = "closes the open file";
	help = "arguments: (none) \nexample usage: close";
}

void ConsoleFileClose::call(std::string args)
{
	if (currentFile == NULL) // if file is not open
	{
		sendMessage("There aren't any open files", MESSAGE_ERROR);
		return;

	}
	
	fileClose();
}

ConsoleFileSave::ConsoleFileSave()
{
	identifier = "save";
	description = "saves the open file";
	help = "arguments: (fileName - if saving as) \nexample usage: save \nexample usage: save example2.txt";
}

void ConsoleFileSave::call(std::string args)
{
	if (currentFile == NULL) // if file is not open
	{
		sendMessage("There aren't any open files", MESSAGE_ERROR);
		return;

	}

	if (args != "") currentFile->saveAs(args);

	else currentFile->save();
}

ConsoleFileSaveAs::ConsoleFileSaveAs()
{
	identifier = "saveas";
	description = "saves the open file under a new file name";
	help = "arguments: fileName \nexample usage: save example2.txt";
}

void ConsoleFileSaveAs::call(std::string args)
{
	if (currentFile == NULL) // if file is not open
	{
		sendMessage("There aren't any open files", MESSAGE_ERROR);
		return;

	}

	if (args == "") { // if no file name provided

		sendMessage("Expected a file name", MESSAGE_ERROR);
		return;

	}

	currentFile->saveAs(args);
}

ConsoleQuit::ConsoleQuit()
{
	identifier = "quit";
	description = "quits the program";
	help = "arguments: (none) \nexample usage: quit";
}

void ConsoleQuit::call(std::string args)
{
	exit(0);
}

ConsoleHelp::ConsoleHelp()
{
	identifier = "help";
	description = "provides help";
	help = "arguments: (argument) \nexample usage: help \nexample usage: help open";
}

void ConsoleHelp::call(std::string args)
{
	//set colour to green
	HANDLE hConsole;
	int colour = 2;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);

	//if no argument
	if (args == "") {
		

		std::cout << "Help:" << std::endl;
		for (int i = 0; i < NUM_HANDLERS; i++) {			
			std::cout << input_handlers[i]->getIdentifier() << ": "
				<< input_handlers[i]->getDescription() << std::endl;
		}
	}
	//if argument provided
	else {

		bool foundCall = false; // bool for whether a handler was found
		for (int i = 0; i < NUM_HANDLERS; i++) {
			if (input_handlers[i]->getIdentifier() == args) {
				std::cout << "help for " << input_handlers[i]->getIdentifier() << "\n" 
					<< input_handlers[i]->getDescription() << "\n" 
					<< input_handlers[i]->getHelp() << std::endl;
				foundCall = 1;
				break;
			}			
		}
		if (!foundCall) sendMessage("Didn't find a matching command", MESSAGE_ERROR);
	}

	SetConsoleTextAttribute(hConsole, 15);

}

ConsoleCrash::ConsoleCrash()
{
	identifier = "crash";
	description = "crashes the application";
	help = "arguments: (none) \nexample usage: crash";
}

void ConsoleCrash::call(std::string args)
{
	throw new std::exception("ForceQuit");
}
